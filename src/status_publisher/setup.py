'''
Author: Zhang-sklda 845603757@qq.com
Date: 2025-10-22 21:24:28
LastEditors: Zhang-sklda 845603757@qq.com
LastEditTime: 2025-10-22 21:40:58
FilePath: /ROS_Learn_way/src/status_publisher/setup.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
'''
from setuptools import find_packages, setup

package_name = 'status_publisher'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='zhang',
    maintainer_email='845603757@qq.com',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'sys_status_pub = status_publisher.sys_status_pub:main',
        ],
    },
)
