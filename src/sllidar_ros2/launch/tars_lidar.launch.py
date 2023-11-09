#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import LogInfo
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

'''端口号已经被固定为A2_rplidar S1_rplidar如果无法找着雷达请查询.rules文件'''
def generate_launch_description():
    channel_type =  LaunchConfiguration('channel_type', default='serial')
    A2_serial_port = LaunchConfiguration('serial_port', default='/dev/A2_rplidar')
    A2_serial_baudrate = LaunchConfiguration('serial_baudrate', default='115200')

    S1_serial_port = LaunchConfiguration('serial_port', default='/dev/S1_rplidar')
    S1_serial_baudrate = LaunchConfiguration('serial_baudrate', default='256000')
    frame_id = LaunchConfiguration('frame_id', default='laser')
    inverted = LaunchConfiguration('inverted', default='false')
    angle_compensate = LaunchConfiguration('angle_compensate', default='true')
    # scan_mode = LaunchConfiguration('scan_mode', default='Express')

    rviz_config_dir = os.path.join(
            get_package_share_directory('sllidar_ros2'),
            'rviz',
            'sllidar_ros2.rviz')

    return LaunchDescription([


        Node(
            package='sllidar_ros2',
            executable='sllidar_node',
            name='sllidar_A2',
            remappings=[("/scan","lidar_rear_left/scan")],
            parameters=[{'channel_type':channel_type,
                         'serial_port': A2_serial_port, 
                         'serial_baudrate': A2_serial_baudrate, 
                         'frame_id': frame_id,
                         'inverted': inverted, 
                         'angle_compensate': angle_compensate, 
                        #  'scan_mode': scan_mode
                         }],
            output='screen'),

        Node(
            package='sllidar_ros2',
            executable='sllidar_node',
            name='sllidar_S1',
            remappings=[("/scan","lidar_front_right/scan")],
            parameters=[{'channel_type':channel_type,
                         'serial_port': S1_serial_port, 
                         'serial_baudrate': S1_serial_baudrate, 
                         'frame_id': frame_id,
                         'inverted': inverted, 
                         'angle_compensate': angle_compensate
                         }],
            output='screen'),

        # Node(
        #     package='rviz2',
        #     executable='rviz2',
        #     name='rviz2',
        #     arguments=['-d', rviz_config_dir],
        #     output='screen'),
    ])

