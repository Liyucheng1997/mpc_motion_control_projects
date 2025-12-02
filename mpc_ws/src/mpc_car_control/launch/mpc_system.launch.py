from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
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

    return LaunchDescription([
        scenario_id_arg,
        Node(
            package='mpc_car_control',
            executable='scenario_generator_node',
            name='scenario_generator_node',
            output='screen',
            parameters=[{'scenario_id': LaunchConfiguration('scenario_id')}]
        ),
        Node(
            package='mpc_car_control',
            executable='mpc_controller_node',
            name='mpc_controller_node',
            output='screen'
        ),
        Node(
            package='mpc_car_control',
            executable='control_allocator_node',
            name='control_allocator_node',
            output='screen'
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
