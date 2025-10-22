'''
Author: Zhang-sklda 845603757@qq.com
Date: 2025-10-22 21:25:20
LastEditors: Zhang-sklda 845603757@qq.com
LastEditTime: 2025-10-22 21:44:44
FilePath: /ROS_Learn_way/src/status_publisher/status_publisher/sys_status_pub.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
'''
import rclpy
from status_interfaces.msg import SystemStatus

from rclpy.node import Node
import psutil
import platform

class SysStatusPub(Node):
    def __init__(self,node_name):
        super().__init__(node_name)
        self.status_publisher_ =self.create_publisher(
            SystemStatus,"sys_status",10
        )
        self.timer_ = self.create_timer(1.0,self.timer_callback)


    def timer_callback(self):
        cpu_percent = psutil.cpu_percent()
        memory_info = psutil.virtual_memory()
        net_io_counters = psutil.net_io_counters()

# builtin_interfaces/Time stamp 
# string host_name
# float32 cpu_percent
# float32 memory_percent
# float32 memory_total_size
# float32 memory_available
# float64 net_sent
# float64 net_receive
        msg = SystemStatus()
        msg.stamp = self.get_clock().now().to_msg()
        msg.host_name = platform.node()
        msg.cpu_percent = psutil.cpu_percent
        msg.memory_percent = memory_info.percent
        msg.memory_total_size = memory_info.total/1024/1024
        msg.memory_available = memory_info.available/1024/1024
        msg.net_sent = net_io_counters.bytes_sent/1024/1024
        msg.net_receive = net_io_counters.bytes_recv/1024/1024

        self.get_logger().info(f'publisher: {str(msg)}')
        self.status_publisher_.publish(msg)

def main():
    rclpy.init()
    node = SysStatusPub('sys_status_pub')
    rclpy.spin(node)
    rclpy.shutdown()