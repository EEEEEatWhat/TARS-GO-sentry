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

    """定位功能包package路径"""
    rplidar_package = get_package_share_directory('sllidar_ros2')
    merger_package = get_package_share_directory('ros2_laser_scan_merger')
    matcher_package = get_package_share_directory('ros2_laser_scan_matcher')
    gmapping_package = get_package_share_directory('slam_gmapping')
    runnavigation_package = get_package_share_directory('run_navigation')
    bringup_package = get_package_share_directory('bringup')

    """设置所需dir路径"""
    rpliadar_launch_dir = os.path.join(rplidar_package, 'launch')
    merger_launch_dir = os.path.join(merger_package, 'launch')
    matcher_node_dir = os.path.join(matcher_package, 'src')
    gmapping_launch_dir = os.path.join(gmapping_package, 'launch')
    runnavigation_launch_dir = os.path.join(runnavigation_package,'launch')
    rviz_config_dir = os.path.join(bringup_package,'rviz','rviz_config.rviz')

    """添加launch文件cmd"""
    rpliarlaunch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(rpliadar_launch_dir, 'tars_lidar.launch.py')
        ),    
            # launch_arguments={'arg-name': example-arg}.items()
    )
    mergerlaunch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(merger_launch_dir, 'merge_2_scan.launch.py')
        ),      
            # launch_arguments={'arg-name': example-arg}.items()
    )
    gmappinglaunch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gmapping_launch_dir, 'slam_gmapping.launch.py')
        ),      
            # launch_arguments={'arg-name': example-arg}.items()
    )
    runnavigationlaunch_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(runnavigation_launch_dir, 'run_navigation2.launch.py')
        ),      
            # launch_arguments={'arg-name': example-arg}.items()
    )

    """添加Node节点cmd"""
    matcher_to_odom_cmd = Node(
        package =  'ros2_laser_scan_matcher',
        executable = 'laser_scan_matcher' 
    )
    settf_cmd = Node(
        package =  'bringup',
        executable = 'settf' 
    )    
    rviz_cmd = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_dir],
        output='screen'
    )
    
    """添加启动项目"""
    ld.add_action(settf_cmd)
    ld.add_action(rpliarlaunch_cmd)
    ld.add_action(mergerlaunch_cmd)
    ld.add_action(matcher_to_odom_cmd)
    # ld.add_action(gmappinglaunch_cmd)
    # ld.add_action(runnavigationlaunch_cmd)
    ld.add_action(rviz_cmd)

    return ld