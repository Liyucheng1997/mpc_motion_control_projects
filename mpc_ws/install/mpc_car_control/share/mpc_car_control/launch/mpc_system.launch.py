from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='mpc_car_control',
            executable='scenario_generator_node',
            name='scenario_generator_node',
            output='screen'
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
            executable='vehicle_interface_node',
            name='vehicle_interface_node',
            output='screen'
        )
    ])
