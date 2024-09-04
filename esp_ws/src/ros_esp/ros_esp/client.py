from esp_interface.srv import AuzaGuillermo
import sys
import rclpy
from rclpy.node import Node


class EspClient(Node):

    def __init__(self):
        super().__init__('esp_client')
        self.cli = self.create_client(AuzaGuillermo, 'Led_status')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Service Unavailable')
        self.req = AuzaGuillermo.Request()

    def client_request(self):
        try:
            value = int(sys.argv[1])
            if value not in [0, 1]:
                raise ValueError
        except ValueError:
            self.get_logger().error('Input must be 1 or 0')
            sys.exit(1)

        self.req.state = value
        self.future = self.cli.call_async(self.req)

        rclpy.spin_until_future_complete(self, self.future)
        if self.future.result() is not None:
            self.get_logger().info('Request Processed Successfully')
        else:
            self.get_logger().error('Request Processed Unsuccessfully')

        self.destroy_node()
        rclpy.shutdown()


def main(args=None):
    rclpy.init(args=args)
    esp_client = EspClient()
    esp_client.client_request()


if __name__ == '__main__':
    main()
