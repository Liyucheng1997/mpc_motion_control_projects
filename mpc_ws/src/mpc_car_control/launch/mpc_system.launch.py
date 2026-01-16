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
        default_value='10.0',
        description='Simulation Duration in seconds (10s to avoid oscillation)'
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
        # Optimal Config: Low q_z (Best for Speed Bump: +17.5% RMS improvement)
        DeclareLaunchArgument('q_z', default_value='100.0', description='MPC Weight: z position (Low = Soft tracking)'),
        DeclareLaunchArgument('q_vz', default_value='50.0', description='MPC Weight: z velocity'),
        DeclareLaunchArgument('r_suspension', default_value='0.01', description='MPC Weight: suspension force'),

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
            parameters=[{
                'q_z': LaunchConfiguration('q_z'),
                'q_vz': LaunchConfiguration('q_vz'),
                'r_suspension': LaunchConfiguration('r_suspension')
            }],
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
        # Automatic Shutdown (增加2秒延迟，确保数据先保存)
        # vehicle_model_node会在sim_duration时保存数据并shutdown
        # 这里的Timer只是备用方案，确保所有节点最终关闭
        TimerAction(
            period=18.0,  # 固定为18秒，比sim_duration长3秒
            actions=[Shutdown(reason='Simulation completed after specified duration')]
        )
    ])
