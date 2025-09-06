/*
 * @Author: Robotics_Zhang 845603757@qq.com
 * @Date: 2025-08-25 23:28:37
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-08-26 21:24:55
 * @FilePath: /learn_ros_way/chapt_ws/src/example_topic_rclcpp/src/topic_publisher_01.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher01 : public rclcpp::Node
{
private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;

    void timer_callback()
    {
        std_msgs::msg::String message;
        message.data = "forward";
        RCLCPP_INFO(this->get_logger(),"Publisher: %s ",message.data.c_str());
        command_publisher_ -> publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;

public:

    TopicPublisher01(std::string name);
    ~TopicPublisher01();
};

TopicPublisher01::TopicPublisher01(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(),"%s Node is Starting!",name.c_str());
    command_publisher_=this->create_publisher<std_msgs::msg::String>("command",10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(500),std::bind(&TopicPublisher01::timer_callback,this));

}
/*定时器
是ROS2中的另外一个常用功能，通过定时器可以实现按照一定周期调用某个函数以实现定时发布等逻辑。
定时器对应的类是 rclcpp::TimerBase，调用create_wall_timer将返回其共享指针。
创建定时器时传入了两个参数，这两个参数都利用了C++11的新特性。 
std::bind(&TopicPublisher01::timer_callback, this)，bind() 函数的意义就像它的函数名一样，是用来绑定函数调用的某些参数的。
*/

TopicPublisher01::~TopicPublisher01()
{
    RCLCPP_INFO(this->get_logger(),"Node is ended!");
}

int main(int argc, char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<TopicPublisher01>("topic_publisher_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
