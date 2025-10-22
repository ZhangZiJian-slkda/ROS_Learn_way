/*
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-22 22:00:03
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-22 22:19:19
 * @FilePath: /ROS_Learn_way/src/status_display/src/hello_qt.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <QApplication>
#include <QLabel>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *label = new QLabel();
    QString message = QString::fromStdString("Hello QT!");
    label->setText(message);
    label->show();
    app.exec();
    return 0;
}