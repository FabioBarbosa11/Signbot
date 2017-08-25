#include "ros/ros.h"
#include "std_msgs/String.h"

#define MAX_JOINTS 46
/*******************************************************************************
 *        database
 * ****************************************************************************/

//vector com as coordenadas default(braços em baixo)
float default_pose[MAX_JOINTS] = { 1.57, 1.5, 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,

                                 1.57, -1.5, 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0};

float leter_b[MAX_JOINTS] = {
                              0.52, 1.19, -0.09, -0.16, 1.57,
                              0.27, 0, 0.3,
                              0, 0, 0,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,
                              1.57, 1.57, 1.57,

                              1.57, -1.5, 0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0,
                              0, 0, 0
                            };

float bom_dia[4][MAX_JOINTS] =
{
  {
    0.52, 1.19, -0.09, -0.16, 1.57,
    0.27, 0, 0.3,
    0, 0, 0,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    0.52, 1.19, -0.09, -0.16, 1.57,
    0.27, 0, 0.3,
    0, 0, 0,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,
    1.57, 1.57, 1.57,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    0.52, 1.19, -0.09, -0.16, 1.57,
    0.27, 0, 0.3,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
   0.59, 1.41, -0.23, -1.34, 1.57,
    0, -0.22, 0.35,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    1.57, -1.5, 0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  }
};

float ajudar[2][MAX_JOINTS] =
{
  {
    0.49, 1.03, 0.23, -0.45, 1.57,
    0, -0.43, -0.79,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    0.08, -0.93, -0.49, -0.17, -1.57,
    0, 0.52, 0.79,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    0, 1.41, 0.61, -0.51, 0.7,
    0, -0.37, -0.4,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,

    0, -1.49, -0.69, -0.8, -0.81,
    0, 0.09, 0.48,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  }
};

/**********************************************************************************
 *
 * *******************************************************************************/

class Word_searcher
{
private:
  ros::Publisher word_LGP_pub_;
public:
  Word_searcher(const ros::Publisher& _word_LGP_pub)
    :word_LGP_pub_(_word_LGP_pub)
  {

  }

  void word_LPCallBack(const std_msgs::String::ConstPtr& _word)
  {
    ROS_INFO_STREAM("\n I heard: "<<_word->data.c_str()<<"\n");
    search_database(_word);
  }

  void search_database(const std_msgs::String::ConstPtr& _word)
  {
    //Search in database

    //send the gesture
    word_LGP_pub_.publish(*_word);
  }

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "signbot_db_core");
  ros::NodeHandle nh;

  //Publisher to send the angles of the gestures
  ros::Publisher word_LGP_pub = nh.advertise<std_msgs::String>("wordLGP", 10);
  Word_searcher word_searcher(word_LGP_pub);
  //Subscriber to listen what word it needs to translate
  ros::Subscriber word_LP_sub = nh.subscribe("wordLP", 10, &Word_searcher::word_LPCallBack, &word_searcher);

  sleep(10);
  ROS_INFO_STREAM("\nProgram is ready to execute\n");

  if(ros::ok())
  {
    ros::spin();
  }

  ROS_INFO_STREAM("\n\t***** SHUTTING DOWN ********\n");
  return 0;
}

// *************************************** other tests ******************************** //
/*
int main(int argc, char **argv)
{
  ros::init(argc, argv, "signbot_db_core");
  ros::NodeHandle nh;
  ros::Publisher gesture_pose_pub = nh.advertise<Float32MultiArray>("gesture_pose", 1000);

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
*/

/*
#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"

#include "std_msgs/Int32MultiArray.h"

int main(int argc, char **argv)
{


  ros::init(argc, argv, "signbot_db_core");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<std_msgs::Int32MultiArray>("array", 100);

  while (ros::ok())
  {
    std_msgs::Int32MultiArray array;
    //Clear array
    array.data.clear();
    //for loop, pushing data in the size of the array
    for (int i = 0; i < 90; i++)
    {
      //assign array a random number between 0 and 255.
      array.data.push_back(rand() % 255);
    }
    //Publish array
    pub.publish(array);
    //Let the world know
    ROS_INFO("I published something!");
    //Do this.
    ros::spinOnce();
    //Added a delay so not to spam
    sleep(2);
  }

}
*/
