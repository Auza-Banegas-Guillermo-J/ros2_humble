import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='p_msg',
            executable='talker',
            name='talker'),
        launch_ros.actions.Node(
            package='p_msg',
            executable='tranceiver',
            name='tranceiver'),
        launch_ros.actions.Node(
            package='p_msg',
            executable='listener',
            name='listener'),
  ])