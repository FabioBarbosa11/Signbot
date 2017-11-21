/**
 *  Lets try see read some data from database.
 *    For this, lets follow the data from the example of mongodb_store
 */

#include "ros/ros.h"
#include "mongodb_store/message_store.h"
#include "geometry_msgs/Pose.h"
#include <boost/foreach.hpp>
#include "std_msgs/String.h"

#include <sstream>
#include <cassert>

using namespace geometry_msgs;
using namespace mongodb_store;
using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "example_mongodb_store_cpp_client");
	ros::NodeHandle nh;

	//Create object which does the work for us.
	MessageStoreProxy messageStore(nh);

	//This is the message we want to store
	Pose p;
  string name("my pose");
  string id(messageStore.insertNamed(name, p));
  cout<<"CREATED: Name: " <<name<<", id: "<<id<<endl;

	vector< boost::shared_ptr<Pose> > results;

	//Get it back, by default get one
  if(messageStore.queryNamed<Pose>(name, results))
  {

    BOOST_FOREACH( boost::shared_ptr<Pose> p,  results)
		{
			ROS_INFO_STREAM("Got by name: " << *p);
		}
	}
  ROS_INFO_STREAM("Did you got? 1\n");

  if(messageStore.queryNamed<Pose>(name, results))
  {

    BOOST_FOREACH( boost::shared_ptr<Pose> p,  results)
    {
      ROS_INFO_STREAM("Got by name: " << *p);
    }
  }
  ROS_INFO_STREAM("Did you got? 1\n");

	results.clear();
	// try to get it back with an incorrect name, so get None instead
	messageStore.queryNamed<Pose>("my favourite position", results);
	BOOST_FOREACH( boost::shared_ptr<Pose> p,  results)
	{
		ROS_INFO_STREAM("Got: " << *p);
	}

  ROS_INFO_STREAM("Did you got? 2, recomended not to\n");

	results.clear();
	// get all poses, should show updated named position  
  messageStore.query<Pose>(results);
	BOOST_FOREACH( boost::shared_ptr<Pose> p,  results)
	{
		ROS_INFO_STREAM("Got: " << *p);
	}

  ROS_INFO_STREAM("Now by the names..."<<endl);
  results.clear();
  vector< boost::shared_ptr<std_msgs::String> > n_results;
  messageStore.query<std_msgs::String>(n_results);
  BOOST_FOREACH( boost::shared_ptr<std_msgs::String> n,  n_results)
  {
    ROS_INFO_STREAM("Got: " << *n);
  }

  messageStore.query<Pose>(results, mongo::BSONObj(), mongo::BSONObj(),mongo::BSONObj(), false, 2); // limit=2
  ROS_INFO_STREAM("Got: " << results.size() << " messages.");

	results.clear();

	return 0;
}


