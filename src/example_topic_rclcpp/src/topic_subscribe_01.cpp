/*
 * @Author: Robotics_Zhang 845603757@qq.com
 * @Date: 2025-08-26 00:14:12
 * @LastEditors: Robotics_Zhang 845603757@qq.com
 * @LastEditTime: 2025-08-26 00:40:40
 * @FilePath: /learn_ros_way/chapt_ws/src/example_topic_rclcpp/src/topic_subscribe_01.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class topic_subscribe_01 : public rclcpp :: Node
{
private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_;
    void command_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed = 0.0f;
        if (msg->data == "forward")
        {
            speed = 0.2f;
        }
        RCLCPP_INFO(this->get_logger()," I have received [%s] command , and send speed %f !",msg->data.c_str(),speed);
    
    }
public:
    topic_subscribe_01(std::string name);
    ~topic_subscribe_01();
};

topic_subscribe_01::topic_subscribe_01(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(),"hello ereryone  My name is %s !",name.c_str());
    
    command_subscribe_ = this->create_subscription<std_msgs::msg::String>("command", 10, std::bind(
        &topic_subscribe_01::command_callback, this, std::placeholders::_1));
}

topic_subscribe_01::~topic_subscribe_01()
{
    RCLCPP_INFO(this->get_logger(),"Node is ended!");
}

int main(int argc, char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<topic_subscribe_01>("topic_subscribe_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

// 运行发布节点
// ros2 run example_topic_rclcpp topic_publisher_01
// 运行接收节点
// ros2 run example_topic_rclcpp topic_subscribe_01
// 手动发布数据测试订阅者
// ros2 topic pub /command std_msgs/msg/String "{data: forward}"
// 查看计算图
// rqt