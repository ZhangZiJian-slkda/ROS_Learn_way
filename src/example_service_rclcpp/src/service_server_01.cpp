/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-08-26 21:53:00
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-09-08 22:56:14
 * @FilePath: /Ros_Learning_Way/src/example_service_rclcpp/src/service_server_01.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"

class service_server_01 : public rclcpp::Node
{
private:
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_ints_server;

    void handle_add_two_ints(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
        std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
        RCLCPP_INFO(this->get_logger(),"收到  a: %ld    b: %ld", request->a,request->b);
        response->sum = request->a + request->b;
    };
public:
    service_server_01(std::string name);
    ~service_server_01();
};

service_server_01::service_server_01(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(),"节点已启动：:%s.",name.c_str());
    //创建服务
    add_ints_server = this->create_service<example_interfaces::srv::AddTwoInts>(
        "add_two_ints_srv",
        std::bind(&service_server_01::handle_add_two_ints,this,
            std::placeholders::_1,std::placeholders::_2));
}

service_server_01::~service_server_01()
{
    RCLCPP_INFO(this->get_logger(),"Node is end!");
}


int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<service_server_01>("service_server_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}