# TARS_GO 哨兵的裁缝铺
* 简介
* 代码框架
* 项目依赖
* 食用说明

## 简介
吉林大学TARS_GO 2023 哨兵导航代码。

## 代码框架
还没写。

## 项目依赖
自己都不知道

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