/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-19 18:55:23
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-19 22:21:48
 * @FilePath: /ROS_Learn_way/src/example_topic_rclcpp/src/learn_thread.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include "cpp-httplib/httplib.h"

using namespace std;

class Download
{
private:
    /* data */
public:
    Download(/* args */) = default;
    ~Download() = default;

    void download(const string &host, const string &path, const function<void(const string &, const string &)> &callback_word_count)
    {
        cout << "thread:" << this_thread::get_id() << endl;
        httplib::Client client(host);
        auto response = client.Get(path);
        if (response && response->status == 200)
        {
            callback_word_count(path, response->body);
        }
    };

    void start_download(const string &host, const string &path, const function<void(const string &, const string &)> &callback_word_count)
    {
        auto download_fun = bind(&Download::download, this, placeholders::_1, placeholders::_2, placeholders::_3);
        thread thread(download_fun, host, path, callback_word_count);
        thread.detach();
    };
};

int main()
{
    auto t = Download();
    auto word_count = [](const string &path, const string &result) -> void
    {
        cout << "finished" << path << result.length() << "->" << result.substr(0, 9) << endl;
    };

    t.start_download("http://0.0.0.0:8000", "/novel1.txt", word_count);
    t.start_download("http://0.0.0.0:8000", "/novel2.txt", word_count);
    t.start_download("http://0.0.0.0:8000", "/novel3.txt", word_count);

    this_thread::sleep_for(chrono::milliseconds(1000 * 10));

    return 0;
}