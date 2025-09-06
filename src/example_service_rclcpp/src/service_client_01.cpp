/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-08-26 21:53:22
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-08-31 22:54:40
 * @FilePath: /Ros_Learning_Way/src/example_service_rclcpp/src/service_client_01.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class service_client_01 : public rclcpp::Node
{
private:
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client;

    void result_callback(
        rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture 
        result_future){
            auto response = result_future.get();
            RCLCPP_INFO(this->get_logger(),"calculate the result:%ld",response->sum);
        }
    
public:
    service_client_01(std::string name);
    ~service_client_01();

    void send_request(int a,int b)
    {
        RCLCPP_INFO(this->get_logger(),"calculate %d+%d",a,b);

        while (!client -> wait_for_service(std::chrono::seconds(1)))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(),"w s zzj waiting for service has been derupt...");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "等待服务端上线中");
        }
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts_Request>();
        request->a = a;
        request->b = b;

        client->async_send_request(
            request,std::bind(&service_client_01::result_callback,this,std::placeholders::_1));
    }
};

service_client_01::service_client_01(std::string name) : Node(name)
{
    RCLCPP_INFO(this->get_logger(),"Node is start: %s.",name.c_str());

    client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints_srv");
    
}

service_client_01::~service_client_01()
{
    RCLCPP_INFO(this->get_logger(),"Node is ended Zhangzijian!");
}

int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<service_client_01>("service_client_01");
    node->send_request(5,6);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}