#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Empty
import sys
import termios
import tty
import select

class KeyboardListenerNode(Node):
    def __init__(self):
        super().__init__('keyboard_listener_node')
        self.publisher_ = self.create_publisher(Empty, '/pause_toggle', 10)
        self.settings = termios.tcgetattr(sys.stdin)
        self.get_logger().info('Keyboard Listener Started. Press SPACE to toggle pause. Press Ctrl+C to exit.')

    def getKey(self):
        tty.setraw(sys.stdin.fileno())
        rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
        if rlist:
            key = sys.stdin.read(1)
        else:
            key = ''
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.settings)
        return key

    def run(self):
        try:
            while rclpy.ok():
                key = self.getKey()
                if key == ' ':
                    msg = Empty()
                    self.publisher_.publish(msg)
                    self.get_logger().info('Space pressed -> Toggling Pause')
                elif key == '\x03': # Ctrl+C
                    break
        except Exception as e:
            print(e)
        finally:
            termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.settings)

def main(args=None):
    rclpy.init(args=args)
    node = KeyboardListenerNode()
    node.run()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
