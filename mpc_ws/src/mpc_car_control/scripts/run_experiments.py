import subprocess
import time
import os

def run_simulation(scenario_id, use_mpc, duration=15.0):
    mode_str = "Active" if use_mpc else "Passive"
    print(f"\n>>> Running Scenario {scenario_id} | Mode: {mode_str}")
    
    ctrl_type = "mpc" if use_mpc else "pid"
    active_susp = "true" if use_mpc else "false"
    
    cmd = [
        "ros2", "launch", "mpc_car_control", "mpc_system.launch.py",
        f"scenario_id:={scenario_id}",
        f"controller_type:={ctrl_type}",
        f"active_suspension_enabled:={active_susp}",
        f"sim_duration:={duration}"
    ]
    
    try:
        subprocess.run(cmd, check=True)
        time.sleep(2)
        
        # 整理数据
        base_path = "/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws/plot/"
        src_file = os.path.join(base_path, "az_history.csv")
        dst_file = os.path.join(base_path, f"data_S{scenario_id}_{mode_str}.csv")
        
        if os.path.exists(src_file):
            os.rename(src_file, dst_file)
            print(f"--- Data saved to {dst_file}")
        else:
            print(f"!!! Warning: {src_file} not found skipping rename.")
            
    except Exception as e:
        print(f"Error during simulation: {e}")

if __name__ == "__main__":
    # 确保目录存在
    os.makedirs("/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws/plot/", exist_ok=True)
    
    scenarios = [1, 2, 3, 4]
    for sid in scenarios:
        run_simulation(sid, False) # Passive
        run_simulation(sid, True)  # Active
