#ifndef _CLASS_TRANSLATOR_
#define _CLASS_TRANSLATOR_

#include "signbot_plugins/signbot_controll.h"
#include <signbot_plugins/gesture_info.h>

#include "std_msgs/String.h"

class MyTranslator
{
private:
 ros::Subscriber phrase_PL_sub;     //Subscriber to listen the phrase in PL
 SignbotController sc;              //class that controls the model in gaebo

  int send_defaultpose();
public:
 MyTranslator(ros::NodeHandle _node);

 void phrase_PLCallback(const std_msgs::String::ConstPtr& _phrase);
 int trans_pub(const std_msgs::String::ConstPtr& _phrase);

};

#endif
