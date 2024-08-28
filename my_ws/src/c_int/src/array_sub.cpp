
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8_multi_array.hpp"

using std::placeholders::_1;

class ArraySuscriber : public rclcpp::Node
{
public:
  ArraySuscriber()
  : Node("ArraySuscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int8MultiArray>(
      "Auza_array", 10, std::bind(&ArraySuscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::Int8MultiArray & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: a:%d b:%d c:%d", msg.data[0],msg.data[1],msg.data[2]);
  }
  rclcpp::Subscription<std_msgs::msg::Int8MultiArray>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArraySuscriber>());
  rclcpp::shutdown();
  return 0;
}
