from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, TimerAction, Shutdown
from launch.substitutions import LaunchConfiguration, EqualsSubstitution
from launch.conditions import IfCondition
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    rviz_config_dir = os.path.join(
        get_package_share_directory('mpc_car_control'),
        'launch',
        'default.rviz'
    )

    sim_duration_arg = DeclareLaunchArgument(
        'sim_duration',
        default_value='15.0',
        description='Simulation Duration in seconds'
    )

    return LaunchDescription([
        sim_duration_arg,
        DeclareLaunchArgument(
            'scenario_id',
            default_value='1',
            description='Scenario ID (1: Straight, 2: Bump, 3: Turn, 4: Complex)'
        ),
        DeclareLaunchArgument(
            'controller_type',
            default_value='mpc',
            description='Controller Type (mpc, pid)'
        ),
        DeclareLaunchArgument(
            'active_suspension_enabled',
            default_value='true',
            description='Enable Active Suspension (true/false)'
        ),
        # 1. az_plotter
        Node(
            package='mpc_car_control',
            executable='az_plotter.py',
            name='az_plotter',
            output='screen'
        ),
        # 2. scenario_generator
        Node(
            package='mpc_car_control',
            executable='scenario_generator_node',
            name='scenario_generator_node',
            output='screen',
            parameters=[{'scenario_id': LaunchConfiguration('scenario_id')}]
        ),
        # 3. mpc_controller (if mpc)
        Node(
            package='mpc_car_control',
            executable='mpc_controller_node',
            name='mpc_controller_node',
            output='screen',
            condition=IfCondition(
                EqualsSubstitution(LaunchConfiguration('controller_type'), 'mpc')
            )
        ),
        # 4. control_allocator
        Node(
            package='mpc_car_control',
            executable='control_allocator_node',
            name='control_allocator_node',
            output='screen',
            parameters=[{'active_suspension_enabled': LaunchConfiguration('active_suspension_enabled')}]
        ),
        # 5. pid_controller
        Node(
            package='mpc_car_control',
            executable='pid_controller_node',
            name='pid_controller_node',
            output='screen'
        ),
        # 6. vehicle_model
        Node(
            package='mpc_car_control',
            executable='vehicle_model_node',
            name='vehicle_model_node',
            output='screen',
            parameters=[{'sim_duration': LaunchConfiguration('sim_duration')}]
        ),
        # 7. visualization
        Node(
            package='mpc_car_control',
            executable='visualization_node',
            name='visualization_node',
            output='screen'
        ),
        # 8. rviz2
        Node(
            package='rviz2',
            executable='rviz2',
            arguments=['-d', rviz_config_dir],
            output='screen'
        ),
        # Automatic Shutdown
        TimerAction(
            period=LaunchConfiguration('sim_duration'),
            actions=[Shutdown(reason='Simulation completed after specified duration')]
        )
    ])
