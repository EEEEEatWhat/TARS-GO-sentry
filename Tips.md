# 小妙招之固定端口号:
## 给予USB永久权限

过两天写
## 不希望使用ttyUSB*这种可变端口

查看现有USB设备，有可能是ACM*这种，确定现有端口号
``` bash
ls /dev/ttyUSB*
``` 
然后输入
``` bash
lsusb
```
会得到类似如下的东西
``` bash
Bus 003 Device 005: ID 05e3:0610 Genesys Logic, Inc. Hub
Bus 003 Device 003: ID 0483:5740 STMicroelectronics Virtual COM Port
Bus 003 Device 007: ID 8087:0026 Intel Corp. AX201 Bluetooth
Bus 003 Device 006: ID 10c4:ea60 Silicon Labs CP210x UART Bridge
Bus 003 Device 004: ID 10c4:ea60 Silicon Labs CP210x UART Bridge
```
重点关注 ID后面的 如`10c4:ea60`对应`idVendor和idProduct` 根据这个写udev文件

用自己喜欢的编辑器在 `/etc/udev/rules.d/` 下创建`xx.rules`文件,写上下面的
``` bash
KERNEL== "ttyUSB*" , ATTRS{idVendor}== "10c4" , ATTRS{idProduct}== "ea60" , MODE:= "0777" , SYMLINK+= "rplidar" 
```
重新加载规则并拔插：
``` bash
sudo  udevadm control --reload
```
## 相同厂商的设备设置不同端口
如果有两个相同ID的设备会发现设置上面的也没用，这时候就得固定到物理端口

使用下面的命令查看物理端口`devpath`
``` bash
sudo udevadm info --attribute-walk --name=/dev/ttyUSB0 | grep devpath
```
发现不同端口对应的devpath不同，故可以用来区分端口：

修改规则，并重新加载规则
``` bash
KERNEL=="ttyUSB*", ATTRS{devpath}=="1",ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE:="0777",SYMLINK+="rplidar"
```
| 注意此时已经绑定到了物理的USB端口上，切勿随意插拔端口

输入`ls /dev/ -l` 得到如下结果
``` bash
lrwxrwxrwx   1 root root             7 11月  9 00:59 rplidar -> ttyUSB0
```
