from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    pkg_share = get_package_share_directory('my_rover')
    
    # Include the Gazebo launch file
    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_share, 'launch', 'gazebo.launch.py')
        )
    )
    
    # Include the RViz launch file
    rviz_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_share, 'launch', 'display.launch.py')
        )
    )
    

   
    
    # Add a static transform publisher for the `map -> odom` frame
    static_transform_publisher = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="static_odom_tf_broadcaster",
        arguments=["0", "0", "0", "0", "0", "0", "map", "odom"],
        parameters=[{'use_sim_time': True}],

    )

    gps = Node(
        package="my_rover",
        executable="gps_navigation",
        name="gps_navigation",
        parameters=[{'use_sim_time': True}],
        arguments=['--ros-args', '--log-level', 'info'],
        prefix='gnome-terminal -- bash -c'
    )
    
    return LaunchDescription([
        gazebo_launch,
        rviz_launch,
        static_transform_publisher,
        gps
    ])