import rclpy
from rclpy.node import Node

from std_msgs.msg import Int8MultiArray


class PublisherArray(Node):

    def __init__(self):
        super().__init__('publish_node')
        self.publisher_ = self.create_publisher(Int8MultiArray, 'Auza_array', 10)
        timer_period = 2  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.a = 0; self.b=0; self.c=0;

    def timer_callback(self):
        msg = Int8MultiArray()
        msg.data.append(self.a);
        msg.data.append(self.b);
        msg.data.append(self.c);
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: %d,%d,%d' % (msg.data[0], msg.data[1], msg.data[2]))
        self.a += 1; self.b += 2; self.c -= 1


def main(args=None):
    rclpy.init(args=args)
    my_pub= PublisherArray()
    rclpy.spin(my_pub)
    my_pub.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
