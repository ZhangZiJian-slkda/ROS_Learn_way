<!--
 * @Author: Zhang-sklda 845603757@qq.com
 * @Date: 2025-10-19 22:38:35
 * @LastEditors: Zhang-sklda 845603757@qq.com
 * @LastEditTime: 2025-10-20 00:26:43
 * @FilePath: /ROS_Learn_way/src/topic_ws/readme.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
----------------------------
turtle_circle.cpp
需求:控制海龟模拟器中的小海龟转指定半径的圆  
核心问题： 
1.小海龟凭什么听我的？（话题） 
2.前进后退我知道-》画圆-》线速度/角速度=半径 
3.发一下就停，如何循环发？-》定时器
----------------------------
turtle_control.cpp
需求:告诉小海龟到指定位置 自己滚过去
核心问题:
1.小海龟凭什么听我的?发布话题 
2.小海龟现在在哪里?订阅话题
3.怎么根据当前位置和目标位置计算角速度和线速度?两点之间距离->线速度 当前朝向和目标朝向差->角速度