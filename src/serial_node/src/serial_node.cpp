#include <iostream>
#include <asio.hpp>
#include <thread>
#include <random>
//定义一个结构体
#pragma pack(1)
typedef struct serial_node{
    uint8_t head_frame;
    uint8_t head_frame_id;
    struct {
        //自身参数
        float bllistic;							//弹道系数			
        float current_v;						//当前自身弹速
        float current_pitch;					//当前自身pitch	
        float current_yaw;						//当前自身yaw
        float xw_ROS;							//ROS坐标系下的位置x	
        float yw_ROS;							//ROS坐标系下的位置y
        float zw_ROS;							//ROS坐标系下的位置z
        float vxw_ROS;							//ROS坐标系下的vx
        float vyw_ROS;							//ROS坐标系下的vy	
        float vzw_ROS;							//ROS坐标系下的vz
    }self_data;
    struct {
        //目标参数
        float tar_yaw;							//目标yaw	
        float tar_v_yaw;						//目标yaw速度
        float bias_time;						//偏置时间
        float s_bias;							//枪口前推的距离
        float yaw_to_s_bias;					//yaw轴电机到枪口水平面的垂直距离
        uint8_t armor_type;						//RIGO:装甲板类型，1为平衡步兵（两块大装甲板），否则为四装甲板
    }target_data;
        uint8_t rx_end;							//帧尾
}Serial_Node;
#pragma pack()

void writeSerial(asio::serial_port& serialPort) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    Serial_Node send;

    while (true) {
        int randomNumber = dis(gen);
        std::cout << "Sent number: " << randomNumber << std::endl;

        // 将随机数写入串口
        asio::async_write(serialPort, asio::buffer(&randomNumber, sizeof(randomNumber)),
            [](const asio::error_code& error, std::size_t bytesTransferred) {
                (void)bytesTransferred;
                if (error) {
                    std::cerr << "Write error: " << error.message() << std::endl;
                }
            });

        // 延迟一段时间
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void readSerial(asio::serial_port& serialPort) {
    char data[8];
    asio::async_read(serialPort, asio::buffer(data, sizeof(data)),
        [&](const asio::error_code& error, std::size_t bytesTransferred) {
            (void)bytesTransferred;
            if (!error) {
                // 处理读取到的数据
                int receivedNumber = *reinterpret_cast<int*>(data);
                std::cout << "Received number: " << receivedNumber << std::endl;
            } else {
                std::cerr << "Read error: " << error.message() << std::endl;
            }

            // 继续异步读取串口数据
            readSerial(serialPort);
        });
}

int main() {
    asio::io_context ioContext;
    asio::serial_port serialPort(ioContext, "/dev/ttyACM0");  // 替换为你的串口设备路径

    // 配置串口参数
    serialPort.set_option(asio::serial_port_base::baud_rate(115200));
    serialPort.set_option(asio::serial_port_base::character_size(8));
    serialPort.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
    serialPort.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));

    // 异步写入串口数据
    std::thread writeThread([&]() {
        writeSerial(serialPort);
        ioContext.run();
    });

    // 异步读取串口数据
    std::thread readThread([&]() {
        readSerial(serialPort);
        ioContext.run();
    });

    // 运行IO上下文
    ioContext.run();

    // 等待线程结束
    writeThread.join();
    readThread.join();

    return 0;
}