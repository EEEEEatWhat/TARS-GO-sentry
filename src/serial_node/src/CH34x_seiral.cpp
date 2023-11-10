#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <asio.hpp>
#include "geometry_msgs/msg/twist.hpp"
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

class SerialNode : public rclcpp::Node
{
public:
    SerialNode(const std::string serial_port)
    :   Node("serial_node"),
        io_service_(),
        serial_(io_service_,serial_port)
    {
        // 打开串口
        // serial_.open(port);
        // 配置串口参数
        serial_.set_option(asio::serial_port_base::baud_rate(115200));
        serial_.set_option(asio::serial_port_base::character_size(8));
        serial_.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
        serial_.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));

        // 创建发布者
        // publisher_ = this->create_publisher<std_msgs::msg::String>("serial_data", 10);

        // 创建订阅者
        subscriber_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "cmd_vel",10,std::bind(&SerialNode::topicCallback, this, std::placeholders::_1));

        // 创建定时器，定时读取串口数据
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100),
        std::bind(&SerialNode::readSerialData, this));
    }

private:
void topicCallback(const geometry_msgs::msg::Twist::SharedPtr msg){
    serial_msg.self_data.vxw_ROS = msg->linear.x;
    serial_msg.self_data.vyw_ROS = msg->linear.y;
    serial_msg.self_data.vzw_ROS = msg->angular.z;
    asio::write(serial_, asio::buffer(&serial_msg, sizeof(serial_msg)));
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void readSerialData(){
    // // 读取串口数据
    // asio::streambuf buffer;
    // asio::read_until(serial_, buffer, '\n');

    // // 转换为字符串
    // std::istream input(&buffer);
    // std::string data;
    // std::getline(input, data);


    // RCLCPP_INFO(this->get_logger(), "接收的消息： '%s'", data.c_str());
    // // 发布串口数据到ROS话题
    // auto msg = std::make_shared<std_msgs::msg::String>();
    // msg->data = data;
    // publisher_->publish(*msg);
}

    Serial_Node serial_msg;
    asio::io_service io_service_;
    asio::serial_port serial_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscriber_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SerialNode>("/dev/ttyACM0");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
