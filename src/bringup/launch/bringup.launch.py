#
#   created by: suzukisuncy
#   github.com/suzukisuncy
#   2023/11/4
#
# 导入库
import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
    """定义LaunchDescription对象"""
    ld = LaunchDescription()

    """定位功能包路径"""
    rplidar_path = get_package_share_directory('sllidar_ros2')
    merger_path = get_package_share_directory('ros2_laser_scan_merger')
    matcher_path = get_package_share_directory('ros2_laser_scan_matcher')

    """设置所需路径"""
    rpliadar_launch_path = os.path.join(rplidar_path, 'launch')
    merger_launch_path = os.path.join(merger_path, 'launch')
    matcher_node_path = os.path.join(matcher_path, 'src')

    """添加launch文件"""
    rpliarlaunch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(rpliadar_launch_path, 'sllidar_s1_launch.py')
        ),    
            # launch_arguments={'arg-name': example-arg}.items()
    )
    mergerlaunch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(merger_launch_path, 'merge_2_scan.launch.py')
        ),      
            # launch_arguments={'arg-name': example-arg}.items()
    )
    """添加Node节点"""
    matcher_to_odom = Node(
        package =  'ros2_laser_scan_matcher',
        executable = 'laser_scan_matcher' 
    )
    """添加启动项目"""
    ld.add_action(rpliarlaunch)
    ld.add_action(mergerlaunch)
    ld.add_action(matcher_to_odom)
    return ld