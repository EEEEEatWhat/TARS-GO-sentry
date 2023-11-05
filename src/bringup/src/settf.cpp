#include <rclcpp/rclcpp.hpp>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <chrono>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("static_tf2_broadcaster");

    auto static_broadcaster = std::make_shared<tf2_ros::StaticTransformBroadcaster>(node);
    
    geometry_msgs::msg::TransformStamped static_transformStamped;
    while(rclcpp::ok())
    {    
        static_transformStamped.header.stamp = node->now();
        static_transformStamped.header.frame_id = "base_link";
        static_transformStamped.child_frame_id = "laser";
        static_transformStamped.transform.translation.x = 0.0;
        static_transformStamped.transform.translation.y = 0.0;
        static_transformStamped.transform.translation.z = 0.0;
        static_transformStamped.transform.rotation.x = 0.0;
        static_transformStamped.transform.rotation.y = 0.0;
        static_transformStamped.transform.rotation.z = 0.0;
        static_transformStamped.transform.rotation.w = 1.0;
        static_broadcaster->sendTransform(static_transformStamped);
        rclcpp::sleep_for(std::chrono::seconds(1));
    }
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}