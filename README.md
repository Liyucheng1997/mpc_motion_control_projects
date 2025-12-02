# ROS2 MPC Controller Project

This project implements a complete MPC controller system for a 6DOF vehicle model using ROS2 and C++.

## Architecture

The system consists of the following nodes:

1.  **`scenario_generator_node`**: Generates a reference trajectory (sinusoidal path) for the vehicle to follow.
2.  **`mpc_controller_node`**: Subscribes to the reference trajectory and vehicle state, and computes desired body forces/moments using a simplified MPC logic.
3.  **`control_allocator_node`**: Maps the body forces/moments to actuator commands (steering, throttle, brake).
4.  **`vehicle_interface_node`**: Simulates the vehicle dynamics (using a kinematic bicycle model) or interfaces with an external simulator (like Carsim via Simulink).

## Prerequisites

*   ROS2 (Foxy or later)
*   `colcon` build tool

## Build Instructions

1.  Clone the repository or copy the `mpc_car_control` package to your ROS2 workspace `src` folder.
2.  Build the workspace:
    ```bash
    cd mpc_ws
    colcon build --packages-select mpc_car_control
    ```
3.  Source the setup script:
    ```bash
    source install/setup.bash
    ```

## Run Instructions

To launch the entire system:

```bash
ros2 launch mpc_car_control mpc_system.launch.py
```

## Topics

*   `/reference_trajectory`: The target path.
*   `/vehicle_state`: Current vehicle state (x, y, yaw, v, etc.).
*   `/control_command_body`: Desired forces and moments.
*   `/actuator_command`: Final control inputs.
