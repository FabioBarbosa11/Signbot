#include "ros/ros.h"

#include "std_msgs/Float32MultiArray.h"
using std_msgs::Float32MultiArray;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_multiarray_msg");
  ros::NodeHandle nh;
  ros::Publisher gesture_pose_pub = nh.advertise<Float32MultiArray>("multiarray", 1000);

  ros::Rate loop_rate(0.2);

  //let's build a 3x3 matrix:
  Float32MultiArray msg;

  msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
  msg.layout.dim.push_back(std_msgs::MultiArrayDimension());

  msg.layout.dim[0].label = "height";
  msg.layout.dim[0].size = 3;
  msg.layout.dim[0].stride = 3*3;

  msg.layout.dim[1].label = "width";
  msg.layout.dim[1].size = 3;
  msg.layout.dim[1].stride = 3;

  msg.layout.data_offset = 0;

  msg.data.push_back(1);
  msg.data.push_back(2);
  msg.data.push_back(3);
  msg.data.push_back(4);
  msg.data.push_back(5);
  msg.data.push_back(6);
  msg.data.push_back(7);
  msg.data.push_back(8);
  msg.data.push_back(9);

  while (ros::ok())
  {
    ROS_INFO_STREAM("\n ola \n");
    gesture_pose_pub.publish(msg);
    //Let the world know
    ROS_INFO("I published something!");

    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}
