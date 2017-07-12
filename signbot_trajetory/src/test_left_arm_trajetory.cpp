/*************************************************
 *  AINDA COM PROBLEMAS!!!!!!!!!!!
 *  O NODO JA PERTENCE AOS GRUPO PUBLISHERS DO TOPICO
 *  MAS AINDA NAO CONSEGUE MANDAR MENSAGEM
 *  MENSAGEM COM ESTRUTRA DIREITA
 * */
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"

using std::string;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "trajectory_test_node");
  ros::NodeHandle nh;
/*
  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std_msgs::String msg;
    msg.data = "hello world";

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }
*/
  /*
  * é so preciso fazer um publish com a mensagem que tera as coordenadas para o /signbot/left_arm/command
  */
  ros::Publisher r_arm_comand_publisher = nh.advertise<trajectory_msgs::JointTrajectory>("/signbot/r_arm_controller/command", 1000);

  /// Create a JointTrajectory with all positions set to zero, and command the arm.
  if(ros::ok())
  {
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
    msg.points[0].positions.resize(msg.joint_names.size(), 1.0);
    // ********************************** dtestar primeiro na shell e depois por os valores aqui **********************
    //msg.points[0].positions[0] = 1.0;
    //msg.points[0].positions[1] = 1.0;
    //msg.points[0].positions[2] = 1.0;
    //msg.points[0].positions[3] = 1.0;
    // How long to take getting to the point (floating point seconds).
    msg.points[0].time_from_start = ros::Duration(0.001);


    ROS_INFO_STREAM ("Sending command:\n" << msg);
    r_arm_comand_publisher.publish(msg);

    ros::spinOnce();

    ros::Duration(3).sleep();
  }

  ROS_INFO_STREAM("***** SHUTTING DOWN ********\n");
  return 0;
}
