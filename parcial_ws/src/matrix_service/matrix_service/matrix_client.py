from parcial_interface.srv import Matrix 
import sys
import rclpy
from rclpy.node import Node


class Matrix_Client(Node):

    def __init__(self):
        super().__init__('Matrix_Transofrmation_Client')
        self.cli = self.create_client(Matrix, 'matrix_transform')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Service unavailable')
        self.req = Matrix.Request()

    def send_request(self):          
        self.future = self.cli.call_async(self.req)


def main(args=None):
    rclpy.init(args=args)

    client_transform = Matrix_Client()
    client_transform.send_request()

    while rclpy.ok():
        rclpy.spin_once(client_transform)
        if client_transform.future.done():
            try:
                response = client_transform.future.result()
            except Exception as e:
                client_transform.get_logger().info(
                    'Service call failed %r' % (e,))
            else:
                client_transform.get_logger().info(
                    'Resulting axis positions x: %.3f y: %.3f z: %.3f' %     
                    (response.x, response.y, response.z))
            break

    client_transform.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()