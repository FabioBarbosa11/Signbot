#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"

#define MAX_JOINTS 46
//vector com as coordenadas default(braços em baixo)
float default_pose[MAX_JOINTS] = { 1.57, 1.5, 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,

                                 1.57, -1.5, 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0};
float leter_b[MAX_JOINTS] = {
                              0.52, 1.19, -0.09, -0.16, 1.57,
                              0.27, 0, 0.3,
                              0, 0, 0,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,

                              1.57, -1.5, 0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0
                            };

float bom_dia[2][MAX_JOINTS] =
{
  {
    0.52, 1.19, -0.09, -0.16, 1.57,
    0.27, 0, 0.3,
    0, 0, 0,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
   0.59, 1.41, -0.23, -1.34, 1.57,
    0, -0.22, 0.35,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  }
};

float ajudar[2][MAX_JOINTS] =
{
  {
    0, 0.78, 0.6, -0.15,
    0, -0.3, -0.67,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    0, -0.84, -0.72, -0.24, -1.57,
    0, 0.29, 0.79,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    0, 1.41, 0.61, -0.51, 0.7,
    0, -0.37, -0.4,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    0, -1.49, -0.69, -0.8, -0.81,
    0, 0.09, 0.48,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  }
};

void prepare_message(trajectory_msgs::JointTrajectory& _message)
{
  // Fill the names of the joints to be controlled.
  // Note that the vacuum_gripper_joint is not controllable.
  _message.joint_names.clear();

  _message.joint_names.push_back("r_shoulder1_joint");
  _message.joint_names.push_back("r_shoulder2_joint");
  _message.joint_names.push_back("r_arm_joint");
  _message.joint_names.push_back("r_elbow1_joint");
  _message.joint_names.push_back("r_elbow2_joint");
  _message.joint_names.push_back("r_wirst1_j");
  _message.joint_names.push_back("r_wirst2_j");
  _message.joint_names.push_back("r_wirst3_j");
  _message.joint_names.push_back("r_bottom_knuckle1_thumb_j");
  _message.joint_names.push_back("r_bottom_knuckle2_thumb_j");
  _message.joint_names.push_back("r_top_knuckle_thumb_j");
  _message.joint_names.push_back("r_bottom_knuckle_index_j");
  _message.joint_names.push_back("r_middle_knuckle_index_j");
  _message.joint_names.push_back("r_top_knuckle_index_j");
  _message.joint_names.push_back("r_bottom_knuckle_middle_j");
  _message.joint_names.push_back("r_middle_knuckle_middle_j");
  _message.joint_names.push_back("r_top_knuckle_middle_j");
  _message.joint_names.push_back("r_bottom_knuckle_third_j");
  _message.joint_names.push_back("r_middle_knuckle_third_j");
  _message.joint_names.push_back("r_top_knuckle_third_j");
  _message.joint_names.push_back("r_bottom_knuckle_little_j");
  _message.joint_names.push_back("r_middle_knuckle_little_j");
  _message.joint_names.push_back("r_top_knuckle_little_j");

  _message.joint_names.push_back("l_shoulder1_joint");
  _message.joint_names.push_back("l_shoulder2_joint");
  _message.joint_names.push_back("l_arm_joint");
  _message.joint_names.push_back("l_elbow1_joint");
  _message.joint_names.push_back("l_elbow2_joint");
  _message.joint_names.push_back("l_wirst1_j");
  _message.joint_names.push_back("l_wirst2_j");
  _message.joint_names.push_back("l_wirst3_j");
  _message.joint_names.push_back("l_bottom_knuckle1_thumb_j");
  _message.joint_names.push_back("l_bottom_knuckle2_thumb_j");
  _message.joint_names.push_back("l_top_knuckle_thumb_j");
  _message.joint_names.push_back("l_bottom_knuckle_index_j");
  _message.joint_names.push_back("l_middle_knuckle_index_j");
  _message.joint_names.push_back("l_top_knuckle_index_j");
  _message.joint_names.push_back("l_bottom_knuckle_middle_j");
  _message.joint_names.push_back("l_middle_knuckle_middle_j");
  _message.joint_names.push_back("l_top_knuckle_middle_j");
  _message.joint_names.push_back("l_bottom_knuckle_third_j");
  _message.joint_names.push_back("l_middle_knuckle_third_j");
  _message.joint_names.push_back("l_top_knuckle_third_j");
  _message.joint_names.push_back("l_bottom_knuckle_little_j");
  _message.joint_names.push_back("l_middle_knuckle_little_j");
  _message.joint_names.push_back("l_top_knuckle_little_j");
}

void insert_jointvalues(trajectory_msgs::JointTrajectory& _message)
{
  int i=0;
  // Create one point in the trajectory.
  _message.points.resize(3);
  // Resize the vector to the same length as the joint names.
  // Values are initialized to 0.
  _message.points[0].positions.resize(_message.joint_names.size());
  _message.points[1].positions.resize(_message.joint_names.size());
  _message.points[2].positions.resize(_message.joint_names.size());

  for(i=0; i<MAX_JOINTS; i++)
  {
        _message.points[0].positions[i] = bom_dia[0][i];
        _message.points[1].positions[i] = bom_dia[0][i];
        _message.points[2].positions[i] = bom_dia[1][i];
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "signbot_2poses");
  ros::NodeHandle nh;

  ros::Rate loop_rate(0.5);

  ros::Publisher r_arm_comand_publisher = nh.advertise<trajectory_msgs::JointTrajectory>("/signbot/body_controller/command", 10);
  // Create a message to send.
  trajectory_msgs::JointTrajectory message;
  //increment the joints
  prepare_message(message);
  //insert the angle  value for which joint
  insert_jointvalues(message);
  message.points[0].time_from_start = ros::Duration(2.0);
  message.points[1].time_from_start = ros::Duration(4.0);
  message.points[2].time_from_start = ros::Duration(6.0);

  if(ros::ok())
  {
    sleep(5);
    ROS_INFO_STREAM("\n\t2 subscibers listening \n number of subs:" << r_arm_comand_publisher.getNumSubscribers()<<"\n");

    r_arm_comand_publisher.publish(message);

    ros::spinOnce();
    loop_rate.sleep();
    ROS_INFO_STREAM ("\ncommand SENT:\n" << message);
  }

  ROS_INFO_STREAM("\n\n\t***** SHUTTING DOWN ********\n\n");
  return 0;
}
