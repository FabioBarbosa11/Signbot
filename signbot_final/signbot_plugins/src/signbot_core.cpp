#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"

#include "std_msgs/String.h"

#define MAX_JOINTS 46

class Phrase_resender
{
  private:
   ros::Publisher word_LP_pub_;

  public:
    Phrase_resender(const ros::Publisher& _word_LP_pub)
      : word_LP_pub_(_word_LP_pub)
    {

    }

    void phrase_LPCallback(const std_msgs::String::ConstPtr& _msg)
    {
      ROS_INFO_STREAM("\n *1* I heard: "<<_msg->data.c_str()<<"\n");
      send_to_database(_msg);
    }

    void send_to_database(const std_msgs::String::ConstPtr& _msg)
    {
      word_LP_pub_.publish(*_msg);
    }

};

void word_LGPCallBack(const std_msgs::String::ConstPtr& _msg)
{
  ROS_INFO_STREAM("\n *2* I heard: "<<_msg->data.c_str()<<"\n");
}

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
 /* int i=0;
  // Create one point in the trajectory.
  _message.points.resize(1);
  // Resize the vector to the same length as the joint names.
  // Values are initialized to 0.
  //_message.points[0].positions.resize(_message.joint_names.size(), 1.0);
  _message.points[0].positions.resize(_message.joint_names.size());
  for(i=0; i<MAX_JOINTS; i++)
  {
        _message.points[0].positions[i] = default_pose[i];
                                          //leter_b[i];
                                          //ajudar[0][i];
  }
  _message.points[0].time_from_start = ros::Duration(2.0);
*/
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "signbot_core");
  ros::NodeHandle nh;
  ros::Rate loop_rate(0.5);

  //Publisher para buscar os gestos na base de dados
  ros::Publisher word_LP_pub = nh.advertise<std_msgs::String>("wordLP", 10);
  Phrase_resender resend_phrase(word_LP_pub);
  //Subscriber para ouvir a frase em LP
  ros::Subscriber phrase_LP_sub = nh.subscribe("phraseLP",10, &Phrase_resender::phrase_LPCallback, &resend_phrase);
  ros::Subscriber word_LGP_sub = nh.subscribe("wordLGP",10, word_LGPCallBack);
  //Publisher para publicar ao modelo os angulos para gesto em LGP
  //ros::Publisher r_arm_comand_publisher = nh.advertise<trajectory_msgs::JointTrajectory>("/signbot/body_controller/command", 10);
  /*
  // Create a message to send.
  trajectory_msgs::JointTrajectory message;
  //increment the joints
  prepare_message(message);
  //insert the angle  value for which joint
  insert_jointvalues(message);
*/

  /*  other method of waiting
   * while(r_arm_comand_publisher.getNumSubscribers() != 1)
  {
    ROS_INFO_STREAM("\n\tWaiting for subscibers\n number of subs:"<<r_arm_comand_publisher.getNumSubscribers()<<"\n");
    sleep(5);
  }*/
  sleep(10);
  ROS_INFO_STREAM("\nProgram is ready to execute\n");

  if(ros::ok())
  {
/*    r_arm_comand_publisher.publish(message);

    ros::spinOnce();
    loop_rate.sleep();
    ROS_INFO_STREAM ("\ncommand SENT:\n" << message);
    */
    ros::spin();
  }

  ROS_INFO_STREAM("\n\t***** SHUTTING DOWN ********\n");
  return 0;
}
