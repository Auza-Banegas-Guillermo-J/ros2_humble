from parcial_interface.srv import Matrix 
import sys
import rclpy
from rclpy.node import Node


class Matrix_Client(Node):

    def __init__(self):
        super().__init__('Matrix_Transofrmation')
        self.cli = self.create_client(AddThreeInts, 'add_three_ints')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = AddThreeInts.Request()        

    def send_request(self):
        self.req.a = int(sys.argv[1])
        self.req.b = int(sys.argv[2])
        self.req.c = int(sys.argv[3])            
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
                    'Result of add_three_ints: for %d + %d + %d = %d' %     
                    (client_transform.req.a, client_transform.req.b, client_transform.req.c, response.sum))
            break

    client_transform.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()