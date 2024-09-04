from parcial_interface.srv import Matrix                                                           
import sympy as sp
import rclpy
from rclpy.node import Node

class Matrix_Service(Node):

    def __init__(self):
        super().__init__('Matrix_Transofrmation_Server')
        self.srv = self.create_service(Matrix, 'matrix_transform', self.matrix_callback)
        self.angles=[20.0,45.0,10.0]
            
    def matrix_callback(self, request, response):
        self.get_logger().info('Incoming request\nalpha: %.3f beta: %.3f gamma: %.3f' % (self.angles[0], self.angles[1], self.angles[2]))
        alpha, beta, gamma, l1, l2 = sp.symbols('alpha beta gamma l1 l2')

        Ry1 = sp.Matrix([
            [sp.cos(-beta), 0, sp.sin(-beta), 0],
            [0, 1, 0, 0],
            [-sp.sin(-beta), 0, sp.cos(-beta), 0],
            [0, 0, 0, 1]
        ])

        Rx1 = sp.Matrix([
            [1, 0, 0, 0],
            [0, sp.cos(alpha), -sp.sin(alpha), 0],
            [0, sp.sin(alpha), sp.cos(alpha), 0],
            [0, 0, 0, 1]
        ])

        Tz1 = sp.Matrix([
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, -l1],
            [0, 0, 0, 1]
        ])

        Ry2 = sp.Matrix([
            [sp.cos(-gamma), 0, sp.sin(-gamma), 0],
            [0, 1, 0, 0],
            [-sp.sin(-gamma), 0, sp.cos(-gamma), 0],
            [0, 0, 0, 1]
        ])

        Tz2 = sp.Matrix([
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, -l2],
            [0, 0, 0, 1]
        ])

        M = Rx1 * Ry1 * Tz1 * Ry2 * Tz2

        M_simplified = sp.simplify(M * sp.Matrix([0, 0, 0, 1]))

        # Sustituir valores numéricos
        M_numeric = M_simplified.subs({
            alpha: (self.angles[0]*0.01745),
            beta: (self.angles[1]*0.01745),
            gamma: (self.angles[2]*0.01745),
            l1: float(69.5),
            l2: float(71.5),
        })

        x = M_numeric[0].evalf()
        y = M_numeric[1].evalf()
        z = M_numeric[2].evalf()

        self.get_logger().info(f"Calculated Positions:\n x:{x} y: {y} z: {z}")

        response.x = float(x)
        response.y = float(y)
        response.z = float(z)

        return response

def main(args=None):
    rclpy.init(args=args)

    serve_matrix= Matrix_Service()

    rclpy.spin(serve_matrix)

    rclpy.shutdown()

if __name__ == '__main__':
    main()