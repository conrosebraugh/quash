#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include "Job.cpp"

using namespace std;

vector<string> parseinput(string input);
int countwords(string strString);


int main(int argc, char **argv, char **envp)
{
  //  char input[1024];
  string input;
  string PATH = envp[42];
  string HOME = envp[64];

  cout << endl;

  int i = 0;

  while(true)
  {
    cout << "quash$ ";
    getline(cin, input);
    
    vector<string> cmdinput = parseinput(input);

    int numcmds = cmdinput.size();

    if(numcmds == 1)
    {
      if(cmdinput[0] == "quit" || cmdinput[0] == "exit")
	exit(0);
      else if(cmdinput[0] == "\n")
	continue;
      else
      {
      	pid_t pid;
      }
    }//end if(numcmds == 1)

  }
}

vector<string> parseinput(string input)
{
  int pos1, pos2 = 0, wordcount = countwords(input);

  pos1 = input.find(" ");

  vector<string> cmds;
 
  if(wordcount == 1)
  {
    cmds.push_back(input);
    return cmds;
  }
  else
  {
    cmds.push_back(input.substr(0, pos1));

    int i = 1;

    while(i < wordcount)
      {
	pos1++;
	pos2 = input.substr(pos1).find(" ");
	cmds.push_back(input.substr(pos1, pos2));
	pos1 = pos1 + pos2;
	i++;
      }

    return cmds;
  }
}

int countwords(string str)
{
   bool inSpaces = true;
   int numWords = 0;
   int i = 0;

   while (str[i] != NULL)
   {
      if (isspace(str[i]))
      {
         inSpaces = true;
      }
      else if (inSpaces)
      {
         numWords++;
         inSpaces = false;
      }

      ++i;
   }

   return numWords;
}

