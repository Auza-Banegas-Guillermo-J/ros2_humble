from parcial_interface.srv import Matrix                                                           # CHANGE

import rclpy
from rclpy.node import Node


class Matrix_Service(Node):

    def __init__(self):
        super().__init__('Matrix_Transofrmation_Server')
        self.srv = self.create_service(Matrix, 'matrix_transform', self.matrix_callback)       # CHANGE

    def matrix_callback(self, request, response):
        #response.sum = request.a + request.b + request.c                                                   # CHANGE
        self.get_logger().info('Incoming request\nalpha: %.3f b: %.3f c: %.3f' % (request.alpha, request.beta, request.gamma))  # CHANGE

        return response

def main(args=None):
    rclpy.init(args=args)

    serve_matrix= Matrix_Service()

    rclpy.spin(serve_matrix)

    rclpy.shutdown()

if __name__ == '__main__':
    main()