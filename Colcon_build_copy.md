# * 常用命令速查
## 1. colcon构建工具介绍
1. 构建系统与构建工具
2. 构建系统
3. 构建工具
4. colcon构建工具
## 2. colcon参数
1. Global 参数
2. Executor参数
3. Event handler参数
4. Discovery 参数
5. Package selection参数
6. Mixin参数
7. 环境变量
## 3. colcon build命令
1. --packages-select参数
2. --symlink-install参数
3. --parallel-workers NUMBER参数
## 4. colcon edit命令
## 5. colcon graph命令
1. --legend参数
2. --dot参数
## 6. colcon info
## 7. colcon list
## 8. colcon metadata

# * 常用命令速查

`colcon build --symlink-install`

创建符号连接，每次调整 launch文件时都不必重新build，如果install的文件需要拷贝到另外的机器使用，不要使用这个参数，否则会找不到源文件。

`colcon build --packages-select <name-of-pkg>`

编译一个单独的包，但这个指令并不会编译该包的依赖，往往会报错。

`colcon build --packages-up-to <name-of-pkg>`

编译一个单独的包和其依赖编译

`colcon build --packages-ignore <name-of-pkg>`

编译时忽略指定包

`colcon build --cmake-args -DCMAKE_BUILD_TYPE=Debug`

编译开启Debug模式

`colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release`

编译开启Release模式

`colcon build --packages-select rmw_coredds_shared_cpp --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Debug --event-handlers=console_direct+`

编译一个package 并且把log 显示在屏幕上

`colcon build --packages-select examples_rclcpp_minimal_action_client --symlink-install --cmake-args -DCMAKE_CXX_FLAGS='-o0 -ggdb' -DCMAKE_C_FLAGS='-o0 -ggdb'`

设置编译优化等级

`colcon build --cmake-args -DCMAKE_CXX_FLAGS="-O2 -g -Wall `

“-D” --宏定义，每定义一个就在前边加上"-D"，给gcc传递参数，-g debug选项， gdb模式，符号表会保存，-s link选项，删除符号表，这一步会极大减少文件体积。

## 1. colcon构建工具介绍

### 1. 构建系统与构建工具

构建系统与构建工具区分点在于针对的对象不同，构建系统只针对一个单独的包进行构建，而构建工具重点在于按照依赖关系依次调用构建系统完成一系列功能包的构建。

### 2. 构建系统

构建系统包括CMake、Python setuptools、catkin。


catkin基于CMake，并提供了一组方便的函数，使编写CMake包更容易。它自动生成 CMake 配置文件以及 pkg 配置文件。它还提供了注册不同类型测试的函数。python setuptools是用来创建和分发ROS的Python包。

### 3. 构建工具

构建工具包括catkin_make、catkin_make_isolated、python-catkin-tools、ament_tools、colcon。

catkin_make由包含ROS 1构建系统的ROS软件包catkin提供。该构建工具仅调用CMake一次，并使用CMake的函数 add_subdirectory()在单一环境中处理所有软件包。

catkin_make_isolated也是由包含ROS 1构建系统的ROS软件包catkin提供的。该构建工具是在catkin_make之后开发的，用于解决在单一CMake环境中构建多个软件包所涉及的问题。

catkin_tools是由用于构建ROS 1软件包的独立Python软件包提供的。该构建工具是在catkin_make / catkin_make_isolated之后开发的，用于并行构建多个软件包并提供显著的可用性改进。该构建工具支持构建CMake软件包并且单独构建这些软件包，以及支持跨软件包并行处理过程。

ament_tools是ament为早期ROS2提供的一种工具，可以让用户完成功能包的编译、测试、安装、卸载，而且它本身也是一个Python的功能包。

### 4. colcon构建工具

colcon是一个构建软件包集合的命令行工具，是ros构建工具catkin_make、catkin_make_isolated、catkin_tools 和ament_tools的迭代版本，其设计目的是为了开发一款通用的软件包构建工具，可以依赖不同的构建工具(如catkin_cmake, ament_tool等)，支持不同的构建系统(如catkin, ament等)。

ROS２Bouncy 版本之前的构建工具使用的是ament_tool，之后(foxy、Humble版本)的构建工具统一使用colcon。但ROS2默认是没有安装colcon的，需要单独安装。



>作者：wanghuohuo0716
链接：https://www.jianshu.com/p/5cc7a78a9dc6
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。