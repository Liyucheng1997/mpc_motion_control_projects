#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from mpc_car_control.msg import VehicleState
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque
import threading

class AzPlotter(Node):
    def __init__(self):
        super().__init__('az_plotter')
        self.subscription = self.create_subscription(
            VehicleState,
            '/vehicle_state',
            self.listener_callback,
            10)
        self.az_data = [] # Keep all data
        self.t_data = []
        self.start_time = self.get_clock().now().nanoseconds / 1e9

    def listener_callback(self, msg):
        current_time = self.get_clock().now().nanoseconds / 1e9 - self.start_time
        self.az_data.append(msg.az)
        self.t_data.append(current_time)

def main():
    rclpy.init()
    node = AzPlotter()

    # Spin ROS in a separate thread so Matplotlib can block main thread
    thread = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
    thread.start()

    # Matplotlib Setup
    fig, ax = plt.subplots()
    line, = ax.plot([], [], 'r-', label='Vertical Accel (az)')
    ax.set_xlabel('Time (s)')
    ax.set_ylabel('Az (m/s^2)')
    ax.set_title('Vertical Acceleration Monitor')
    ax.grid(True)
    ax.legend()

    def update(frame):
        if not node.t_data:
            return line,
        
        t = node.t_data
        az = node.az_data
        
        line.set_data(t, az)
        
        # Auto-scale X Axis
        ax.set_xlim(0, max(10.0, t[-1] * 1.1))
        
        # Auto-scale Y Axis
        if az:
            y_min = min(az)
            y_max = max(az)
            margin = max(0.5, (y_max - y_min) * 0.1)
            ax.set_ylim(y_min - margin, y_max + margin)
            
        return line,

    ani = animation.FuncAnimation(fig, update, interval=50, blit=False)
    plt.show()

    rclpy.shutdown()

if __name__ == '__main__':
    main()
