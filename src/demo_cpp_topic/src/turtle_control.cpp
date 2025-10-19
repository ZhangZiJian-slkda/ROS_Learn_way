/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-19 22:46:20
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-20 00:24:50
 * @FilePath: /ROS_Learn_way/src/demo_cpp_topic/src/turtle_circle.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>
#include "turtlesim/msg/pose.hpp"

using namespace std;
using namespace literals;

class TurtlesimControlNode : public rclcpp::Node
{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;
    double target_x_{-0.6};
    double target_y_{-0.6};
    double k_{0.3};
    double max_speed_{1.0};

public:
    explicit TurtlesimControlNode(const string &node_name) : Node(node_name)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
        subscriber_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, bind(&TurtlesimControlNode::subscribe_callback, this, placeholders::_1));
    }

    ~TurtlesimControlNode() = default;

    void subscribe_callback(const turtlesim::msg::Pose::SharedPtr pose)
    {
        // TODO
        
        // 1.获取当前的位置
        auto current_x_ = pose->x;
        auto current_y_ = pose->y;
        RCLCPP_INFO(get_logger(), "current pose x=%f,y=%f", current_x_, current_y_);

        // 2.计算当前海龟位置跟目标位置之间的距离差和角度差
        auto distance = sqrt(
            (target_x_ - current_x_) * (target_x_ - current_x_) +
            (target_y_ - current_y_) * (target_y_ - current_y_));

            // (current_x_ - target_x_) * (current_x_ - target_x_) +
            // (current_y_ - target_y_) * (current_y_ - target_y_));

        auto angle = atan2((current_y_ - target_y_), (current_x_ - target_x_)) - pose->theta;

        // 3.控制策略
        auto msg = geometry_msgs::msg::Twist();
        if (distance > 0.1)
        {
            if (fabs(angle) > 0.2)
            {
                msg.angular.z = fabs(angle);
            }
            else
            {
                msg.linear.x = k_ * distance;
            }
        }
        // 4.限制线速度最大值
        if (msg.linear.x > max_speed_)
        {
            msg.linear.x = max_speed_;
        }
        
        // 5.发布消息
        publisher_->publish(msg);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = make_shared<TurtlesimControlNode>("turtle_control");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}