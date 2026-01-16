#!/usr/bin/env python3
"""
Control Horizon vs. Efficiency & Comfort Combined Test Script

Tests Nc = 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 (with N fixed at 20)
For each Nc:
  1. Modify mpc_controller_node.cpp to set Nc_ = Nc
  2. Recompile
  3. Run Scenario 2
  4. Read both mpc_execution_times.csv and ride_comfort_data.csv
  5. Calculate avg computation time, RMS and P2P
  6. Store results
Finally:
  - Plot 1: Nc vs avg_time
  - Plot 2: Nc vs RMS & P2P (dual axis)
"""

import subprocess
import os
import re
import time
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# === Configuration ===
BASE_PATH = "/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws"
CPP_FILE = os.path.join(BASE_PATH, "src/mpc_car_control/src/mpc_controller_node.cpp")
PLOT_PATH = os.path.join(BASE_PATH, "plot")
SIM_DURATION = 15.0
SCENARIO_ID = 2

# Nc values to test: 1, 3, 5, ..., 19
NC_VALUES = list(range(1, 21, 2))

def modify_nc_value(new_nc):
    """Modify Nc_ value in mpc_controller_node.cpp"""
    with open(CPP_FILE, 'r') as f:
        content = f.read()
    
    # Pattern to match: const int Nc_ = XX;
    pattern = r'(const int Nc_ =\s*)\d+;'
    replacement = f'const int Nc_ = {new_nc};'
    
    new_content, count = re.subn(pattern, replacement, content)
    
    if count == 0:
        print(f"  [ERROR] Failed to find Nc_ pattern in {CPP_FILE}")
        return False
    
    with open(CPP_FILE, 'w') as f:
        f.write(new_content)
    
    return True

def compile_package():
    """Compile the mpc_car_control package"""
    cmd = f"source /opt/ros/jazzy/setup.bash && cd {BASE_PATH} && colcon build --packages-select mpc_car_control"
    result = subprocess.run(
        cmd, shell=True, executable='/bin/bash',
        stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
        timeout=120
    )
    return result.returncode == 0

def run_simulation():
    """Run Scenario 2 simulation"""
    cmd = f"""
    source /opt/ros/jazzy/setup.bash && \
    source {BASE_PATH}/install/setup.bash && \
    ros2 launch mpc_car_control mpc_system.launch.py \
        scenario_id:={SCENARIO_ID} \
        sim_duration:={SIM_DURATION}
    """
    result = subprocess.run(
        cmd, shell=True, executable='/bin/bash',
        stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
        timeout=SIM_DURATION + 60
    )
    return result.returncode == 0

def get_avg_execution_time():
    """Read mpc_execution_times.csv and return average"""
    csv_path = os.path.join(PLOT_PATH, "mpc_execution_times.csv")
    if not os.path.exists(csv_path):
        return None
    try:
        df = pd.read_csv(csv_path)
        if 'Execution Time (ms)' in df.columns:
            return df['Execution Time (ms)'].mean()
        elif len(df.columns) == 1:
            return df.iloc[:, 0].mean()
        else:
            return None
    except Exception as e:
        print(f"  [ERROR] Reading execution times: {e}")
        return None

def get_comfort_metrics():
    """Read ride_comfort_data.csv and return RMS and P2P of az"""
    csv_path = os.path.join(PLOT_PATH, "ride_comfort_data.csv")
    if not os.path.exists(csv_path):
        return None, None
    try:
        df = pd.read_csv(csv_path)
        if 'az' not in df.columns:
            return None, None
        az = df['az']
        rms = np.sqrt(np.mean(np.square(az)))
        p2p = az.max() - az.min()
        return rms, p2p
    except Exception as e:
        print(f"  [ERROR] Reading comfort data: {e}")
        return None, None

def main():
    print("=" * 70)
    print("Control Horizon vs. Efficiency & Comfort Combined Test")
    print("=" * 70)
    print(f"Nc values to test: {NC_VALUES}")
    print(f"Prediction Horizon N is fixed at 20")
    print()
    
    results = []
    
    for idx, nc in enumerate(NC_VALUES):
        print(f"[{idx+1}/{len(NC_VALUES)}] Testing Nc = {nc}")
        
        # Step 1: Modify Nc_
        print("  Modifying Nc_...", end="", flush=True)
        if not modify_nc_value(nc):
            print(" FAILED")
            continue
        print(" Done")
        
        # Step 2: Compile
        print("  Compiling...", end="", flush=True)
        if not compile_package():
            print(" FAILED")
            continue
        print(" Done")
        
        # Step 3: Run Simulation
        print("  Running Simulation...", end="", flush=True)
        if not run_simulation():
            print(" FAILED")
            continue
        print(" Done")
        
        # Step 4: Get Metrics
        avg_time = get_avg_execution_time()
        rms, p2p = get_comfort_metrics()
        
        if avg_time is None or rms is None:
            print("  [WARNING] Could not read metrics")
            continue
        
        print(f"  -> Avg Time: {avg_time:.2f} ms, az RMS: {rms:.4f} m/s², P2P: {p2p:.2f} m/s²")
        results.append({
            'Nc': nc, 
            'avg_time_ms': avg_time, 
            'az_rms': rms, 
            'az_p2p': p2p
        })
    
    print()
    print("=" * 70)
    print("Test Complete. Generating Plots...")
    print("=" * 70)
    
    if not results:
        print("No valid results collected. Exiting.")
        return
    
    df_results = pd.DataFrame(results)
    
    # ============ Plot 1: Computation Time ============
    fig1, ax1 = plt.subplots(figsize=(10, 6))
    ax1.plot(df_results['Nc'], df_results['avg_time_ms'], 'b-o', linewidth=2, markersize=8)
    ax1.set_xlabel('Control Horizon (Nc)', fontsize=12)
    ax1.set_ylabel('Average MPC Computation Time (ms)', fontsize=12)
    ax1.set_title('MPC Computation Time vs. Control Horizon (N=20)', fontsize=14)
    ax1.grid(True, linestyle='--', alpha=0.7)
    ax1.set_xticks(df_results['Nc'])
    
    for i, row in df_results.iterrows():
        ax1.annotate(f"{row['avg_time_ms']:.1f}ms", 
                     (row['Nc'], row['avg_time_ms']),
                     textcoords="offset points", xytext=(0, 10),
                     ha='center', fontsize=9)
    
    fig1.tight_layout()
    plot1_file = os.path.join(PLOT_PATH, "control_horizon_vs_computation_time.png")
    fig1.savefig(plot1_file, dpi=150)
    print(f"Plot 1 saved to: {plot1_file}")
    
    # ============ Plot 2: Comfort (RMS & P2P) ============
    fig2, ax2_1 = plt.subplots(figsize=(12, 7))
    
    color1 = 'tab:blue'
    ax2_1.set_xlabel('Control Horizon (Nc)', fontsize=12)
    ax2_1.set_ylabel('az RMS (m/s²)', color=color1, fontsize=12)
    line1, = ax2_1.plot(df_results['Nc'], df_results['az_rms'], 'b-o', 
                        linewidth=2, markersize=8, label='RMS')
    ax2_1.tick_params(axis='y', labelcolor=color1)
    ax2_1.set_xticks(df_results['Nc'])
    ax2_1.grid(True, linestyle='--', alpha=0.5)
    
    ax2_2 = ax2_1.twinx()
    color2 = 'tab:red'
    ax2_2.set_ylabel('az Peak-to-Peak (m/s²)', color=color2, fontsize=12)
    line2, = ax2_2.plot(df_results['Nc'], df_results['az_p2p'], 'r-s', 
                        linewidth=2, markersize=8, label='P2P')
    ax2_2.tick_params(axis='y', labelcolor=color2)
    
    plt.title('Ride Comfort vs. Control Horizon (N=20, Scenario 2)', fontsize=14)
    lines = [line1, line2]
    labels = [l.get_label() for l in lines]
    ax2_1.legend(lines, labels, loc='upper right')
    
    for i, row in df_results.iterrows():
        ax2_1.annotate(f"{row['az_rms']:.2f}", 
                       (row['Nc'], row['az_rms']),
                       textcoords="offset points", xytext=(0, 10),
                       ha='center', fontsize=8, color=color1)
    
    fig2.tight_layout()
    plot2_file = os.path.join(PLOT_PATH, "control_horizon_vs_comfort.png")
    fig2.savefig(plot2_file, dpi=150)
    print(f"Plot 2 saved to: {plot2_file}")
    
    # Save data as CSV
    csv_file = os.path.join(PLOT_PATH, "control_horizon_test_data.csv")
    df_results.to_csv(csv_file, index=False)
    print(f"Data saved to: {csv_file}")
    
    plt.show()

if __name__ == "__main__":
    main()
