
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8_multi_array.hpp"
#include "std_msgs/msg/float32.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class ArraySumTranceiver : public rclcpp::Node
{
public:
  ArraySumTranceiver()
  : Node("Sum_Array")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int8MultiArray>(
      "Auza_array", 10, std::bind(&ArraySumTranceiver::topic_callback, this, _1));

    publisher_ = this->create_publisher<std_msgs::msg::Float32>("array_sum", 10);
  }

private:
  void topic_callback(const std_msgs::msg::Int8MultiArray & msg_sub) const
  {
    std_msgs::msg::Float32 msg_pub;
    msg_pub.data = msg_sub.data[0] + msg_sub.data[1] + msg_sub.data[2];
    RCLCPP_INFO(this->get_logger(), "I heard: a:%d b:%d c:%d", msg_sub.data[0],msg_sub.data[1],msg_sub.data[2]);
    RCLCPP_INFO(this->get_logger(), "Publishing: %.4f", msg_pub.data);
    publisher_->publish(msg_pub);
  }
  rclcpp::Subscription<std_msgs::msg::Int8MultiArray>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArraySumTranceiver>());
  rclcpp::shutdown();
  return 0;
}