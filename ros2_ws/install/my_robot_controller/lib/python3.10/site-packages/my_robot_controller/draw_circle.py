#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist

class DrawCircleNode(Node):
    def __init__(self):
        super().__init__("draw_circle")
        # Create a publisher to the /turtle1/cmd_vel topic
        self.cmd_vel_pub_ = self.create_publisher(Twist, "/turtle1/cmd_vel", 10)
        # Create a timer that calls send_velocity_command every 0.5 seconds
        self.timer_ = self.create_timer(0.5, self.send_velocity_command)
        # Log that the node has started
        self.get_logger().info("Draw circle node has started.")

    def send_velocity_command(self):
        # Create a new Twist message
        msg = Twist()
        # Set linear and angular velocity for a circular motion
        msg.linear.x = 2.0  # Forward speed
        msg.angular.z = 1.0  # Angular speed (turning rate)
        # Publish the message
        self.cmd_vel_pub_.publish(msg)

def main(args=None):
    # Initialize ROS 2
    rclpy.init(args=args)
    # Create the node
    node = DrawCircleNode()
    # Spin the node to keep it running
    rclpy.spin(node)
    # Shutdown ROS 2 when done
    rclpy.shutdown()
