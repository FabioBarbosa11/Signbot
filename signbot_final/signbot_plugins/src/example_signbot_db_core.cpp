#include "ros/ros.h"
#include "std_msgs/String.h"

#include "signbot_plugins/gestureInformation.h"
using signbot_plugins::gestureInformation;

#include <vector>
using std::vector;

#include <string>
using std::string;


#define MAX_JOINTS 46
/*******************************************************************************
 *                                database
 * ****************************************************************************/

//vector com as coordenadas default(braços em baixo)
float default_pose[MAX_JOINTS] = {
                                   1.57, 1.5, 0, 0, 0,
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
 * *******************************************************************************/

class Word_searcher
{
private:
  ros::Publisher gesture_LGP_pub_;
public:
  Word_searcher(const ros::Publisher& _gesture_LGP_pub)
    :gesture_LGP_pub_(_gesture_LGP_pub)
  {

  }

  void word_LPCallBack(const std_msgs::String::ConstPtr& _word)
  {
    ROS_INFO_STREAM("\n I heard: "<<_word->data.c_str()<<"\n");
    search_database(_word);
  }

  void search_database(const std_msgs::String::ConstPtr& _word)
  {
    int i, j;
    gestureInformation  gesture;
    //ROS_INFO_STREAM("message receive:\n"<<_word->data<<"\n");


    //  ************** Search in database  *****************************

    if(_word->data == "default_pose" )
      //ou _word->data == "default_pose"
    {
      gesture.gesture_name = "default";
      gesture.max_poses = 1;

      for(i=0; i< MAX_JOINTS; i++)
      {
        gesture.poses.push_back(default_pose[i]);
      }
    }
    else
    {
      if(_word->data == "b" || _word->data == "B" )
      {
        gesture.gesture_name = "b";
        gesture.max_poses = 1;

        for(i=0; i< MAX_JOINTS; i++)
        {
          gesture.poses.push_back(default_pose[i]);
        }

      }
      else
      {
        if(_word->data == "bom dia")
        {
          gesture.gesture_name = "bom dia";
          gesture.max_poses = 4;

          for(j=0; j< gesture.max_poses; j++)
          {
            for(i=0; i< MAX_JOINTS; i++)
            {
              gesture.poses.push_back(bom_dia[j][i]);
            }
          }
        }
        else
        {
          if(_word->data == "ajudar")
          {
            gesture.gesture_name = "ajudar";
            gesture.max_poses = 2;

            for(j=0; j< gesture.max_poses ; j++)
            {
              for(i=0; i< MAX_JOINTS; i++)
              {
                gesture.poses.push_back(ajudar[j][i]);
              }
            }
          }
          else    //if theres none of the words that exist in the database
          {
            gesture.gesture_name = "nao reconhecido";
            gesture.max_poses = 0;

            for(i=0; i<MAX_JOINTS; i++)
            {
              gesture.poses.push_back(0.0);
            }
          }
        }
      }
    }
    //send the gesture
    gesture_LGP_pub_.publish(gesture);
  }

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "signbot_db_core");
  ros::NodeHandle nh;

  //Publisher to send the angles of the gestures
  ros::Publisher gesture_LGP_pub = nh.advertise<gestureInformation>("gestureInfo_LGP", 10);
  Word_searcher word_searcher(gesture_LGP_pub);
  //Subscriber to listen what word it needs to translate
  ros::Subscriber word_LP_sub = nh.subscribe("word_LP", 10, &Word_searcher::word_LPCallBack, &word_searcher);

  sleep(10);
  ROS_INFO_STREAM("\nProgram is ready to execute\n");

  if(ros::ok())
  {
    ros::spin();
  }

  ROS_INFO_STREAM("\n\t***** SHUTTING DOWN ********\n");
  return 0;
}
