/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-09-01 00:02:54
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-09-01 23:31:12
 * @FilePath: /ROS_Learn_way/src/example_ros2_interfaces/src/example_interfaces_robot_01.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "rclcpp/rclcpp.hpp"
#include "example_ros2_interfaces/msg/robot_status.hpp"
#include "example_ros2_interfaces/srv/move_robot.hpp"

/*创建一个机器人类，模拟真实机器人*/
class Robot
{
private:
    // 声明当前位置
    float current_pose_ = 0.0;
    // 目标距离
    float target_pose_ = 0.0;
    int status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
public:
    Robot(/* args */) = default ;
    ~Robot() = default;


    // 移动指定的距离
    float move_distance(float distance){
        status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_MOVING;
        target_pose_ += distance;

        // 当目标距离-当前距离 大于 0.01 ,则持续向目标移动
        while (fabs(target_pose_ - current_pose_) > 0.01)
        {
            // 每一步移动当前到目标距离的1/10
            float step = distance / fabs(distance) * fabs(target_pose_ - current_pose_) * 0.1;
            current_pose_ += step;
            std::cout << "移动了：" << step << "当前位置：" << current_pose_ << std::endl;
            // 当前线程休眠500ms
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
        return current_pose_;
    }
    
    // 获取当前位置
    float get_current_pose() {return current_pose_};
    // 获取当前状态
    int get_status() {return status_ };

};

/*
 * 测试指令：ros2 service call /move_robot example_ros2_interfaces/srv/MoveRobot "{distance: 5}"
*/

class ExampleInterfacesRobot : public rclcpp::Node
{
private:
    Robot robot;
    // 定时器，用于定时发布机器人位置
    rclcpp::TimerBase::SharedPtr timer;
    // 移动机器人服务
    rclcpp::Service<example_ros2_interfaces::srv::MoveRobot>::SharedPtr move_robot_service;
    // 发布机器人位姿发布者
    rclcpp::Publisher<example_ros2_interfaces::msg::RobotStatus>::SharedPtr robot_status_publisher;


    void timer_callback()
    {
        example_ros2_interfaces::msg::RobotStatus message;
        message.status = robot.get_status();
        message.pose = robot.get_current_pose();
        RCLCPP::INFO(this->get_logger(),"Publishing: %f",robot.get_current_pose());
        robot_status_publisher->publish(message);
    }


    void handle_move_robot(const std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Request> request,
        std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Response> response)
        {
            RCLCPP_INFO(this->get_logger(),"收到请求移动距离: %f,当前位置:%f",request->distance,robot.get_current_pose());
            robot.move_distance(request->distance);
            response->pose = robot.get_current_pose();
        }



public:
    ExampleInterfacesRobot(std::string name);

};

ExampleInterfacesRobot::ExampleInterfacesRobot(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_Logger(),"节点已启动: %s.",name.c_str());
    /*创建move_robot服务*/
    move_robot_server_ = this->create_service<example_ros2_interfaces::srv::MoveRobot>(
        "move_robot",std::bind(&ExampleInterfacesRobot::handle_move_robot,this,std::placeholders::_1,std::placeholders::_2));
    /*创建发布者*/
    robot_status_publisher = this->create_publisher<example_ros2_interfaces::msg::RobotStatus>("robot_status",10);

    timer = this -> create_wall_timer(std::chrono::milliseconds(500),std::bind(&ExampleInterfacesRobot::timer_callback,this));

}


int main(int argc ,char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<ExampleInterfacesRobot>("example_interfaces_robot_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}