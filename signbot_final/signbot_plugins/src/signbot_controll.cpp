#include  <signbot_plugins/signbot_controll.h>

#define GESTURE_DURATION 3.0

void SignbotController::establish_pub(ros::NodeHandle n)
{
  body_controll_pub = n.advertise<trajectory_msgs::JointTrajectory>("/signbot/body_controller/command", 10);

  sleep(1);
  while (body_controll_pub.getNumSubscribers()<1)
  {
   ROS_INFO_STREAM("\nbody_controll_pub: Waiting for at least one subscriber...");
   sleep(5);
  }

  //prepares the message
  insert_jointnames();
}

void SignbotController::insert_jointnames()
{
  // Fill the names of the joints to be controlled.
  // Note that the vacuum_gripper_joint is not controllable.
  _message.joint_names.clear();

  _message.joint_names.push_back("r_shoulder1_joint");
  _message.joint_names.push_back("r_shoulder2_joint");
  _message.joint_names.push_back("r_arm_joint");
  _message.joint_names.push_back("r_elbow1_joint");
  _message.joint_names.push_back("r_elbow2_joint");
  _message.joint_names.push_back("r_wirst1_j");
  _message.joint_names.push_back("r_wirst2_j");
  _message.joint_names.push_back("r_wirst3_j");
  _message.joint_names.push_back("r_bottom_knuckle1_thumb_j");
  _message.joint_names.push_back("r_bottom_knuckle2_thumb_j");
  _message.joint_names.push_back("r_top_knuckle_thumb_j");
  _message.joint_names.push_back("r_bottom_knuckle_index_j");
  _message.joint_names.push_back("r_middle_knuckle_index_j");
  _message.joint_names.push_back("r_top_knuckle_index_j");
  _message.joint_names.push_back("r_bottom_knuckle_middle_j");
  _message.joint_names.push_back("r_middle_knuckle_middle_j");
  _message.joint_names.push_back("r_top_knuckle_middle_j");
  _message.joint_names.push_back("r_bottom_knuckle_third_j");
  _message.joint_names.push_back("r_middle_knuckle_third_j");
  _message.joint_names.push_back("r_top_knuckle_third_j");
  _message.joint_names.push_back("r_bottom_knuckle_little_j");
  _message.joint_names.push_back("r_middle_knuckle_little_j");
  _message.joint_names.push_back("r_top_knuckle_little_j");

  _message.joint_names.push_back("l_shoulder1_joint");
  _message.joint_names.push_back("l_shoulder2_joint");
  _message.joint_names.push_back("l_arm_joint");
  _message.joint_names.push_back("l_elbow1_joint");
  _message.joint_names.push_back("l_elbow2_joint");
  _message.joint_names.push_back("l_wirst1_j");
  _message.joint_names.push_back("l_wirst2_j");
  _message.joint_names.push_back("l_wirst3_j");
  _message.joint_names.push_back("l_bottom_knuckle1_thumb_j");
  _message.joint_names.push_back("l_bottom_knuckle2_thumb_j");
  _message.joint_names.push_back("l_top_knuckle_thumb_j");
  _message.joint_names.push_back("l_bottom_knuckle_index_j");
  _message.joint_names.push_back("l_middle_knuckle_index_j");
  _message.joint_names.push_back("l_top_knuckle_index_j");
  _message.joint_names.push_back("l_bottom_knuckle_middle_j");
  _message.joint_names.push_back("l_middle_knuckle_middle_j");
  _message.joint_names.push_back("l_top_knuckle_middle_j");
  _message.joint_names.push_back("l_bottom_knuckle_third_j");
  _message.joint_names.push_back("l_middle_knuckle_third_j");
  _message.joint_names.push_back("l_top_knuckle_third_j");
  _message.joint_names.push_back("l_bottom_knuckle_little_j");
  _message.joint_names.push_back("l_middle_knuckle_little_j");
  _message.joint_names.push_back("l_top_knuckle_little_j");
}

void SignbotController::register_positions(std::vector<float> _array)
{
  unsigned int i=0,
               j=0,
               array_index=0;                                         //this will be the index for running the array
  //resize the waypoint to the total of waypoints needed for the PLphrase translation
  _message.points.resize(_array.size()/MAX_JOINTS);
  // Resize the vector to the same length as the joint names.
  for(i=0; i<_array.size()/MAX_JOINTS; i++)
  {
    _message.points[i].positions.resize(_message.joint_names.size());
  }
  //copy the angle value for which joint to which waypoint sequel
  i=0;
  array_index=0;

  while(array_index < _array.size())
  {
    for(j=0; j< MAX_JOINTS; j++)                                    //copy all the angles for that pose
    {
      _message.points[i].positions[j]=_array[array_index+j];
    }
    _message.points[i].time_from_start = ros::Duration(GESTURE_DURATION*i+GESTURE_DURATION);      //says the time that which point has (always current+2 seconds)

    ROS_INFO_STREAM("i: "<<i);
    ROS_INFO_STREAM("duration: "<<_message.points[i].time_from_start);
    ROS_INFO_STREAM("_array.size: "<<_array.size());
    ROS_INFO_STREAM("array_index: "<<array_index);

    i++;                                                            //goes to the next pose waypoint
    array_index += MAX_JOINTS;                                      // increments, so that the next iterations points to the next waypoint pose



  }
  //ROS_INFO_STREAM("it went off the new while algoritm :-)");
  duration = 2*(GESTURE_DURATION*_array.size()+GESTURE_DURATION);   //because of gazebo lag

  this->publish();
}

void SignbotController::publish()
{
   body_controll_pub.publish(_message);
   //ROS_INFO_STREAM("\n publishing comand to robot. Message: \n"<<_message);
   //sleep(duration);
   ROS_INFO_STREAM("stop sleeping");
}

void SignbotController::pub_default_pose(std::vector<float> _array)
{
  _message.points.resize(1);

  _message.points[0].positions.resize(_message.joint_names.size());

  for(int i=0; i< MAX_JOINTS; i++)
  {
    _message.points[0].positions[i]=_array[i];
  }

  _message.points[0].time_from_start = ros::Duration(GESTURE_DURATION);

  duration = 2*GESTURE_DURATION;

  this->publish();
}
