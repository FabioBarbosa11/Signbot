/**
 *  Lets try see read some data from database.
 *    For this, lets follow the data from the example of mongodb_store
 */

#include "ros/ros.h"
#include "mongodb_store/message_store.h"
#include <boost/foreach.hpp>
#include "std_msgs/Float32MultiArray.h"

#include <sstream>
#include <cassert>

#include <signbot_db/gesture_info.h>

using namespace mongodb_store;
using namespace std;
using namespace std_msgs;

Float32MultiArray fill_array(string _name)
{
  Float32MultiArray poses;
  int i=0, j=0;

  if(_name=="default_pose")
  {
    for(i=0; i<MAX_JOINTS; i++)
    {
      poses.data.push_back(default_pose[0][i]);
    }
  }
  else
  {
    if(_name=="b")
    {
      for(i=0; i<MAX_JOINTS; i++)
      {
        poses.data.push_back(letter_b[0][i]);
      }
    }
    else
    {
      if(_name=="bom dia")
      {
        for(j=0;j<3; j++)
        {
          for(i=0; i<MAX_JOINTS; i++)
          {
           poses.data.push_back(bom_dia[j][i]);
          }
        }
      }
      else
      {
        if(_name=="eu")
        {
          for(i=0; i<MAX_JOINTS; i++)
          {
            poses.data.push_back(eu[0][i]);
          }
        }
        else
        {
          if(_name=="posso")
          {
            for(j=0;j<2; j++)
            {
              for(i=0; i<MAX_JOINTS; i++)
              {
               poses.data.push_back(posso[j][i]);
              }
            }
          }
          else  //ajudar
          {
            for(j=0;j<2; j++)
            {
              for(i=0; i<MAX_JOINTS; i++)
              {
               poses.data.push_back(ajudar[j][i]);
              }
            }
          }
        }
      }
    }
  }

  return poses;
}

void insert_db(MessageStoreProxy _ms, string _name)
{
  string name(_name);
  Float32MultiArray poses;

  poses = fill_array(_name);

  string id(_ms.insertNamed(name, poses));

  ROS_INFO_STREAM("CREATED: Name: " <<name<<"id: "<<id<<endl);

  vector< boost::shared_ptr<Float32MultiArray> > results;
  if(_ms.queryNamed<Float32MultiArray>(name, results)) {

    BOOST_FOREACH( boost::shared_ptr<Float32MultiArray> p,  results)
    {
      ROS_INFO_STREAM("Got by name: " << *p);
      ROS_INFO_STREAM(" size: "<<p->data.size()<<endl);
    }
  }
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "create_db");
  ros::NodeHandle nh;

  //Create object which does the work for us.
  MessageStoreProxy messageStore(nh);
//  -----------------------  default_pose ---------------------
  insert_db(messageStore, "default_pose");
  /*
  //This is the message we want to store
  string name("default_pose");
  Float32MultiArray poses;

  for(int i=0; i<MAX_JOINTS; i++)
  {
    poses.data.push_back(default_pose[0][i]);
  }

  string id(messageStore.insertNamed(name, poses));

  ROS_INFO_STREAM("CREATED: Name: " <<name<<"id: "<<id<<endl);

  vector< boost::shared_ptr<Float32MultiArray> > results;
  if(messageStore.queryNamed<Float32MultiArray>(name, results)) {

    BOOST_FOREACH( boost::shared_ptr<Float32MultiArray> p,  results)
    {
      ROS_INFO_STREAM("Got by name: " << *p);
    }
  }
*/
// ----------------------------------- letter_b --------------------------------------------
  insert_db(messageStore, "b");
  /*
  //This is the message we want to store
  name.clear();
  name.push_back('b');

  poses.data.clear();

  for(int i=0; i<MAX_JOINTS; i++)
  {
    poses.data.push_back(letter_b[0][i]);
  }

  string id_b(messageStore.insertNamed(name, poses));

  ROS_INFO_STREAM("CREATED: Name: " <<name<<"id_b: "<<id_b<<endl);

    vector< boost::shared_ptr<Float32MultiArray> > results;

    if(messageStore.queryNamed<Float32MultiArray>(name, results)) {

      BOOST_FOREACH( boost::shared_ptr<Float32MultiArray> p,  results)
      {
        ROS_INFO_STREAM("Got by name: " << *p);
      }
    }
*/
  // ----------------------------------- bom dia --------------------------------------------
  insert_db(messageStore, "bom dia");
  // ----------------------------------- ajudar --------------------------------------------
  insert_db(messageStore, "ajudar");
  // ----------------------------------- eu --------------------------------------------
  insert_db(messageStore, "eu");
  // ----------------------------------- posso --------------------------------------------
  insert_db(messageStore, "posso");

  return 0;
}


