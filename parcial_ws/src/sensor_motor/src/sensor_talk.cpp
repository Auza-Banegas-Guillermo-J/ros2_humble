#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cstdint>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8_multi_array.hpp"

using namespace std::chrono_literals;

class Sensor_Inform : public rclcpp::Node
{
public:
  Sensor_Inform() : Node("Sensor_Inform")
  {
    publisher_ = this->create_publisher<std_msgs::msg::Int8MultiArray>("Sensor_Values", 10);
    timer_ = this->create_wall_timer(
      3000ms, std::bind(&Sensor_Inform::timer_callback, this));
  }

private:
  void timer_callback()
  {
    std_msgs::msg::Int8MultiArray message;
    const uint8_t n=3;
    int value = count_;

    for (int i = 0; i < n; i++)
    {
      int bit = (value >> (n - 1 - i)) & 1;
      message.data.push_back(bit);
    }
    RCLCPP_INFO(this->get_logger(), 
    "\nSensor Data: S1: %d S2: %d S3: %d \nCounter: %d", message.data[0], message.data[1], message.data[2],value);
    publisher_->publish(message);
    count_++;
    if (count_ >= (1 << n))
    {
      count_ = 0;
    }
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Int8MultiArray>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Sensor_Inform>());
  rclcpp::shutdown();
  return 0;
}
