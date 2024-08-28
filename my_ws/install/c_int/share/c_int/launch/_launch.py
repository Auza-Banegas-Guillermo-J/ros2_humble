import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='c_int',
            executable='pub_array',
            name='publish_3D_array'),
        launch_ros.actions.Node(
            package='c_int',
            executable='sub_array',
            name='subscribe_3D_array'),
  ])
