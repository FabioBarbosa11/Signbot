#include <signbot_plugins/classtranslator.h>

#include <string>
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "signbot_core");
  ros::NodeHandle nh;

  if(ros::ok())
  {
    ROS_INFO_STREAM("\nSetting up. Wait a moment...");
    MyTranslator myTranslator(nh);

    ros::spin();
  }

  ROS_INFO_STREAM("\n\t***** SHUTTING DOWN ********\n");
  return 0;
}
