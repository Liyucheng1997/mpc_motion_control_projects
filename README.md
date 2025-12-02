# MPC Motion Control Projects

## 简介 (Introduction)
本项目致力于探索和实现基于模型预测控制（Model Predictive Control, MPC）的运动控制算法。旨在为移动机器人、自动驾驶车辆等平台提供高效、鲁棒的路径跟踪与运动规划解决方案。

## 主要功能 (Key Features)

*   **核心控制算法**:
    *   **线性模型预测控制 (Linear MPC)**: 适用于计算资源受限或系统模型近似线性的场景。
    *   **非线性模型预测控制 (NMPC)**: 处理复杂的非线性系统动力学和约束。
*   **运动学与动力学建模**:
    *   支持多种常见的机器人底盘模型（如差速驱动 Differential Drive、阿克曼转向 Ackermann Steering、全向移动 Omnidirectional 等）。
*   **轨迹规划与避障**:
    *   基于优化的局部路径规划。
    *   静态与动态障碍物的实时避障能力。
*   **仿真与验证**:
    *   提供 Python/C++ 仿真环境。
    *   集成 Matplotlib 或 ROS Rviz 进行实时数据可视化。

## 环境依赖 (Requirements)
*   Python 3.x / C++ 14+
*   常见依赖库: NumPy, SciPy, OSQP/Ipopt (求解器), Matplotlib, ROS (可选)

## 快速开始 (Getting Started)
*(此处将添加具体的安装和运行指南)*

## 待办事项 (To-Do List)
- [ ] 初始化项目结构
- [ ] 实现基础车辆运动学模型
- [ ] 搭建简单的 MPC 仿真闭环
- [ ] 添加 ROS 接口支持

## 许可证 (License)
MIT License
