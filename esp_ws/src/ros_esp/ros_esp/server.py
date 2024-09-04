from esp_interface.srv import AuzaGuillermo
import rclpy
from rclpy.node import Node
import requests

class EspServer(Node):

    def __init__(self):
        super().__init__('esp_server')
        self.srv = self.create_service(AuzaGuillermo, 'Led_status', self.state_callback)

    def state_callback(self, request, response):
        if request.state == 1:
            response.message = 'Led On'
            self.send_request('http://192.168.1.91', 'on')
        elif request.state == 0:
            response.message = 'Led Off'
            self.send_request('http://192.168.1.91', 'off')

        self.get_logger().info(f'Request: {request.state}, Response: {response.message}')
        return response

    def send_request(self, url, state):
            response = requests.get(f'{url}/{state}')
            self.get_logger().info(response.text)

def main(args=None):
    rclpy.init(args=args)
    esp_service = EspServer()
    rclpy.spin(esp_service)
    esp_service.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
