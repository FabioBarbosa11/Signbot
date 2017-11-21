#include "ros/ros.h"
#include "mongodb_store/message_store.h"
#include <boost/foreach.hpp>
#include "std_msgs/Float32MultiArray.h"

#include <sstream>
#include <cassert>


using namespace mongodb_store;
using namespace std;
using namespace std_msgs;


void search_db(MessageStoreProxy _ms, string _name)
{
  //This is the message we want to store
  string name(_name);
  Float32MultiArray poses;

  vector< boost::shared_ptr<Float32MultiArray> > results;
  //Get it back, by default get one
  if(_ms.queryNamed<Float32MultiArray>(name, results)) {

    BOOST_FOREACH( boost::shared_ptr<Float32MultiArray> p,  results)
    {
      ROS_INFO_STREAM("Got by name: "<< _name<<endl<< *p);
      ROS_INFO_STREAM(" size: "<<p->data.size()<<endl);
    }
  }

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "read_db");
  ros::NodeHandle nh;

  //Create object which does the work for us.
  MessageStoreProxy messageStore(nh);
  search_db(messageStore, "default_pose");
  search_db(messageStore, "b");
  search_db(messageStore, "bom dia");
  search_db(messageStore, "ajudar");
  search_db(messageStore, "eu");
  search_db(messageStore, "posso");

  return 0;
}
