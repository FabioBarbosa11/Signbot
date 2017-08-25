#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"


int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_1pose");
  ros::NodeHandle nh;

  ros::Rate loop_rate(0.5);
  ros::Publisher r_arm_comand_publisher = nh.advertise<trajectory_msgs::JointTrajectory>("/signbot/body_controller/command", 10);
  // Create a message to send.
  trajectory_msgs::JointTrajectory msg;

  // Fill the names of the joints to be controlled.
  // Note that the vacuum_gripper_joint is not controllable.
  msg.joint_names.clear();

  msg.joint_names.push_back("r_shoulder1_joint");
  msg.joint_names.push_back("r_shoulder2_joint");
  msg.joint_names.push_back("r_arm_joint");
  msg.joint_names.push_back("r_elbow1_joint");
  msg.joint_names.push_back("r_elbow2_joint");
  msg.joint_names.push_back("r_wirst1_j");
  msg.joint_names.push_back("r_wirst2_j");
  msg.joint_names.push_back("r_wirst3_j");
  msg.joint_names.push_back("r_bottom_knuckle1_thumb_j");
  msg.joint_names.push_back("r_bottom_knuckle2_thumb_j");
  msg.joint_names.push_back("r_top_knuckle_thumb_j");
  msg.joint_names.push_back("r_bottom_knuckle_index_j");
  msg.joint_names.push_back("r_middle_knuckle_index_j");
  msg.joint_names.push_back("r_top_knuckle_index_j");
  msg.joint_names.push_back("r_bottom_knuckle_middle_j");
  msg.joint_names.push_back("r_middle_knuckle_middle_j");
  msg.joint_names.push_back("r_top_knuckle_middle_j");
  msg.joint_names.push_back("r_bottom_knuckle_third_j");
  msg.joint_names.push_back("r_middle_knuckle_third_j");
  msg.joint_names.push_back("r_top_knuckle_third_j");
  msg.joint_names.push_back("r_bottom_knuckle_little_j");
  msg.joint_names.push_back("r_middle_knuckle_little_j");
  msg.joint_names.push_back("r_top_knuckle_little_j");

  msg.joint_names.push_back("l_shoulder1_joint");
  msg.joint_names.push_back("l_shoulder2_joint");
  msg.joint_names.push_back("l_arm_joint");
  msg.joint_names.push_back("l_elbow1_joint");
  msg.joint_names.push_back("l_elbow2_joint");
  msg.joint_names.push_back("l_wirst1_j");
  msg.joint_names.push_back("l_wirst2_j");
  msg.joint_names.push_back("l_wirst3_j");
  msg.joint_names.push_back("l_bottom_knuckle1_thumb_j");
  msg.joint_names.push_back("l_bottom_knuckle2_thumb_j");
  msg.joint_names.push_back("l_top_knuckle_thumb_j");
  msg.joint_names.push_back("l_bottom_knuckle_index_j");
  msg.joint_names.push_back("l_middle_knuckle_index_j");
  msg.joint_names.push_back("l_top_knuckle_index_j");
  msg.joint_names.push_back("l_bottom_knuckle_middle_j");
  msg.joint_names.push_back("l_middle_knuckle_middle_j");
  msg.joint_names.push_back("l_top_knuckle_middle_j");
  msg.joint_names.push_back("l_bottom_knuckle_third_j");
  msg.joint_names.push_back("l_middle_knuckle_third_j");
  msg.joint_names.push_back("l_top_knuckle_third_j");
  msg.joint_names.push_back("l_bottom_knuckle_little_j");
  msg.joint_names.push_back("l_middle_knuckle_little_j");
  msg.joint_names.push_back("l_top_knuckle_little_j");

  // Create one point in the trajectory.
  msg.points.resize(1);
  // Resize the vector to the same length as the joint names.
  // Values are initialized to 0.
  msg.points[0].positions.resize(msg.joint_names.size(), 1.0);
  msg.points[0].time_from_start = ros::Duration(2.0);
  sleep(10);

  /// Create a JointTrajectory with all positions set to zero, and command the arm.
  if(ros::ok())
  {
    r_arm_comand_publisher.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
    ROS_INFO_STREAM ("\ncommand SENT:\n" << msg);
  }

  ROS_INFO_STREAM("\n\n\t***** SHUTTING DOWN ********\n\n");
  return 0;
}
