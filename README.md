# TARS_GO 哨兵的裁缝铺
* 简介
* 代码框架
* 项目依赖
* 食用说明

## 简介
吉林大学TARS_GO 2023 哨兵导航代码。

## 代码框架
```bash
├── bringup                     # 统一启动入口
├── csm                         # 作为 ros2_laser_scan_matcher 依赖的库
├── laser_merger_rplidar        # 双2D雷达融合 pointcloud，并由 pointcloud 转 laserscan
│   ├── ira_laser_tools
│   ├── pointcloud_to_laserscan
│   └── ros2_laser_scan_merger
├── navigation2                 # ROS2 Navigation Stack
├── ros2_laser_scan_matcher     # 2D laserscan 里程计
├── run_navigation              # 外部向 Navigation 传参并启动 Navigation
├── serial_node                 # CH34x虚拟串口，与单片机通信
├── slam_gmapping               # gmapping 建图算法包
└── sllidar_ros2                # slamtec 雷达驱动包

```

## 项目依赖
自己都不知道

## 软硬件支持
intel 11代nuc

rplidar-S1 && A2

DJI C型开发板

系统使用Ubuntu 22.04 配合ROS2（humble）

固定端口号为 S1_rplidar A2_rplidar

## 食用说明
> 所有代码包除作为项目库文件的包都有单独launch启动，在bringup包中有一键启动所有功能包；指令如下

```bash
#rosdepc安装依赖 （小鱼一键安装）
wget http://fishros.com/install -O fishros && . fishros
rosdepc install -r --from-paths src --ignore-src --rosdistro $ROS_DISTRO -y
```
```bash
colcon build  --parallel-workers 16
. install/setup.bash
ros2 launch bringup bringup.launch.py
```
## TODO
- [x] 固定端口号
- [ ] 2D建图功能(gmapping)正常
- [ ] Cartograph 支持
- [ ] Navgation2 Sack 正常
- [ ] Nav2 支持阿克曼底盘、TEB