#!/usr/bin/env python3
"""
MPC参数自动调优脚本
执行网格搜索，在场景2(Speed Bump)中寻找最佳参数组合。
"""

import subprocess
import os
import time
import pandas as pd
import numpy as np
import itertools
import json
from datetime import datetime

# 配置
BASE_PATH = "/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws"
PLOT_PATH = os.path.join(BASE_PATH, "plot")
SIM_DURATION = 15.0  # 同步为15s (Matching User's Manual Run)
SCENARIO_ID = 2      # 仅针对场景2调优

# 默认参数 (作为Baseline)
DEFAULT_PARAMS = {
    'q_z': 500.0,
    'q_vz': 50.0,
    'r_suspension': 0.01
}

# 参数网格 (Expansive Search)
PARAM_GRID = {
    'q_z': [100.0, 500.0, 1000.0, 2000.0],
    'q_vz': [10.0, 50.0, 200.0, 500.0],
    'r_suspension': [0.001, 0.005, 0.01, 0.05]
}

def calculate_metrics(csv_path):
    """计算RMS和峰值"""
    if not os.path.exists(csv_path):
        return None, None
    try:
        df = pd.read_csv(csv_path)
        if 'az' not in df.columns:
            return None, None
        
        rms = np.sqrt(np.mean(np.square(df['az'])))
        peak = df['az'].abs().max()
        return rms, peak
    except Exception as e:
        print(f"Error reading csv: {e}")
        return None, None

def run_simulation(active_mode, params=None):
    """运行一次仿真"""
    mode_str = "Active" if active_mode else "Passive"
    
    cmd_list = [
        f"source /opt/ros/jazzy/setup.bash && source {BASE_PATH}/install/setup.bash",
        "ros2 launch mpc_car_control mpc_system.launch.py"
    ]
    
    # 基础参数
    args = [
        f"scenario_id:={SCENARIO_ID}",
        f"controller_type:=mpc",
        f"active_suspension_enabled:={'true' if active_mode else 'false'}",
        f"sim_duration:={SIM_DURATION}"
    ]
    
    # 附加调优参数 (仅对Active有效，Passive忽略)
    if active_mode and params:
        for k, v in params.items():
            args.append(f"{k}:={v}")
            
    cmd = f"{cmd_list[0]} && {cmd_list[1]} {' '.join(args)}"
    
    print(f"Running {mode_str} Sim...", end="", flush=True)
    try:
        result = subprocess.run(
            cmd,
            shell=True,
            executable='/bin/bash',
            check=True,
            cwd=BASE_PATH,
            timeout=SIM_DURATION + 30,
            stdout=subprocess.DEVNULL, # 减少输出干扰
            stderr=subprocess.PIPE
        )
        
        # 移动数据文件
        src = os.path.join(PLOT_PATH, "ride_comfort_data.csv")
        if active_mode:
            # 构造参数标志文件名
            param_str = "_".join([f"{k}{v}" for k, v in params.items()])
            dst = os.path.join(PLOT_PATH, f"tuning_{param_str}.csv")
        else:
            dst = os.path.join(PLOT_PATH, f"tuning_passive_baseline.csv")
            
        if os.path.exists(src):
            if os.path.exists(dst):
                os.remove(dst)
            os.rename(src, dst)
            print(" Done.")
            return dst
        else:
            print(" Failed (No Data).")
            return None
            
    except Exception as e:
        print(f" Error: {e}")
        return None

def main():
    print(f"========== MPC Tuning Start: Scenario {SCENARIO_ID} ==========")
    
    # 1. 运行 Passive Baseline (只需一次)
    print("\n[1/3] Running Passive Baseline...")
    passive_csv = run_simulation(active_mode=False)
    passive_rms, passive_peak = calculate_metrics(passive_csv)
    
    if passive_rms is None:
        print("Error: Passive baseline failed. Aborting.")
        return

    print(f"Passive Baseline: RMS={passive_rms:.4f}, Peak={passive_peak:.4f}")
    
    # 2. 运行网格搜索
    print("\n[2/3] Starting Grid Search...")
    keys, values = zip(*PARAM_GRID.items())
    combinations = [dict(zip(keys, v)) for v in itertools.product(*values)]
    
    results = []
    
    start_time = time.time()
    for idx, params in enumerate(combinations):
        print(f"Test {idx+1}/{len(combinations)}: {params}")
        
        csv_path = run_simulation(active_mode=True, params=params)
        
        if csv_path is None:
             print("  -> Simulation Failed (No Data)")
             continue

        rms, peak = calculate_metrics(csv_path)
        
        if rms is not None:
            imp_rms = (passive_rms - rms) / passive_rms * 100
            
            # 峰值抑制 (如果峰值比Passive大太多，则不可接受)
            peak_ratio = peak / passive_peak
            
            print(f"  -> RMS: {rms:.4f} (Imp: {imp_rms:.1f}%), Peak: {peak:.2f} (Ratio: {peak_ratio:.2f}x)")
            
            results.append({
                "params": params,
                "rms": rms,
                "peak": peak,
                "improvement": imp_rms,
                "valid": peak < 70.0 # 放宽阈值至 70 m/s^2 (Passvie Peak ~96)
            })
        else:
            print("  -> Simulation Failed")
            
    total_time = time.time() - start_time
    print(f"\nGrid Search Completed in {total_time/60:.1f} minutes.")
    
    # 3. 分析结果
    print("\n[3/3] Analysis & Best Parameters")
    
    # 筛选 valid 且改善率高的
    valid_results = [r for r in results if r['valid']]
    valid_results.sort(key=lambda x: x['improvement'], reverse=True)
    
    if not valid_results:
        print("No VALID results found (Limit: Peak < 70). Showing optimal regardless of peak:")
        results.sort(key=lambda x: x['improvement'], reverse=True)
        best_result = results[0]
    else:
        best_result = valid_results[0]
        
    print(f"\n🏆 BEST ROBUST CONFIGURATION:")
    print(json.dumps(best_result['params'], indent=2))
    print(f"RMS Improvement: {best_result['improvement']:.2f}%")
    print(f"Peak AZ: {best_result['peak']:.2f} m/s^2 (Passive: {passive_peak:.2f})")
    
    # 保存结果到文件
    output_data = {
        "timestamp": datetime.now().isoformat(),
        "scenario": SCENARIO_ID,
        "passive_rms": passive_rms,
        "best_config": best_result,
        "all_results": results
    }
    
    json_path = os.path.join(PLOT_PATH, "tuning_results.json")
    with open(json_path, 'w') as f:
        json.dump(output_data, f, indent=2)
    
    print(f"\nFull results saved to: {json_path}")
    
    # 保存最佳参数到独立文件方便读取
    best_params_path = os.path.join(PLOT_PATH, "best_mpc_params.json")
    with open(best_params_path, 'w') as f:
        json.dump(best_result['params'], f, indent=2)
        
    print(f"Best parameters saved to: {best_params_path}")

if __name__ == "__main__":
    main()
