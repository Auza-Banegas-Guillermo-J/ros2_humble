import rclpy
from rclpy.node import Node

from std_msgs.msg import Int8MultiArray


class ArraySuscriber(Node):

    def __init__(self):
        super().__init__('Array_Suscriber_Node')
        self.subscription = self.create_subscription(
            Int8MultiArray,
            'Auza_array',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('I heard: %d,%d,%d' % (msg.data[0],msg.data[1],msg.data[2]))


def main(args=None):
    rclpy.init(args=args)
    my_sub = ArraySuscriber()
    rclpy.spin(my_sub)
    my_sub.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
