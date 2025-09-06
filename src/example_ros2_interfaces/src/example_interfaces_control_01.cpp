/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-09-01 00:06:33
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-09-01 23:46:41
 * @FilePath: /ROS_Learn_way/src/example_ros2_interfaces/src/example_interfaces_control_01.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "rclcpp/rclcpp.hpp"
#include "example_ros2_interfaces/srv/move_robot.hpp"
#include "example_ros2_interfaces/msg/robot_status.hpp"


class ExampleInterfacesControl : public rclcpp::Node    
{
private:
    rclcpp::Client<example_ros2_interfaces::srv::MoveRobot>::SharedPtr client;
    rclcpp::Subscription<example_ros2_interfaces::msg::RobotStatus>::SharedPtr robot_status_subscribe;

    void result_callback(rclcpp::Client<example_ros2_interfaces::srv::MoveRobot>::SharedFuture result_future)
    {
        audo response = result_future.get();
        RCLCPP_INFO(this->get_logger(), "收到移动结果：%f", response->pose);
    }

    void robot_status_callback(const example_ros2_interfaces::msg::RobotStatus::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "收到状态数据位置：%f 状态：%d", msg->pose ,msg->status);
    }
    
public:
    ExampleInterfacesControl(std::string name);
    ~ExampleInterfacesControl();

    void move_robot(float distance)
    {
        RCLCPP_INFO(this->get_logger(), "请求让机器人移动%f", distance);

        while (!client -> wait_for_service(std::chrono::seconds(1)))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(),"等待服务的过程中被打断...");
                return ;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务端上线中");
        }
        auto request = std::make_shared<example_ros2_interfaces::srv::MoveRobot::Request>();
        request->distance = distance;

        client -> async_send_request(
            request,std::bind(&ExampleInterfacesControl::result_callback,this,std::placeholders::_1));
            
    }
};

ExampleInterfacesControl::ExampleInterfacesControl(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_Logger(),"节点已启动: %s.",name.c_str());
    client = this->create_client<example_ros2_interfaces::srv::MoveRobot>("move_robot");
    robot_status_subscribe = this->create_subscription<example_ros2_interfaces::msg::RobotStatus>("robot_status",
        10,std::bind(&ExampleInterfacesControl::robot_status_callback,this,std::placeholders::_1));
}

ExampleInterfacesControl::~ExampleInterfacesControl()
{    
    RCLCPP_INFO("Node is ending!");
}

int main(int argc, char ** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<ExampleInterfacesControl>("example_interfaces_control_01");
    node->move_robot(5.0);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
