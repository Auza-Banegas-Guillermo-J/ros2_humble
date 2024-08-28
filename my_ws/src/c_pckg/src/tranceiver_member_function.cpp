#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class tranceiver : public rclcpp::Node
{
public:
  tranceiver()
  : Node("tranceiver"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("message_2", 10);
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "message_1", 10, std::bind(&tranceiver::topic_callback, this, _1));
    timer_ = this->create_wall_timer(
      2000ms, std::bind(&tranceiver::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Publishing in Topic-2 count: " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
    void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<tranceiver>());
  rclcpp::shutdown();
  return 0;
}