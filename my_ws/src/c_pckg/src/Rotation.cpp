#include <cmath>
#include <vector>

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"

using namespace std::chrono_literals;

int main() {
    double s;

    vector<vector<double>> Rotacion_y = {
        {cos(s), 0, sin(s), 0},
        {0, 1, 0, 0},
        {-sin(s), 0, cos(s), 0},
        {0, 0, 0, 1}
    };

    vector<vector<double>> Rotacion_x = {
        {1, 0, 0, 0},
        {0, cos(s), -sin(s), 0},
        {-sin(s), 0, cos(s), 0},
        {0, 0, 0, 1}
    };

    vector<vector<double>> Rotacion_z = {
        {cos(s), -sin(s), 0, 0},
        {sin(s), cos(s), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    double angle_z = 180;
    double angle_x = 90;
    double angle_y = -90;

    s = angle_z * M_PI / 180; // Convert degrees to radians
    vector<vector<double>> Rotacion_z_1 = {
        {cos(s), -sin(s), 0, 0},
        {sin(s), cos(s), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    s = angle_x * M_PI / 180; // Convert degrees to radians
    vector<vector<double>> Rotacion_x_1 = {
        {1, 0, 0, 0},
        {0, cos(s), -sin(s), 0},
        {-sin(s), 0, cos(s), 0},
        {0, 0, 0, 1}
    };

    s = angle_y * M_PI / 180; // Convert degrees to radians
    vector<vector<double>> Rotacion_y_1 = {
        {cos(s), 0, sin(s), 0},
        {0, 1, 0, 0},
        {-sin(s), 0, cos(s), 0},
        {0, 0, 0, 1}
    };

    // Matrix multiplication for Rotacion_Final
    vector<vector<double>> Rotacion_Final(4, vector<double>(4, 0));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                Rotacion_Final[i][j] += Rotacion_z_1[i][k] * Rotacion_x_1[k][j];
            }
        }
    }

    vector<vector<double>> Temp(4, vector<double>(4, 0));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                Temp[i][j] += Rotacion_Final[i][k] * Rotacion_y_1[k][j];
            }
        }
    }

    Rotacion_Final = Temp;

    return 0;
}


class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("Rotation_Publish"), count_(0)
  {
    std_msgs::msg::message = int16MultiArray()
    message.data = "Publishing in Topic-2 count: " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("message_1", 10);
  }

private:
      void topic_callback(const std_msgs::msg::String & msg) const
  {
    std_msgs::msg::Int16MultiArray message;
    message.data.push_back(x);
    message.data.push_back(y);
    message.data.push_back(z);
    RCLCPP_INFO(this->get_logger(), "Publishing: x:%d y:%d z:%d", message.data[0],message.data[1],message.data[2]);
    publisher_->publish(message);
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
