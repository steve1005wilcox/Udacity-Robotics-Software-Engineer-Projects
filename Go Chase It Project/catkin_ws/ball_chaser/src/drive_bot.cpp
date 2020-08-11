#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
#include <std_msgs/Float64.h>

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// Define a /ball_chaser/command_robot service with a handle_drive_request callback function
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
                          ball_chaser::DriveToTarget::Response& res){    
    // Create a motor_command object of type geometry_msgs::Twist
    geometry_msgs::Twist motor_command;
    ROS_INFO("DriveToTargetRequest received - linear_x:%1.2f, angular:%1.2f", (float)req.linear_x, (float)req.angular_z);
    // This function should publish the requested linear x and angular velocities to the robot wheel joints
    motor_command.linear.x = req.linear_x;
    // This function should publish the requested linear x and angular velocities to the robot wheel joints
    motor_command.angular.z = req.angular_z;
    // Publish angles to drive the robot
    motor_command_publisher.publish(motor_command);
    //Robot wait/ sleep time
    ros::Duration().sleep();
    // After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
    res.msg_feedback = "Motor Cmnd Set - linear_x: "+ std::to_string(req.linear_x) + " angular_z: " + std::to_string(req.angular_z);
    ROS_INFO_STREAM(res.msg_feedback);
    return true;
};

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle nh;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // Define a /ball_chaser/command_robot service with a handle_drive_request callback function
    ros::ServiceServer drive_robot_srv = nh.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    ROS_INFO("Ready to send motor commands");

    //Handle ROS communication events
     ros::spin();

    return 0;
}
