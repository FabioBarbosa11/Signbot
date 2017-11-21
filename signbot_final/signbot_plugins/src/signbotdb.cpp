#include "signbot_plugins/signbotdb.h"


SignbotDB::SignbotDB(ros::NodeHandle _node) : messageStore(_node)
{


}

std::vector<float> SignbotDB::getposes(std::string _name)
{
  int i;
  std::vector<float> posesarray;
  posesarray.clear();

  std::vector< boost::shared_ptr<std_msgs::Float32MultiArray> > results;
  //Get it back, by default get one
  if(this->messageStore.queryNamed<std_msgs::Float32MultiArray>(_name, results))
  {
    BOOST_FOREACH( boost::shared_ptr<std_msgs::Float32MultiArray> p,  results)
    {
      for(i=0; i<p->data.size(); i++)
      {
        posesarray.push_back(p->data[i]);
      }
/*
        ROS_INFO_STREAM("Got by name: "<< _name<<std::endl<< *p);
        ROS_INFO_STREAM(" size: "<<p->data.size()<<std::endl);

        ROS_INFO_STREAM("----------OUTRA VEZ-----------");
        for(i=0; i<posesarray.size(); i++)
        {
          ROS_INFO_STREAM(posesarray[i]);
        }
*/
        return posesarray;
    }
  }
  else
  {
    posesarray.clear();                 //absurd value, to known that it is a error
    ROS_INFO_STREAM("size when null: "<<posesarray.size());
    return posesarray;
  }

}
