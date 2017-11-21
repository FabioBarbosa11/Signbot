#ifndef SIGNBOTDB_H
#define SIGNBOTDB_H

#include "ros/ros.h"
#include "mongodb_store/message_store.h"
#include <boost/foreach.hpp>
#include "std_msgs/Float32MultiArray.h"
#include  <iostream>
#include <vector>

#include <sstream>
#include <cassert>

class SignbotDB
{
public:
  SignbotDB(ros::NodeHandle _node);

  std::vector<float> getposes(std::string _name);

private:
   mongodb_store::MessageStoreProxy messageStore;
};

#endif // SIGNBOTDB_H
