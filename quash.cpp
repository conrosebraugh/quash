#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include "Job.cpp"

using namespace std;

vector<string> parseinput(string input);
int countwords(string strString);
char** vectortoarray(vector<string> &thestrings);
//void basicParse(string input, string found, int splitPoint);

int main(int argc, char **argv, char **envp)
{
  //  char input[1024];
  string input;
  string PATH = envp[42];
  string HOME = envp[64];
  string workingdir;

  int status;
  pid_t pid;

  while(true)
  {
  	workingdir = get_current_dir_name();
  	int temp = workingdir.find_last_of("/");
  	workingdir.erase(0,temp+1);
    cout << "[" << workingdir << "]" << "quash$ ";
    
    getline(cin, input);
    
    vector<string> cmdinput = parseinput(input);
    //for( vector<string>::const_iterator i = cmdinput.begin(); i != cmdinput.end(); ++i)
    //cout << *i << ' ';

    int numcmds = cmdinput.size();

    if(cmdinput[0] == "quit" || cmdinput[0] == "exit")
      exit(0);
    else if(cmdinput[0] != "")
    {
      pid = fork();
      if(pid == -1)
	cerr << "Fork error" << endl;
      else if(pid == 0)
      {
	char** temp = vectortoarray(cmdinput);
	execvp(cmdinput[0].c_str(), temp);
	  
      }//end else if(pid...  
      else
	wait(&status);
      continue;
    }
    else
      continue;
    

  }//end while
}//end main

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

/*void basicParse(string input, string &found, int &splitPoint)
{
	for(int i=0; i<input; i++)
	{
		if(strcmp(input[i], "|") == 0)
		{
			found = "pipe";
			splitPoint = i;
		}
		else if(strcmp(input[i], ">") == 0)
		{
			found = "reOut";
			splitPoint = i;
		}
		else if(strcmp(input[i], "<") == 0)
		{
			found = "reIn";
			splitPoint = i;
		}
	}
	
}*/

char** vectortoarray(vector<string> &thestrings)
{
  //create a dynamic array of c strings
  char** temp = new char*[thestrings.size()-1];

  int i = 1;

  for(; i < thestrings.size(); i++)
    temp[i-1] = (char*)thestrings[i].c_str();

  return temp;
}

