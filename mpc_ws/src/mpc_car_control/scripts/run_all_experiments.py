#!/usr/bin/env python3
"""
一键运行所有MPC悬架实验并生成综合对比报告
包含四个场景 x 两种模式 (Active/Passive) = 8次仿真
输出：性能对比图 + 计算效率图 + Markdown报告
"""

import subprocess
import os
import time
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# 配置
BASE_PATH = "/home/yucheng/MPC_Projects/mpc_motion_control_projects/mpc_ws"
PLOT_PATH = os.path.join(BASE_PATH, "plot")
SIM_DURATION = 10.0  # 10s to avoid oscillation

SCENARIOS = {
    1: "Flat Road (Deadband)",
    2: "Speed Bump (Impact)",
    3: "Corner (Roll Control)",
    4: "Corner + Bump (Complex)"
}

SCENARIOS_CN = {
    1: "直线平路 (Deadband测试)",
    2: "直线+减速带 (冲击吸收)",
    3: "转弯 (Roll控制)",
    4: "转弯+减速带 (综合测试)"
}


def calculate_metrics(df):
    """计算完整的Ride Comfort指标"""
    metrics = {}
    for col in ['z', 'vz', 'az']:
        if col in df.columns:
            data = df[col]
            metrics[f'{col}_rms'] = np.sqrt(np.mean(np.square(data)))
            metrics[f'{col}_p2p'] = data.max() - data.min()
    return metrics


def run_experiment(scenario_id, active_mode):
    """运行单个仿真实验"""
    mode_str = "Active" if active_mode else "Passive"
    print(f"\n{'='*60}")
    print(f"▶ 场景 {scenario_id}: {SCENARIOS[scenario_id]}")
    print(f"▶ 模式: {mode_str}")
    print(f"{'='*60}")

    cmd = f"""
    source /opt/ros/jazzy/setup.bash && \
    source {BASE_PATH}/install/setup.bash && \
    ros2 launch mpc_car_control mpc_system.launch.py \
        scenario_id:={scenario_id} \
        controller_type:=mpc \
        active_suspension_enabled:={'true' if active_mode else 'false'} \
        sim_duration:={SIM_DURATION}
    """

    try:
        result = subprocess.run(
            cmd, 
            shell=True, 
            executable='/bin/bash',
            check=True, 
            cwd=BASE_PATH,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.PIPE,
            timeout=SIM_DURATION + 30
        )
        time.sleep(1)

        # 移动并重命名数据文件
        src_comfort = os.path.join(PLOT_PATH, "ride_comfort_data.csv")
        src_mpc = os.path.join(PLOT_PATH, "mpc_execution_times.csv")
        
        dst_comfort = os.path.join(PLOT_PATH, f"S{scenario_id}_{mode_str}.csv")
        dst_mpc = os.path.join(PLOT_PATH, f"S{scenario_id}_{mode_str}_mpc_times.csv")

        if os.path.exists(src_comfort):
            if os.path.exists(dst_comfort):
                os.remove(dst_comfort)
            os.rename(src_comfort, dst_comfort)
            print(f"✓ 舒适性数据: {dst_comfort}")
        
        if os.path.exists(src_mpc) and active_mode:  # Only save MPC times for Active mode
            if os.path.exists(dst_mpc):
                os.remove(dst_mpc)
            os.rename(src_mpc, dst_mpc)
            print(f"✓ MPC计算时间: {dst_mpc}")
            
        return dst_comfort if os.path.exists(dst_comfort) else None

    except subprocess.TimeoutExpired:
        print(f"✗ 仿真超时")
        return None
    except Exception as e:
        print(f"✗ 仿真错误: {e}")
        return None


def generate_comparison_plot():
    """生成四场景舒适性对比图"""
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    axes = axes.flatten()

    for i, (sid, name) in enumerate(SCENARIOS.items()):
        ax = axes[i]
        p_file = os.path.join(PLOT_PATH, f"S{sid}_Passive.csv")
        a_file = os.path.join(PLOT_PATH, f"S{sid}_Active.csv")

        if os.path.exists(p_file) and os.path.exists(a_file):
            df_p = pd.read_csv(p_file)
            df_a = pd.read_csv(a_file)

            t = np.arange(len(df_p)) * 0.01

            p_rms = np.sqrt(np.mean(np.square(df_p['az'])))
            a_rms = np.sqrt(np.mean(np.square(df_a['az'])))
            improvement = (p_rms - a_rms) / p_rms * 100 if p_rms > 0 else 0

            ax.plot(t, df_p['az'], label=f'Passive (RMS={p_rms:.3f})', 
                   color='gray', alpha=0.7, linewidth=1)
            ax.plot(t, df_a['az'], label=f'Active (RMS={a_rms:.3f})', 
                   color='blue', linewidth=1.5)
            
            ax.set_title(f"S{sid}: {name}\nImprovement: {improvement:.1f}%", fontsize=11)
            ax.set_xlabel("Time (s)")
            ax.set_ylabel("Vertical Accel az (m/s²)")
            ax.legend(loc='upper right')
            ax.grid(True, alpha=0.3)
        else:
            ax.text(0.5, 0.5, f"S{sid} Data Missing", ha='center', va='center')
            ax.set_title(f"S{sid}: {name}")

    plt.tight_layout()
    plot_path = os.path.join(PLOT_PATH, "comprehensive_comparison.png")
    plt.savefig(plot_path, dpi=150)
    plt.close()
    print(f"\n✓ 舒适性对比图: {plot_path}")
    return plot_path


def generate_efficiency_plot():
    """生成四场景MPC计算效率对比图"""
    fig, axes = plt.subplots(2, 2, figsize=(16, 10))
    axes = axes.flatten()
    
    all_stats = []

    for i, (sid, name) in enumerate(SCENARIOS.items()):
        ax = axes[i]
        mpc_file = os.path.join(PLOT_PATH, f"S{sid}_Active_mpc_times.csv")

        if os.path.exists(mpc_file):
            df = pd.read_csv(mpc_file)
            
            if 'Execution Time (ms)' in df.columns:
                times = df['Execution Time (ms)'].values
            else:
                times = df.iloc[:, 0].values
            
            # Calculate statistics
            avg_time = np.mean(times)
            max_time = np.max(times)
            min_time = np.min(times)
            std_time = np.std(times)
            
            all_stats.append({
                'scenario': sid,
                'name': name,
                'avg': avg_time,
                'max': max_time,
                'min': min_time,
                'std': std_time
            })
            
            # Plot histogram
            ax.hist(times, bins=30, color='steelblue', alpha=0.7, edgecolor='black')
            ax.axvline(avg_time, color='red', linestyle='--', linewidth=2, 
                      label=f'Mean: {avg_time:.2f}ms')
            ax.axvline(10, color='orange', linestyle=':', linewidth=2, 
                      label='Real-time Limit (10ms)')
            
            ax.set_title(f"S{sid}: {name}\nAvg: {avg_time:.2f}ms, Max: {max_time:.2f}ms", fontsize=11)
            ax.set_xlabel("Computation Time (ms)")
            ax.set_ylabel("Frequency")
            ax.legend(loc='upper right', fontsize=9)
            ax.grid(True, alpha=0.3)
        else:
            ax.text(0.5, 0.5, f"S{sid} MPC Data Missing", ha='center', va='center')
            ax.set_title(f"S{sid}: {name}")

    plt.tight_layout()
    plot_path = os.path.join(PLOT_PATH, "mpc_efficiency_comparison.png")
    plt.savefig(plot_path, dpi=150)
    plt.close()
    print(f"✓ 计算效率对比图: {plot_path}")
    
    return plot_path, all_stats


def generate_summary_bar_chart(all_stats):
    """生成汇总柱状图"""
    if not all_stats:
        return None
        
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
    
    scenarios = [f"S{s['scenario']}" for s in all_stats]
    avgs = [s['avg'] for s in all_stats]
    maxs = [s['max'] for s in all_stats]
    
    # Computation Time Bar Chart
    x = np.arange(len(scenarios))
    width = 0.35
    
    bars1 = ax1.bar(x - width/2, avgs, width, label='Average', color='steelblue')
    bars2 = ax1.bar(x + width/2, maxs, width, label='Maximum', color='coral')
    ax1.axhline(10, color='red', linestyle='--', linewidth=2, label='Real-time Limit')
    
    ax1.set_xlabel('Scenario')
    ax1.set_ylabel('Computation Time (ms)')
    ax1.set_title('MPC Computation Time by Scenario')
    ax1.set_xticks(x)
    ax1.set_xticklabels(scenarios)
    ax1.legend()
    ax1.grid(True, alpha=0.3, axis='y')
    
    # Add value labels
    for bar in bars1:
        height = bar.get_height()
        ax1.annotate(f'{height:.1f}',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3), textcoords="offset points",
                    ha='center', va='bottom', fontsize=9)
    
    # Performance Summary (RMS comparison)
    improvements = []
    for sid in SCENARIOS.keys():
        p_file = os.path.join(PLOT_PATH, f"S{sid}_Passive.csv")
        a_file = os.path.join(PLOT_PATH, f"S{sid}_Active.csv")
        if os.path.exists(p_file) and os.path.exists(a_file):
            df_p = pd.read_csv(p_file)
            df_a = pd.read_csv(a_file)
            p_rms = np.sqrt(np.mean(np.square(df_p['az'])))
            a_rms = np.sqrt(np.mean(np.square(df_a['az'])))
            imp = (p_rms - a_rms) / p_rms * 100 if p_rms > 0 else 0
            improvements.append(imp)
        else:
            improvements.append(0)
    
    colors = ['green' if imp > 0 else 'red' for imp in improvements]
    bars3 = ax2.bar(scenarios, improvements, color=colors, alpha=0.7)
    ax2.axhline(0, color='black', linewidth=0.5)
    ax2.set_xlabel('Scenario')
    ax2.set_ylabel('az RMS Improvement (%)')
    ax2.set_title('Active vs Passive Performance Improvement')
    ax2.grid(True, alpha=0.3, axis='y')
    
    for bar, imp in zip(bars3, improvements):
        height = bar.get_height()
        ax2.annotate(f'{imp:.1f}%',
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3 if height >= 0 else -12), 
                    textcoords="offset points",
                    ha='center', va='bottom' if height >= 0 else 'top', 
                    fontsize=10, fontweight='bold')
    
    plt.tight_layout()
    plot_path = os.path.join(PLOT_PATH, "summary_chart.png")
    plt.savefig(plot_path, dpi=150)
    plt.close()
    print(f"✓ 汇总图表: {plot_path}")
    return plot_path


def generate_markdown_report(mpc_stats):
    """生成Markdown格式的综合报告"""
    report = [
        "# MPC主动悬架 性能验证报告\n",
        f"**生成时间**: {time.strftime('%Y-%m-%d %H:%M:%S')}\n",
        "\n## 1. 测试配置\n",
        f"- 仿真时长: {SIM_DURATION}s",
        "- 预测时域 N: 20",
        "- 控制时域 Nc: 3",
        "- 权重参数: q_z=100, q_vz=50, r_suspension=0.01 (Low q_z - Optimal for Speed Bump)",
        "- 控制器: MPC (Active) vs Passive (无主动悬架)",
        "- 采样率: 100Hz\n",
        "\n## 2. Ride Comfort 指标对比\n",
        "| 场景 | 模式 | z RMS (m) | z P2P (m) | vz RMS (m/s) | az RMS (m/s²) | az P2P (m/s²) | az改善 |",
        "| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: |"
    ]

    improvements = []

    for sid, name in SCENARIOS.items():
        p_file = os.path.join(PLOT_PATH, f"S{sid}_Passive.csv")
        a_file = os.path.join(PLOT_PATH, f"S{sid}_Active.csv")

        if os.path.exists(p_file) and os.path.exists(a_file):
            df_p = pd.read_csv(p_file)
            df_a = pd.read_csv(a_file)

            m_p = calculate_metrics(df_p)
            m_a = calculate_metrics(df_a)

            az_imp = (m_p['az_rms'] - m_a['az_rms']) / m_p['az_rms'] * 100 if m_p['az_rms'] > 0 else 0
            improvements.append(az_imp)

            short_name = name.split('(')[0].strip()
            report.append(
                f"| {short_name} | Passive | {m_p['z_rms']:.4f} | {m_p['z_p2p']:.4f} | "
                f"{m_p['vz_rms']:.4f} | {m_p['az_rms']:.4f} | {m_p['az_p2p']:.2f} | - |"
            )
            report.append(
                f"| | Active | {m_a['z_rms']:.4f} | {m_a['z_p2p']:.4f} | "
                f"{m_a['vz_rms']:.4f} | {m_a['az_rms']:.4f} | {m_a['az_p2p']:.2f} | **{az_imp:.1f}%** |"
            )
        else:
            report.append(f"| {name} | - | 数据缺失 | - | - | - | - | - |")

    # MPC计算效率
    report.append("\n## 3. MPC计算效率\n")
    report.append("| 场景 | 平均时间(ms) | 最大时间(ms) | 最小时间(ms) | 标准差(ms) | 实时性 |")
    report.append("| :--- | :---: | :---: | :---: | :---: | :---: |")
    
    for stat in mpc_stats:
        realtime = "✓ 满足" if stat['max'] < 10 else "✗ 超限"
        report.append(
            f"| S{stat['scenario']} | {stat['avg']:.2f} | {stat['max']:.2f} | "
            f"{stat['min']:.2f} | {stat['std']:.2f} | {realtime} |"
        )

    # 总结
    report.append("\n## 4. 总结\n")
    if improvements:
        avg_imp = np.mean(improvements)
        report.extend([
            f"- 平均az RMS改善: **{avg_imp:.1f}%**",
            f"- 最大az RMS改善: **{max(improvements):.1f}%** (场景{improvements.index(max(improvements))+1})",
            f"- 最小az RMS改善: **{min(improvements):.1f}%** (场景{improvements.index(min(improvements))+1})",
        ])
        
        if mpc_stats:
            avg_mpc = np.mean([s['avg'] for s in mpc_stats])
            max_mpc = max([s['max'] for s in mpc_stats])
            report.extend([
                f"- 平均MPC计算时间: **{avg_mpc:.2f}ms**",
                f"- 最大MPC计算时间: **{max_mpc:.2f}ms**",
                f"- 实时性约束 (10ms): {'**满足** ✓' if max_mpc < 10 else '**超限** ✗'}"
            ])

    report.append("\n## 5. 可视化结果\n")
    report.append("### 舒适性对比\n![综合对比图](comprehensive_comparison.png)\n")
    report.append("### 计算效率\n![效率对比图](mpc_efficiency_comparison.png)\n")
    report.append("### 汇总\n![汇总图表](summary_chart.png)")

    report_path = os.path.join(PLOT_PATH, "comprehensive_report.md")
    with open(report_path, 'w', encoding='utf-8') as f:
        f.write('\n'.join(report))
    print(f"✓ Markdown报告: {report_path}")
    return report_path


def run_all_experiments():
    """主函数：运行所有实验"""
    print("\n" + "="*60)
    print("         MPC主动悬架 综合验证实验")
    print("="*60)
    print(f"配置: N=20, Nc=3, q_z=500, q_vz=50, r=0.1 (Hard Suspension)")
    print(f"共 {len(SCENARIOS)} 个场景 x 2 种模式 = {len(SCENARIOS)*2} 次仿真")
    print(f"预计总时长: {len(SCENARIOS) * 2 * (SIM_DURATION + 5) / 60:.1f} 分钟")
    print("="*60)

    os.makedirs(PLOT_PATH, exist_ok=True)

    # 运行所有实验
    for sid in SCENARIOS.keys():
        run_experiment(sid, active_mode=False)  # Passive先
        run_experiment(sid, active_mode=True)   # Active后

    print("\n" + "="*60)
    print("         生成分析报告")
    print("="*60)

    # 生成报告
    generate_comparison_plot()
    _, mpc_stats = generate_efficiency_plot()
    generate_summary_bar_chart(mpc_stats)
    generate_markdown_report(mpc_stats)

    print("\n" + "="*60)
    print("         实验完成!")
    print("="*60)
    print(f"结果目录: {PLOT_PATH}")


if __name__ == "__main__":
    run_all_experiments()
