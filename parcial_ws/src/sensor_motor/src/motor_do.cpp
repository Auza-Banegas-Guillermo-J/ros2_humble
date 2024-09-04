
#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int8_multi_array.hpp"

using std::placeholders::_1;

class Spin_Motors : public rclcpp::Node
{
public:
  Spin_Motors()
  : Node("Spin_Motors")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int8MultiArray>(
      "Sensor_Values", 10, std::bind(&Spin_Motors::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::Int8MultiArray & msg) const
  {
    int direction = 0,md=0,mi=0;
    std::string sentido="";
    for (size_t i = 0; i < msg.data.size(); ++i) {
      direction |= (msg.data[i] << (msg.data.size() - 1 - i));
    }
    switch(direction){
        case 0:
            md = 1; mi= 1;
            sentido = "Forward";
            break;
        case 1:
            md = 0; mi= 1;
            sentido = "Left";
            break;
        case 2:
            md = 0; mi= 0;
            sentido = "Stop";
            break;
        case 3:
            md = 0; mi= 1;
            sentido = "Left";
            break;
        case 4:
            md = 1; mi= 0;
            sentido = "Right";
            break;
        case 5:
            md = 1; mi= 1;
            sentido = "Forward";
            break;
        case 6:
            md = 1; mi= 0;
            sentido = "Right";
            break;
        case 7:
            md = 0; mi= 0;
            sentido = "Stop";
            break;
    }
    RCLCPP_INFO(this->get_logger(), 
    "\nSensor Values: S1: %d S2: %d S3: %d\nLeft Motor: %d Right Motor: %d\nMoving: %s",
     msg.data[0],msg.data[1],msg.data[2],mi,md,sentido.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::Int8MultiArray>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Spin_Motors>());
  rclcpp::shutdown();
  return 0;
}
