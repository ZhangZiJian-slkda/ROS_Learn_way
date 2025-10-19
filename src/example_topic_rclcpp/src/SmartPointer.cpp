/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-19 17:52:10
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-19 18:17:08
 * @FilePath: /ROS_Learn_way/src/example_topic_rclcpp/src/SmartPointer.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <memory>
using namespace std;

int main()
{
    auto p1 = make_shared<string>("this is a ptr");
    cout << "p1:" << p1.use_count() << p1.get() << endl;
    std::shared_ptr<std::string> p2 = std::make_shared<std::string>();
    cout << "p1:" << p1.use_count() << p1.get() << endl;
    p2 = p1;
    cout << "p2:" << p2.use_count() << p2.get() << endl;

    p1.reset();
    cout << "p1:" << p1.use_count() << p1.get() << endl;
    cout << "p2:" << p2.use_count() << p2.get() << endl;
    cout << "p2" << p2->c_str() << endl;

    return 0;
}