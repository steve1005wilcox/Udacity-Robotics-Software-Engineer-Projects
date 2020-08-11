The Home Service Robot project is a project to simulate a robot that is capable picking up and delivering virtual objects by autonomous navigation.

The first step  was to use an existing Gazebo environment to carry out the following:
1 Teleoperate the robot and test SLAM.
2 Use the ROS navigation stack to send manual commands to the robot using the Rviz 2D Nav Goal button in rviz to move to different locations.
3 Write a pick_objects node that commands your robot to move to the desired pickup and drop off zones.
4 Write an add_markers node that subscribes to the robot odometry, keeps track of your robot pose, and publishes markers to rviz.


Install Packages
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/src
$ catkin_init_workspace
$ cd ..
$ catkin_make
$ sudo apt-get update
$ cd ~/catkin_ws/src
$ git clone https://github.com/ros-perception/slam_gmapping.git
$ git clone https://github.com/turtlebot/turtlebot.git
$ git clone https://github.com/turtlebot/turtlebot_interactions.git
$ git clone https://github.com/turtlebot/turtlebot_simulator.git
$ git clone https://github.com/ros-perception/openslam_gmapping.git
$ cd ~/catkin_ws/
$ source devel/setup.bash
$ rosdep -i install gmapping
$ rosdep -i install turtlebot_teleop
$ rosdep -i install turtlebot_rviz_launchers
$ rosdep -i install turtlebot_gazebo
$ catkin_make
$ source devel/setup.bash

ROS Packages/Nodes
rosmake move_base

Shell Script Install and Permissions
$ sudo apt-get install xterm
$ cd /home/workspace/catkin_ws/ShellScripts
$ chmod +x home_service.sh
$ chmod +x add_markers.sh
$ chmod +x pick_objects.sh

To Run the XTerms
$ ./home_service.sh
$ ./add_markers.sh
$ ./pick_objects.sh