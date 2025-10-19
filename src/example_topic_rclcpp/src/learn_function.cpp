/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-19 18:30:33
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-19 18:49:57
 * @FilePath: /ROS_Learn_way/src/example_topic_rclcpp/src/learn_function.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

// free function
void save_with_free_fun(const string &file_name)
{
    cout << "free function" << file_name << endl;
}

// member function
class FileSave
{
private:
    /* data */
public:
    FileSave(/* args */) = default;
    ~FileSave() = default;

    void save_with_number_fun(const string &file_name)
    {
        cout << "free function" << file_name << endl;
    };
};

int main()
{
    FileSave file_save;
    // string my_member_function;
    // file_save.save_with_number_fun(my_member_function);

    auto save_with_lambda_fun = [](const string &file_name)
    {
        cout << "Lambda function:" << file_name << endl;
    };

    save_with_lambda_fun("file_text1111");

    function<void(const string &)> save1 = save_with_free_fun;
    function<void(const string &)> save2 = save_with_lambda_fun;
    function<void(const string &)> save3 = bind(&FileSave::save_with_number_fun, &file_save, placeholders::_1);

    save1("file_txt");
    save2("file.txt");
    save3("spa");

    return 0;
}