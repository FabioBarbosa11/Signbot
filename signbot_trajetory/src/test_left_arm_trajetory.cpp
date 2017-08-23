#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "trajectory_test_node");
  ros::NodeHandle nh;

  ros::Rate loop_rate(0.5);
  ros::Publisher r_arm_comand_publisher = nh.advertise<trajectory_msgs::JointTrajectory>("/signbot/r_arm_controller/command", 1000);

  // Create a message to send.
  trajectory_msgs::JointTrajectory msg;

  // Fill the names of the joints to be controlled.
  // Note that the vacuum_gripper_joint is not controllable.
  msg.joint_names.clear();
  msg.joint_names.push_back("r_shoulder_joint");
  msg.joint_names.push_back("r_top_arm_joint");
  msg.joint_names.push_back("r_elbow_joint");
  msg.joint_names.push_back("r_wrist_joint");
  // Create one point in the trajectory.
  msg.points.resize(1);
  // Resize the vector to the same length as the joint names.
  // Values are initialized to 0.
  msg.points[0].positions.resize(msg.joint_names.size(), 0.0);
  msg.points[0].time_from_start = ros::Duration(2.0);


  if(ros::ok())
  {
    sleep(5);
    ROS_INFO_STREAM("\n\t2 subscibers listening \n number of subs:" << r_arm_comand_publisher.getNumSubscribers()<<"\n");

    r_arm_comand_publisher.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
    ROS_INFO_STREAM ("\ncommand SENT:\n" << msg);
  }
  loop_rate.sleep();
  ROS_INFO_STREAM("\n\n\t***** SHUTTING DOWN ********\n\n");
  return 0;
}
