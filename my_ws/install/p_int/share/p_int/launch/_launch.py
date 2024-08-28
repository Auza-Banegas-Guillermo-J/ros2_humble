import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='p_int',
            executable='array_talk',),
        launch_ros.actions.Node(
            package='c_int',
            executable='sub_array',),
  ])