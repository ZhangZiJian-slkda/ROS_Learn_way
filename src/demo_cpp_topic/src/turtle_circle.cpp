/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-19 22:46:20
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-19 23:32:10
 * @FilePath: /ROS_Learn_way/src/demo_cpp_topic/src/turtle_circle.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>
// #include <string>
using namespace std;
using namespace literals;

class TurtlesimCircleNode : public rclcpp::Node
{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

public:
    explicit TurtlesimCircleNode(const string &node_name) : Node(node_name)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        // timer_ = this->create_wall_timer(1000ms,
        //                                     bind(&TurtlesimCircleNode::timer_callback, this));

        timer_ = this->create_wall_timer(1000ms,
                                         [this]() -> void
                                         {
                                             auto msg = geometry_msgs::msg::Twist();
                                             msg.linear.x = 1.0;
                                             msg.angular.z = 0.5;
                                             publisher_->publish(msg);
                                         });
    }

    ~TurtlesimCircleNode() = default;

    // void timer_callback()
    // {
    //     auto msg = geometry_msgs::msg::Twist();
    //     msg.linear.x = 1.0;
    //     msg.angular.z = 0.5;
    //     publisher_->publish(msg);
    // }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = make_shared<TurtlesimCircleNode>("turtlesim_circle");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}