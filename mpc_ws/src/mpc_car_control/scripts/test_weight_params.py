#!/usr/bin/env python3
"""
MPC Weight Parameters vs. Performance Test Script (Fixed Version)

IMPORTANT: First runs TRUE Passive baseline (active_suspension_enabled=false)
Then tests different Active MPC weight configurations against it.

Tests on Scenario 2 (Speed Bump) only, analyzing first 10 seconds.
"""

import subprocess
import os
import time
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# === Configuration ===
BASE_PATH = "/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws"
PLOT_PATH = os.path.join(BASE_PATH, "plot")
SIM_DURATION = 10.0  # 10s to avoid oscillation
SCENARIO_ID = 2      # Focus on Speed Bump
DT = 0.01

# Weight configurations to test
WEIGHT_CONFIGS = [
    {"name": "Low q_z",     "q_z": 100.0,  "q_vz": 50.0,   "r_suspension": 0.01},
    {"name": "Med q_z",     "q_z": 500.0,  "q_vz": 50.0,   "r_suspension": 0.01},
    {"name": "High q_z",    "q_z": 2000.0, "q_vz": 50.0,   "r_suspension": 0.01},
    {"name": "Low q_vz",    "q_z": 500.0,  "q_vz": 10.0,   "r_suspension": 0.01},
    {"name": "High q_vz",   "q_z": 500.0,  "q_vz": 200.0,  "r_suspension": 0.01},
    {"name": "Soft r",      "q_z": 500.0,  "q_vz": 50.0,   "r_suspension": 0.001},
    {"name": "Hard r",      "q_z": 500.0,  "q_vz": 50.0,   "r_suspension": 0.1},
    {"name": "Balanced",    "q_z": 1000.0, "q_vz": 100.0,  "r_suspension": 0.005},
    {"name": "Aggressive",  "q_z": 2000.0, "q_vz": 200.0,  "r_suspension": 0.001},
    {"name": "Conservative","q_z": 100.0,  "q_vz": 10.0,   "r_suspension": 0.1},
]

def run_passive_simulation():
    """Run TRUE Passive simulation (active_suspension_enabled=false)"""
    cmd = f"""
    source /opt/ros/jazzy/setup.bash && \
    source {BASE_PATH}/install/setup.bash && \
    ros2 launch mpc_car_control mpc_system.launch.py \
        scenario_id:={SCENARIO_ID} \
        sim_duration:={SIM_DURATION} \
        active_suspension_enabled:=false
    """
    result = subprocess.run(
        cmd, shell=True, executable='/bin/bash',
        stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
        timeout=SIM_DURATION + 60
    )
    return result.returncode == 0

def run_active_simulation(config):
    """Run Active simulation with specified weight parameters"""
    cmd = f"""
    source /opt/ros/jazzy/setup.bash && \
    source {BASE_PATH}/install/setup.bash && \
    ros2 launch mpc_car_control mpc_system.launch.py \
        scenario_id:={SCENARIO_ID} \
        sim_duration:={SIM_DURATION} \
        active_suspension_enabled:=true \
        q_z:={config['q_z']} \
        q_vz:={config['q_vz']} \
        r_suspension:={config['r_suspension']}
    """
    result = subprocess.run(
        cmd, shell=True, executable='/bin/bash',
        stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
        timeout=SIM_DURATION + 60
    )
    return result.returncode == 0

def get_metrics():
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
        print(f"  [ERROR] Reading data: {e}")
        return None, None

def main():
    print("=" * 70)
    print("MPC Weight Parameters Tuning (Fixed - True Passive Baseline)")
    print("=" * 70)
    print(f"Scenario: {SCENARIO_ID} (Speed Bump)")
    print(f"Duration: {SIM_DURATION}s")
    print()
    
    # Step 1: Run TRUE Passive Baseline
    print("[1/11] Running TRUE Passive Baseline (active_suspension_enabled=false)")
    print("  Running...", end="", flush=True)
    if not run_passive_simulation():
        print(" FAILED")
        return
    print(" Done")
    
    passive_rms, passive_p2p = get_metrics()
    if passive_rms is None:
        print("  [ERROR] Could not get Passive metrics")
        return
    
    print(f"  🎯 PASSIVE BASELINE: RMS={passive_rms:.4f} m/s², P2P={passive_p2p:.2f} m/s²")
    print()
    
    # Step 2: Test Active configurations
    results = []
    
    for idx, config in enumerate(WEIGHT_CONFIGS):
        print(f"[{idx+2}/{len(WEIGHT_CONFIGS)+1}] Testing ACTIVE: {config['name']}")
        print(f"    q_z={config['q_z']}, q_vz={config['q_vz']}, r={config['r_suspension']}")
        print("  Running...", end="", flush=True)
        
        if not run_active_simulation(config):
            print(" FAILED")
            continue
        print(" Done")
        
        rms, p2p = get_metrics()
        if rms is None:
            print("  [WARNING] Could not read metrics")
            continue
        
        improvement = (passive_rms - rms) / passive_rms * 100
        p2p_improvement = (passive_p2p - p2p) / passive_p2p * 100
        
        status = "✓ BETTER" if improvement > 0 else "✗ WORSE"
        print(f"  -> RMS={rms:.4f} ({improvement:+.1f}% {status}), P2P={p2p:.2f} ({p2p_improvement:+.1f}%)")
        
        results.append({
            'name': config['name'],
            'q_z': config['q_z'],
            'q_vz': config['q_vz'],
            'r_suspension': config['r_suspension'],
            'rms': rms,
            'p2p': p2p,
            'rms_improvement': improvement,
            'p2p_improvement': p2p_improvement
        })
    
    print()
    print("=" * 70)
    print("RESULTS (Sorted by RMS Improvement)")
    print("=" * 70)
    
    df_results = pd.DataFrame(results)
    df_sorted = df_results.sort_values('rms_improvement', ascending=False)
    
    print(f"\n{'Config':<15} | {'RMS':>8} | {'Imp%':>8} | {'P2P':>8} | Status")
    print("-" * 60)
    print(f"{'PASSIVE':<15} | {passive_rms:>8.4f} | {'BASE':>8} | {passive_p2p:>8.2f} | 🎯 Baseline")
    print("-" * 60)
    
    for _, row in df_sorted.iterrows():
        status = "✓" if row['rms_improvement'] > 0 else "✗"
        print(f"{row['name']:<15} | {row['rms']:>8.4f} | {row['rms_improvement']:>+7.1f}% | {row['p2p']:>8.2f} | {status}")
    
    # Find best
    valid_results = df_sorted[df_sorted['rms_improvement'] > 0]
    
    if len(valid_results) > 0:
        best = valid_results.iloc[0]
        print()
        print("=" * 70)
        print(f"🏆 BEST CONFIGURATION: {best['name']}")
        print(f"   q_z={best['q_z']}, q_vz={best['q_vz']}, r_suspension={best['r_suspension']}")
        print(f"   RMS Improvement: {best['rms_improvement']:.1f}%")
        print(f"   P2P Improvement: {best['p2p_improvement']:.1f}%")
        print("=" * 70)
    else:
        print()
        print("⚠️ WARNING: No configuration improved over Passive baseline!")
        print("   The best 'least-worse' option:")
        worst = df_sorted.iloc[0]
        print(f"   {worst['name']}: {worst['rms_improvement']:+.1f}%")
    
    # Save results
    csv_file = os.path.join(PLOT_PATH, "weight_tuning_vs_passive.csv")
    df_results.to_csv(csv_file, index=False)
    print(f"\nData saved to: {csv_file}")
    
    # Plot
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    
    # RMS comparison
    colors = ['green' if x > 0 else 'red' for x in df_sorted['rms_improvement']]
    ax1.barh(df_sorted['name'], df_sorted['rms_improvement'], color=colors, alpha=0.7)
    ax1.axvline(0, color='black', linewidth=1)
    ax1.set_xlabel('RMS Improvement vs Passive (%)')
    ax1.set_title(f'Active vs Passive (S{SCENARIO_ID})\nPassive RMS: {passive_rms:.3f} m/s²')
    ax1.grid(True, alpha=0.3, axis='x')
    
    # RMS values
    x = np.arange(len(df_sorted) + 1)
    rms_values = [passive_rms] + df_sorted['rms'].tolist()
    names = ['PASSIVE'] + df_sorted['name'].tolist()
    colors2 = ['blue'] + ['green' if r < passive_rms else 'red' for r in df_sorted['rms']]
    
    ax2.bar(x, rms_values, color=colors2, alpha=0.7)
    ax2.set_xticks(x)
    ax2.set_xticklabels(names, rotation=45, ha='right')
    ax2.set_ylabel('az RMS (m/s²)')
    ax2.set_title('Absolute RMS Comparison')
    ax2.axhline(passive_rms, color='blue', linestyle='--', label=f'Passive: {passive_rms:.3f}')
    ax2.legend()
    ax2.grid(True, alpha=0.3, axis='y')
    
    plt.tight_layout()
    plot_file = os.path.join(PLOT_PATH, "weight_tuning_vs_passive.png")
    plt.savefig(plot_file, dpi=150)
    print(f"Plot saved to: {plot_file}")

if __name__ == "__main__":
    main()
