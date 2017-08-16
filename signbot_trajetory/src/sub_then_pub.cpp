#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"

class Classola
{
public:

  Classola()
  {}

  Classola(const ros::Publisher& joint_trajectory_pub)
    : joint_trajectory_publisher_(joint_trajectory_pub)
  {
  }

  void trajetoryCallback(const trajectory_msgs::JointTrajectory::ConstPtr& msg)
  {
    ROS_INFO_STREAM ("Receive command:\n" << *msg);
    send_arm_to_zero_state(msg);
  }

  /// Create a JointTrajectory with all positions set to zero, and command the arm.
  void send_arm_to_zero_state(const trajectory_msgs::JointTrajectory::ConstPtr& msg)
  {
    ROS_INFO_STREAM ("Sending command:\n" << *msg);
    joint_trajectory_publisher_.publish(*msg);
  }

private:
   ros::Publisher joint_trajectory_publisher_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sub_then_pub");
  ros::NodeHandle nh;

  ros::Publisher joint_trajectory_pub = nh.advertise<trajectory_msgs::JointTrajectory>("/signbot/r_arm_controller/command", 10);
  Classola ola(joint_trajectory_pub);
  ros::Subscriber sub = nh.subscribe("/signbot/r_arm_controller/command", 1000, &Classola::trajetoryCallback, &ola);

  ros::spin();

  return 0;
}
