import rclpy
from rclpy.node import Node

from std_msgs.msg import String

class tranceiver(Node):

    def __init__(self):
        super().__init__('tranceiver')
        self.publisher_ = self.create_publisher(String, 'message_2', 10)
        timer_period = 3  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

        self.subscription = self.create_subscription(
            String,
            'message_1',
            self.listener_callback,
            10)
        self.subscription

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)

    def timer_callback(self):
        msg = String()
        msg.data = 'tranceiver count : : %d' % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)
    my_tranceiver = tranceiver()
    rclpy.spin(my_tranceiver)
    my_tranceiver.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
