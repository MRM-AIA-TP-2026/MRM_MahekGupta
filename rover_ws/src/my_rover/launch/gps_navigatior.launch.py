from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_share = get_package_share_directory('my_rover')
    
    
    gps = Node(
        package="my_rover",
        executable="gps_navigation",
        name="gps_navigation",
        output='screen',
        parameters=[{'use_sim_time': True}],
        arguments=['--ros-args', '--log-level', 'info']

    )
    
    return LaunchDescription([
        gps
    ])