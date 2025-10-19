/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-19 18:08:23
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-19 18:19:58
 * @FilePath: /ROS_Learn_way/src/example_topic_rclcpp/src/Lambad.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// [capture list](parameters) -> return_type {function body}

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    auto add = [](int a, int b) -> int
    {
        return a + b;
    };

    int sum = add(200, 50);

    auto print_sum = [sum]() -> void
    {
        printf("print_sum %d:", sum);
        // cout << "print_sum" << sum << endl;
    };
    print_sum();
    return 0;
}