import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='c_pckg',
            executable='talker',
            name='talk_test'),
        launch_ros.actions.Node(
            package='c_pckg',
            executable='tranceiver',
            name='tranceive_test'),
        launch_ros.actions.Node(
            package='c_pckg',
            executable='listener',
            name='listen_test'),
  ])
