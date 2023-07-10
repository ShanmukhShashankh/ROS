#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64


class NumberCounterNode(Node):
    def __init__(self):
        super().__init__("number_counter")
        self.counter = 0
        self.publisher = self.create_publisher(Int64, "number_count", 10)
        self.subscriber = self.create_subscription(Int64, "number", self.callback, 10)
        self.get_logger().info("Number Counter node is successfully implemented")
    

    def callback(self, msg:Int64):
        new_msg = int(msg.data)
        self.get_logger().info("%d" % (new_msg,))
        self.counter += 1
        number = Int64()
        number.data = self.counter
        self.publisher.publish(number)
        

def main(args=None):
    rclpy.init(args=args)
    node = NumberCounterNode()
    rclpy.spin(node)
    rclpy.shutdown()