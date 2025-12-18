from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch.conditions import LaunchConfigurationEquals
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    rviz_config_dir = os.path.join(
        get_package_share_directory('mpc_car_control'),
        'launch',
        'default.rviz'
    )

    scenario_id_arg = DeclareLaunchArgument(
        'scenario_id',
        default_value='1',
        description='Scenario ID (1: Straight, 2: Bump, 3: Turn, 4: Complex)'
    )

    controller_type_arg = DeclareLaunchArgument(
        'controller_type',
        default_value='mpc',
        description='Controller Type (mpc, pid)'
    )

    active_susp_arg = DeclareLaunchArgument(
        'active_suspension_enabled',
        default_value='true',
        description='Enable Active Suspension (true/false)'
    )

    return LaunchDescription([
        scenario_id_arg,
        controller_type_arg,
        active_susp_arg,
        # Visualization Plotter
        Node(
            package='mpc_car_control',
            executable='az_plotter.py',
            name='az_plotter',
            output='screen'
        ),
        Node(
            package='mpc_car_control',
            executable='scenario_generator_node',
            name='scenario_generator_node',
            output='screen',
            parameters=[{'scenario_id': LaunchConfiguration('scenario_id')}]
        ),
        # MPC Nodes (Run Layout: MPC + PID + Allocator)
        Node(
            package='mpc_car_control',
            executable='mpc_controller_node',
            name='mpc_controller_node',
            output='screen',
            condition=LaunchConfigurationEquals('controller_type', 'mpc')
        ),
        Node(
            package='mpc_car_control',
            executable='control_allocator_node',
            name='control_allocator_node',
            output='screen',
            # Allocator always runs
            parameters=[{'active_suspension_enabled': LaunchConfiguration('active_suspension_enabled')}]
        ),
        # PID Node (Run if 'pid' OR 'mpc' because MPC needs PID for steering)
        Node(
            package='mpc_car_control',
            executable='pid_controller_node',
            name='pid_controller_node',
            output='screen'
            # Always run PID? Or create a complex condition?
            # Simpler: Just run it. If 'controller_type' is 'pid', it works alone.
            # If 'mpc', it works in parallel.
            # Note: Condition removed to always run PID.
        ),
        Node(
            package='mpc_car_control',
            executable='vehicle_model_node',
            name='vehicle_model_node',
            output='screen'
        ),
        Node(
            package='mpc_car_control',
            executable='visualization_node',
            name='visualization_node',
            output='screen'
        ),
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', rviz_config_dir],
            output='screen'
        )
    ])
