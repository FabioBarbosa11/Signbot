#include <signbot_plugins/classtranslator.h>

#include <string>
#include <vector>
#include "std_msgs/Float32MultiArray.h"

using namespace std;

MyTranslator::MyTranslator(ros::NodeHandle _node) : sdb(_node) //initalize the messastoreproxy from db object
{
  phrase_PL_sub = _node.subscribe("phrasePL",10, &MyTranslator::phrase_PLCallback, this);

  sc.establish_pub(_node);

  std::vector<float> _default_poses =  sdb.getposes("default_pose");

  sc.pub_default_pose(_default_poses);

  ROS_INFO_STREAM("\nProgram is ready to execute");
}

void  MyTranslator::phrase_PLCallback(const std_msgs::String::ConstPtr& _phrase)
{
  ROS_INFO_STREAM("\nPhrase receive:\n"<<_phrase->data.c_str());

  //calls other function who will process and make a publish
  this->trans_pub(_phrase);
}

int MyTranslator::trans_pub(const std_msgs::String::ConstPtr& _phrase)
{
  unsigned int max_poses, max_words, first_pointer,i,j;
  vector<string> words;

  //Calculate number of words and separate them in a vector
  std::size_t char_divider=0;
  max_words=0;
  first_pointer=0;
  while(char_divider<_phrase->data.length())
  {
    char_divider = _phrase->data.find(".", char_divider, 1);
    max_words+=1;

    words.push_back(_phrase->data.substr(first_pointer,char_divider-first_pointer));
    char_divider+=1;
    first_pointer=char_divider;
  }
/*
  ROS_INFO_STREAM("words:");
  for(i=0; i< max_words; i++)
  {
    ROS_INFO_STREAM(words[i]<<" , ");
  }
*/

  //search on database to known the max number poses for the phrase
  max_poses=1;      //and extra pose for default_pose in the end of the sentence

  // depois seria apenas procurar a palavra na base de dados,
  // a seguir passar do floatmultaaray para vecto<float>
  // acrescentar no final mais a pose final
  // e entregar um array gigante ao signbot control e esse que trata-se de dividir
  vector<float> lgp_phrase, aux_array;

  lgp_phrase.clear();
  aux_array.clear();

  for(i=0; i< max_words; i++)
  {
      aux_array = sdb.getposes(words[i]);

      if(aux_array[0]==-99)
      {
         ROS_INFO_STREAM("\tERRO: palavra nao encontrada!\n");
         return -1;
      }

      for(j=0; j<aux_array.size(); j++)
      {
         lgp_phrase.push_back(aux_array[j]);
      }

      aux_array.clear();
  }

  //insert the last pose, which is the stand by pose(default_pose)
  aux_array = sdb.getposes("default_pose");
  for(j=0; j<aux_array.size(); j++)
  {
     lgp_phrase.push_back(aux_array[j]);
  }
/*
  for(j=0; j<lgp_phrase.size(); j++)
  {
    ROS_INFO_STREAM("angule("<<j<<"):"<<lgp_phrase[j]);
  }
  ROS_INFO_STREAM("total poses:"<<lgp_phrase.size());
*/
  //publishes the message
  sc.register_positions(lgp_phrase);

  return 1;
}
