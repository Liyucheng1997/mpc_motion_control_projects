#!/usr/bin/env python3
"""
Prediction Horizon vs. MPC Computation Time Test Script

Tests N = 1, 6, 11, 16, 21, 26, 31, 36, 41, 46, 50
For each N:
  1. Modify mpc_controller_node.cpp to set N_ = N
  2. Recompile
  3. Run Scenario 2
  4. Read mpc_execution_times.csv and calculate mean
  5. Store result
Finally, plot N vs avg_time and save as PNG.
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
    # Handle multi-line case like: const int N_ =\n      50;
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

def get_avg_execution_time():
    """Read mpc_execution_times.csv and return average"""
    csv_path = os.path.join(PLOT_PATH, "mpc_execution_times.csv")
    if not os.path.exists(csv_path):
        return None
    try:
        df = pd.read_csv(csv_path)
        # Column name is "Execution Time (ms)"
        if 'Execution Time (ms)' in df.columns:
            return df['Execution Time (ms)'].mean()
        elif len(df.columns) == 1:
            return df.iloc[:, 0].mean()
        else:
            return None
    except Exception as e:
        print(f"  [ERROR] Reading CSV: {e}")
        return None

def main():
    print("=" * 60)
    print("Prediction Horizon vs. MPC Computation Time Test")
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
        
        # Step 4: Get Average Execution Time
        avg_time = get_avg_execution_time()
        if avg_time is None:
            print("  [WARNING] Could not read execution time")
            continue
        
        print(f"  -> Avg Execution Time: {avg_time:.2f} ms")
        results.append({'N': n, 'avg_time_ms': avg_time})
    
    print()
    print("=" * 60)
    print("Test Complete. Generating Plot...")
    print("=" * 60)
    
    if not results:
        print("No valid results collected. Exiting.")
        return
    
    # Create DataFrame and Plot
    df_results = pd.DataFrame(results)
    
    plt.figure(figsize=(10, 6))
    plt.plot(df_results['N'], df_results['avg_time_ms'], 'b-o', linewidth=2, markersize=8)
    plt.xlabel('Prediction Horizon (N)', fontsize=12)
    plt.ylabel('Average MPC Computation Time (ms)', fontsize=12)
    plt.title('MPC Computation Time vs. Prediction Horizon', fontsize=14)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.xticks(df_results['N'])
    
    # Annotate points
    for i, row in df_results.iterrows():
        plt.annotate(f"{row['avg_time_ms']:.1f}ms", 
                     (row['N'], row['avg_time_ms']),
                     textcoords="offset points", xytext=(0, 10),
                     ha='center', fontsize=9)
    
    plt.tight_layout()
    
    # Save plot
    plot_file = os.path.join(PLOT_PATH, "horizon_vs_computation_time.png")
    plt.savefig(plot_file, dpi=150)
    print(f"Plot saved to: {plot_file}")
    
    # Save data as CSV
    csv_file = os.path.join(PLOT_PATH, "horizon_efficiency_data.csv")
    df_results.to_csv(csv_file, index=False)
    print(f"Data saved to: {csv_file}")
    
    plt.show()

if __name__ == "__main__":
    main()
