from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
def generate_launch_description():
    ld = LaunchDescription()
    config = os.path.join(
        get_package_share_directory('serial_node'),
        'config',
        'para.yaml'
    )
    examplenode = Node(
        package='turtlesim', #节点所在的功能包
        namespace='n1', #命名空间。如果存在同名节点，这一选项会有用
        executable='turtlesim_node', #表示要运行的可执行文件名或脚本名字.py
        parameters=[config], #参数
        output='screen', #用于将话题信息打印到屏幕
        name='nodename' #表示启动后的节点名，可以没有
    )
    ld.add_action(examplenode)
    return ld
