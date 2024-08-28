#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8_multi_array.hpp"

using namespace std::chrono_literals;

class ArrayPublisher : public rclcpp::Node
{
public:
  ArrayPublisher() : Node("ArrayPublisher")
  {
    publisher_ = this->create_publisher<std_msgs::msg::Int8MultiArray>("Auza_array", 10);
    timer_ = this->create_wall_timer(
      1500ms, std::bind(&ArrayPublisher::timer_callback, this));
  }
  int a=0,b=0,c=0;

private:
  void timer_callback()
  {
    std_msgs::msg::Int8MultiArray message;
    a++;
    c++;
    message.data.push_back(a);
    message.data.push_back(b);
    message.data.push_back(c);
    RCLCPP_INFO(this->get_logger(), "Publishing: a:%s b:%s c:%s", std::to_string(a).c_str(), std::to_string(b).c_str(), std::to_string(c).c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Int8MultiArray>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArrayPublisher>());
  rclcpp::shutdown();
  return 0;
}
