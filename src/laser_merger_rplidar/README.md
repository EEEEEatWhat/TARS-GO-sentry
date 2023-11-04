### 食用方法 ###

The command for RPLIDAR S1 is :

```bash
ros2 launch sllidar_ros2 view_sllidar_s1_launch.py
```

To launch with visualizer (RVIZ2)

```bash
ros2 launch ros2_laser_scan_merger visualize_merge_2_scan.launch.py

```
---

### TODO ###

- 配置merger的tf
- 试试其他融合代码对比效果
- 点云去畸变（找开源或者自己搓（））
