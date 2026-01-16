import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

def calculate_metrics(df):
    """计算完整的Ride Comfort指标"""
    metrics = {}
    for col in ['z', 'vz', 'az']:
        if col in df.columns:
            data = df[col]
            metrics[f'{col}_rms'] = np.sqrt(np.mean(np.square(data)))
            metrics[f'{col}_p2p'] = data.max() - data.min()
    # 兼容旧格式（只有az列）
    if 'az' in df.columns and 'z' not in df.columns:
        metrics['az_rms'] = np.sqrt(np.mean(np.square(df['az'])))
        metrics['az_p2p'] = df['az'].max() - df['az'].min()
    return metrics

def plot_and_analyze():
    base_path = "/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws/plot/"
    scenarios = {
        1: "Flat Road (Deadband Check)",
        2: "Single Speed Bump (Impact Test)",
        3: "Steering (Roll Control)",
        4: "Complex Bumps (Robustness)"
    }
    
    fig, axes = plt.subplots(2, 2, figsize=(15, 10))
    axes = axes.flatten()
    
    report = ["# MPC Performance Analysis Report\\n"]
    report.append("| Scenario | Mode | z RMS | z P2P | vz RMS | vz P2P | az RMS | az P2P | Improvement |")
    report.append("| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |")
    
    for i, (sid, name) in enumerate(scenarios.items()):
        # 尝试新旧两种文件格式
        p_file = os.path.join(base_path, f"S{sid}_Passive.csv")
        a_file = os.path.join(base_path, f"S{sid}_Active.csv")
        
        # 兼容旧格式
        if not os.path.exists(p_file):
            p_file = os.path.join(base_path, f"data_S{sid}_Passive.csv")
        if not os.path.exists(a_file):
            a_file = os.path.join(base_path, f"data_S{sid}_Active.csv")
        
        ax = axes[i]
        
        if os.path.exists(p_file) and os.path.exists(a_file):
            df_p = pd.read_csv(p_file)
            df_a = pd.read_csv(a_file)
            
            m_p = calculate_metrics(df_p)
            m_a = calculate_metrics(df_a)
            
            # 使用az_rms计算改善
            p_rms = m_p.get('az_rms', 0)
            a_rms = m_a.get('az_rms', 0)
            p_p2p = m_p.get('az_p2p', 0)
            a_p2p = m_a.get('az_p2p', 0)
            imp = (p_rms - a_rms) / p_rms * 100 if p_rms > 0 else 0
            
            ax.plot(df_p['az'], label=f'Passive (RMS={p_rms:.2f})', color='gray', alpha=0.7)
            ax.plot(df_a['az'], label=f'Active/MPC (RMS={a_rms:.2f})', color='blue', linewidth=1.5)
            ax.set_title(f"S{sid}: {name}")
            ax.set_ylabel("Vertical Accel (az) [m/s^2]")
            ax.set_xlabel("Steps (10ms)")
            ax.legend()
            ax.grid(True, alpha=0.3)
            
            # 生成报告行
            z_rms_p = m_p.get('z_rms', 0)
            z_p2p_p = m_p.get('z_p2p', 0) 
            vz_rms_p = m_p.get('vz_rms', 0)
            vz_p2p_p = m_p.get('vz_p2p', 0)
            z_rms_a = m_a.get('z_rms', 0)
            z_p2p_a = m_a.get('z_p2p', 0)
            vz_rms_a = m_a.get('vz_rms', 0)
            vz_p2p_a = m_a.get('vz_p2p', 0)
            
            report.append(f"| {name} | Passive | {z_rms_p:.4f} | {z_p2p_p:.4f} | {vz_rms_p:.4f} | {vz_p2p_p:.4f} | {p_rms:.4f} | {p_p2p:.4f} | - |")
            report.append(f"| | Active | {z_rms_a:.4f} | {z_p2p_a:.4f} | {vz_rms_a:.4f} | {vz_p2p_a:.4f} | {a_rms:.4f} | {a_p2p:.4f} | **{imp:.1f}%** |")
        else:
            ax.text(0.5, 0.5, f"Missing Data for S{sid}", ha='center')
            
    plt.tight_layout()
    plot_dst = os.path.join(base_path, "multi_scenario_comparison.png")
    plt.savefig(plot_dst)
    print(f"Comparison plot saved to {plot_dst}")
    
    with open(os.path.join(base_path, "comparison_report.md"), "w") as f:
        f.write("\n".join(report))
    print("Metrics report saved to comparison_report.md")

if __name__ == "__main__":
    plot_and_analyze()
