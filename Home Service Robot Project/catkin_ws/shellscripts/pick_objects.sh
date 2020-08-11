#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/worlds/my_world.world  " &
#xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 3
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/turtlebot_simulator/turtlebot_gazebo/maps/world.yaml " &
#xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 3
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 3
xterm  -e  " rosrun pick_objects pick_objects "