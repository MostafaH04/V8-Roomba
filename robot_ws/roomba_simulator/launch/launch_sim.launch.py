import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource


def generate_launch_description():
    package_name = "roomba_simulator"

    bot_state_pub = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory(package_name),'bot_state_pub.launch.py'
        )]), launch_arguments={'use_sim_time': 'true'}.items()
    )

    gazebo_params_file = os.path.join(get_package_share_directory(package_name),'config','gazebo_params.yaml')

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('gazebo_ros'),'launch', 'gazebo.launch.py')
            ]), launch_arguments={'extra_gazebo_args': '--ros-args --params-file ' + gazebo_params_file}.items()
    )

    spawn_entity = Node(package="gazebo_ros", executable='spawn_entity.py',
                        arguments=['-topic', 'robot_description', '-entity', 'roomba_simulator'],
                        output='screen')
    
    diff_drive_spawner = Node(
        package = "controller_manager", executable = "spawner", arguments = ["diff_cont"]
    )

    joint_broad_spawner = Node(
        package = "controller_manager", executable = "spawner", arguments = ["joint_broad"]
    )

    rviz_launch = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', PathJoinSubstitution([FindPackageShare("roomba_simulator"), "config", "view_robot.rviz"])]
    )

    foxglove_launch_file = PathJoinSubstitution(
        [FindPackageShare('foxglove_bridge'), 'launch', 'foxglove_bridge_launch.xml']
    )

    foxglove_launch = IncludeLaunchDescription(
        XMLLaunchDescriptionSource(foxglove_launch_file)
    )

    return LaunchDescription([
        bot_state_pub,
        gazebo,
        spawn_entity,
        diff_drive_spawner,
        joint_broad_spawner,
        foxglove_launch
    ])