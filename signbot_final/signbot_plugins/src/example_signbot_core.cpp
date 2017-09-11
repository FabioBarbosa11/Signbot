#include "ros/ros.h"
#include "trajectory_msgs/JointTrajectory.h"

#include "std_msgs/String.h"

#include "signbot_plugins/gestureInformation.h"
using signbot_plugins::gestureInformation;

#include <vector>
using std::vector;

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

void gesture_LGPCallBack(const gestureInformation::ConstPtr& _gesture)
{
  ROS_INFO_STREAM("\n I heard: "<<*_gesture<<"\n");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_signbot_core");
  ros::NodeHandle nh;

  //Publisher para buscar os gestos na base de dados
  ros::Publisher word_LP_pub = nh.advertise<std_msgs::String>("word_LP", 10);
  Phrase_resender resend_phrase(word_LP_pub);
  //Subscriber para ouvir a frase em LP
  ros::Subscriber phrase_LP_sub = nh.subscribe("phraseLP",10, &Phrase_resender::phrase_LPCallback, &resend_phrase);
  ros::Subscriber gesture_LGP_sub = nh.subscribe("gestureInfo_LGP",10, gesture_LGPCallBack);

  sleep(10);

  ROS_INFO_STREAM("\nProgram is ready to execute\n");

  if(ros::ok())
  {
    ros::spin();
  }

  ROS_INFO_STREAM("\n\t***** SHUTTING DOWN ********\n");
  return 0;
}
