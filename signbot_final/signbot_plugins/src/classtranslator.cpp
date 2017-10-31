#include <signbot_plugins/classtranslator.h>

#include <string>
#include <vector>
using namespace std;

MyTranslator::MyTranslator(ros::NodeHandle _node)
{
  phrase_PL_sub = _node.subscribe("phrasePL",10, &MyTranslator::phrase_PLCallback, this);

  sc.establish_pub(_node);

  sc.pub_default_pose(default_pose);

  ROS_INFO_STREAM("\nProgram is ready to execute");
}

void  MyTranslator::phrase_PLCallback(const std_msgs::String::ConstPtr& _phrase)
{
  //ROS_INFO_STREAM("\nPhrase receive:\n"<<_phrase->data.c_str());

  //calls other function who will process and make a publish
  this->trans_pub(_phrase);
}

int MyTranslator::trans_pub(const std_msgs::String::ConstPtr& _phrase)
{
  unsigned int max_poses, max_words, first_pointer,i, num_poses,j, word_index;
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

  for(i=0; i< max_words; i++)
  {
      if(words[i] == "default_pose")
      {
       max_poses+=1;
      }
      else
      {
        if(words[i] == "b")
        {
          max_poses+=1;
        }
        else
        {
          if(words[i] == "bom dia")
          {
            max_poses+=3;
          }
          else
          {
            if(words[i] == "ajudar")
            {
              max_poses+=2;
            }
            else    //if theres none of the words that exist in the database
            {
              if(words[i] == "eu")
              {
                max_poses+=1;
              }
              else
              {
                if(words[i] == "posso")
                {
                  max_poses+=2;
                }
                else
                {
                  ROS_INFO_STREAM("\tERRO: palavra nao encontrada!\n");
                  return -1;
                }
              }
            }
           }
          }
        }
  }

  // Creates the variable which will save all poses in order
  float phrase_translated[max_poses][MAX_JOINTS];

  for(i=0; i<max_poses; i++)
  {
    for(j=0; j<MAX_JOINTS; j++)
    {
      phrase_translated[i][j] = 0.0;
    }
  }

  //fills the varible with gesture in order
  word_index=0;
  first_pointer=0;
  while(word_index<max_words)
  {
    ROS_INFO_STREAM("\n copying words... first_pointer: "<<first_pointer<<", word_index:"<<word_index);
    if(words[word_index] == "default_pose")
    {
      for(i=0; i<MAX_JOINTS; i++)
      {
       phrase_translated[first_pointer][i] = default_pose[0][i];
      }
      first_pointer++;
    }
    else
    {
      if(words[word_index] == "b")
      {
        for(i=0; i<MAX_JOINTS; i++)
        {
         phrase_translated[first_pointer][i] = letter_b[0][i];
        }
        first_pointer++;
      }
      else
      {
        if(words[word_index] == "bom dia")
        {
          num_poses=3;
          for(j=0;j<num_poses; j++)
          {
            for(i=0; i<MAX_JOINTS; i++)
            {
             phrase_translated[first_pointer][i] = bom_dia[j][i];
            }
            first_pointer++;
          }
        }
        else
        {
          if(words[word_index] == "ajudar")
          {
            num_poses=2;
            for(j=0;j<num_poses; j++)
            {
              for(i=0; i<MAX_JOINTS; i++)
              {
               phrase_translated[first_pointer][i] = ajudar[j][i];
              }
              first_pointer++;
            }
          }
          else
          {
            if(words[word_index] == "posso")
            {
              num_poses=2;
              for(j=0;j<num_poses; j++)
              {
                for(i=0; i<MAX_JOINTS; i++)
                {
                 phrase_translated[first_pointer][i] = posso[j][i];
                }
                first_pointer++;
              }
            }
            else
            {
              if(words[word_index] == "eu")
              {
                for(i=0; i<MAX_JOINTS; i++)
                {
                 phrase_translated[first_pointer][i] = eu[0][i];
                }
                first_pointer++;
              }
            }
          }
         }
        }
      }
    word_index++;
  }

  //fills the last space with default_pose
  for(i=0; i<MAX_JOINTS; i++)
  {
   phrase_translated[max_poses-1][i] = default_pose[0][i];
  }

  //publishes the message
  sc.register_positions(phrase_translated, max_poses);

  return 1;
}
