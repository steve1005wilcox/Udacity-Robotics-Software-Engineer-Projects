#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "sensor_msgs/Image.h"
//#include <std_msgs/Float64.h>

//using std::endl;

//Define a global client that can request services
ros::ServiceClient srvClient;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z){

    ROS_INFO("Drive the robot: ");
    
    //Call the drive_bot function and pass velocities to it
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    if (!srvClient.call(srv)){
        ROS_ERROR("Failed to call service DriveToTarget! ");
    }
}

//This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img){

    int white_pixel = 255;
    int step_left = 1 * int(img.step/ 3);
    int step_right = 2 * int(img.step/ 3);
    int step_middle = 3* int(img.step/ 3);
    int right_agg = 0; int mid_agg = 0; int left_agg = 0;
    int tot_agg = 0;

    //Loop through each pixel in the image and check if there's a bright white one
    for (int i = 0; i < img.height; i+=3){
    	for (int j = 0; j < img.step; j++){
            int index = j + (i * img.step);
            //int offset = j * img.step;
            //Then, identify if this pixel falls in the left, mid, or right side of the image
            if (img.data[index + 0] == white_pixel && img.data[index + 1] == white_pixel && img.data[index + 2] == white_pixel){

                if (j <= step_left){
                    left_agg  +=1;
                } else if (j >= step_right){
                    right_agg +=1;
                } else {
                    mid_agg +=1;
                }
            } else{
                continue;
            }
        }
    }
    //Depending on the white ball position, call the drive_bot function and pass velocities to it 
    std::cout << "left_agg: " << left_agg << " ; mid_agg: " << mid_agg << " ; right_agg: " << right_agg << std::endl;
    
    tot_agg = std::max(std::max(left_agg, mid_agg), right_agg);
    //Request a stop when there's no white ball seen by the camera
    if (tot_agg == 0){
        drive_robot(0.0,0.0);
    		
    } else if (tot_agg == left_agg){
        drive_robot(0.1,0.5);
    		
   } else if (tot_agg == right_agg){
        drive_robot (0.55,-0.5);
    		
    } else{
        drive_robot (1.0, 0.0);
    		
    }
    
}
 
int main(int argc, char**argv){

    //Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle nh;

    //Define a client service capable of requesting services from command _robot
    srvClient = nh.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    //Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub = nh.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    //Handle ROS communication events
    ros::spin();
    
    return 0;
}
