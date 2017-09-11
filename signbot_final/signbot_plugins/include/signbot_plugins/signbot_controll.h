#ifndef _SIGNBOT_CONTROLL_
#define _SIGNBOT_CONTROLL_

#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"

#define MAX_JOINTS 46

class SignbotController
{
private:
 ros::Publisher body_controll_pub;     //topic which will control the model in gazebo
 trajectory_msgs::JointTrajectory _message;
 float duration;

 void insert_jointnames();

 void publish();
public:

 void establish_pub(ros::NodeHandle n);

 void register_positions(float pos[][MAX_JOINTS], int  num_poses);

 void pub_default_pose(float pos[][MAX_JOINTS]);
};


#endif
