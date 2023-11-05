#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <boost/asio.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
class SerialNode : public rclcpp::Node
{
public:
  SerialNode()
    : Node("serial_node"),
      io_service_(),
      serial_(io_service_)
  {
    // 串口配置
    std::string port = "/dev/ttyACM0"; // 串口设备路径
    int baud_rate = 115200; // 波特率
    
    // 打开串口
    serial_.open(port);
    serial_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));

    // 创建发布者
    publisher_ = this->create_publisher<std_msgs::msg::String>("serial_data", 10);

    // 创建订阅者
    subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "scan",rclcpp::SensorDataQoS(), std::bind(&SerialNode::topicCallback, this, std::placeholders::_1));

    // 创建定时器，定时读取串口数据
    timer_ = this->create_wall_timer(std::chrono::milliseconds(100),
      std::bind(&SerialNode::readSerialData, this));
  }

private:
  void topicCallback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
  {
    // 将ROS消息转换为字符串
    // std::string data = msg->data;

    // 发送字符串到串口
    // boost::asio::write(serial_, boost::asio::buffer(data));
  }

  void readSerialData()
  {
    // 读取串口数据
    boost::asio::streambuf buffer;
    boost::asio::read_until(serial_, buffer, '\n');

    // 转换为字符串
    std::istream input(&buffer);
    std::string data;
    std::getline(input, data);


    RCLCPP_INFO(this->get_logger(), "接收的消息： '%s'", data.c_str());
    // 发布串口数据到ROS话题
    auto msg = std::make_shared<std_msgs::msg::String>();
    msg->data = data;
    publisher_->publish(*msg);
  }

  boost::asio::io_service io_service_;
  boost::asio::serial_port serial_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<SerialNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
