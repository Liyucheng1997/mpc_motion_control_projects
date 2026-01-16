#!/usr/bin/env python3
"""
Prediction Horizon vs. Ride Comfort (RMS & P2P) Test Script

Tests N = 1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 50
For each N:
  1. Modify mpc_controller_node.cpp to set N_ = N
  2. Recompile
  3. Run Scenario 2
  4. Read ride_comfort_data.csv and calculate RMS and P2P of az
  5. Store result
Finally, plot N vs RMS and P2P (dual-axis) and save as PNG.
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

# N values to test: 1, 6, 11, ..., 46, 50
N_VALUES = list(range(1, 51, 5))
if 50 not in N_VALUES:
    N_VALUES.append(50)

def modify_n_value(new_n):
    """Modify N_ value in mpc_controller_node.cpp"""
    with open(CPP_FILE, 'r') as f:
        content = f.read()
    
    # Pattern to match: const int N_ = XX;
    pattern = r'(const int N_ =\s*)\d+;'
    replacement = f'const int N_ = {new_n};'
    
    new_content, count = re.subn(pattern, replacement, content)
    
    if count == 0:
        print(f"  [ERROR] Failed to find N_ pattern in {CPP_FILE}")
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
        print(f"  [ERROR] Reading CSV: {e}")
        return None, None

def main():
    print("=" * 60)
    print("Prediction Horizon vs. Ride Comfort (RMS & P2P) Test")
    print("=" * 60)
    print(f"N values to test: {N_VALUES}")
    print()
    
    results = []
    
    for idx, n in enumerate(N_VALUES):
        print(f"[{idx+1}/{len(N_VALUES)}] Testing N = {n}")
        
        # Step 1: Modify N_
        print("  Modifying N_...", end="", flush=True)
        if not modify_n_value(n):
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
        
        # Step 4: Get Comfort Metrics
        rms, p2p = get_comfort_metrics()
        if rms is None:
            print("  [WARNING] Could not read comfort metrics")
            continue
        
        print(f"  -> az RMS: {rms:.4f} m/s², P2P: {p2p:.2f} m/s²")
        results.append({'N': n, 'az_rms': rms, 'az_p2p': p2p})
    
    print()
    print("=" * 60)
    print("Test Complete. Generating Plot...")
    print("=" * 60)
    
    if not results:
        print("No valid results collected. Exiting.")
        return
    
    # Create DataFrame and Plot
    df_results = pd.DataFrame(results)
    
    fig, ax1 = plt.subplots(figsize=(12, 7))
    
    # Primary axis: RMS
    color1 = 'tab:blue'
    ax1.set_xlabel('Prediction Horizon (N)', fontsize=12)
    ax1.set_ylabel('az RMS (m/s²)', color=color1, fontsize=12)
    line1, = ax1.plot(df_results['N'], df_results['az_rms'], 'b-o', 
                      linewidth=2, markersize=8, label='RMS')
    ax1.tick_params(axis='y', labelcolor=color1)
    ax1.set_xticks(df_results['N'])
    ax1.grid(True, linestyle='--', alpha=0.5)
    
    # Secondary axis: P2P
    ax2 = ax1.twinx()
    color2 = 'tab:red'
    ax2.set_ylabel('az Peak-to-Peak (m/s²)', color=color2, fontsize=12)
    line2, = ax2.plot(df_results['N'], df_results['az_p2p'], 'r-s', 
                      linewidth=2, markersize=8, label='P2P')
    ax2.tick_params(axis='y', labelcolor=color2)
    
    # Title and Legend
    plt.title('Ride Comfort vs. Prediction Horizon (Scenario 2: Speed Bump)', fontsize=14)
    lines = [line1, line2]
    labels = [l.get_label() for l in lines]
    ax1.legend(lines, labels, loc='upper right')
    
    # Annotate RMS points
    for i, row in df_results.iterrows():
        ax1.annotate(f"{row['az_rms']:.2f}", 
                     (row['N'], row['az_rms']),
                     textcoords="offset points", xytext=(0, 10),
                     ha='center', fontsize=8, color=color1)
    
    fig.tight_layout()
    
    # Save plot
    plot_file = os.path.join(PLOT_PATH, "horizon_vs_comfort.png")
    plt.savefig(plot_file, dpi=150)
    print(f"Plot saved to: {plot_file}")
    
    # Save data as CSV
    csv_file = os.path.join(PLOT_PATH, "horizon_comfort_data.csv")
    df_results.to_csv(csv_file, index=False)
    print(f"Data saved to: {csv_file}")
    
    plt.show()

if __name__ == "__main__":
    main()
