#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import LogInfo
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():

    channel_type =  LaunchConfiguration('channel_type', default='serial')
    '''serial_port使用固定后的端口号'''
    '''根据雷达自行设定'''
    A2_serial_port = LaunchConfiguration('serial_port', default='/dev/A2_rplidar')
    A2_serial_baudrate = LaunchConfiguration('serial_baudrate', default='115200')

    S1_serial_port = LaunchConfiguration('serial_port', default='/dev/S1_rplidar')
    S1_serial_baudrate = LaunchConfiguration('serial_baudrate', default='256000')
    frame_id = LaunchConfiguration('frame_id', default='laser')
    inverted = LaunchConfiguration('inverted', default='false')
    angle_compensate = LaunchConfiguration('angle_compensate', default='true')
    scan_mode = LaunchConfiguration('scan_mode', default='Sensitivity')
    
    return LaunchDescription([

        DeclareLaunchArgument(
            'scan_mode',
            default_value=scan_mode,
            description='Specifying scan mode of lidar'),


        Node(
            package='sllidar_ros2',
            executable='sllidar_node',
            name='A2_sllidar_node',
            remappings=[("/scan","lidar_front_right/scan")],
            parameters=[{'channel_type':channel_type,
                         'serial_port': A2_serial_port, 
                         'serial_baudrate': A2_serial_baudrate, 
                         'frame_id': frame_id,
                         'inverted': inverted, 
                         'angle_compensate': angle_compensate}],
            output='screen'),   

        Node(
            package='sllidar_ros2',
            executable='sllidar_node',
            name='S1_sllidar_node',
            remappings=[("/scan","lidar_front_right/scan")],
            parameters=[{'channel_type':channel_type,
                         'serial_port': S1_serial_port, 
                         'serial_baudrate': S1_serial_baudrate, 
                         'frame_id': frame_id,
                         'inverted': inverted, 
                         'angle_compensate': angle_compensate}],
            output='screen'),       

    ])

