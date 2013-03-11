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
  string input;
  string PATH = (string)getenv("PATH");
  string HOME = (string)getenv("HOME");
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
    
    int numcmds = cmdinput.size();


    //Check to see if the user issued the quit command
    if(cmdinput[0] == "quit" || cmdinput[0] == "exit")
      exit(0);
    //Check to see if the user wants to see the environment, print it out
    else if(cmdinput[0] == "env")
    {
      int i = 0;
      while(envp[i] != NULL)
      {
	cout << envp[i] << endl;
	i++;
      }
    }
    //command isn' one of the above and isn't just a carriage return
    else if(cmdinput[0] != "")
    {
      pid = fork(); //fork a new process
     
      if(pid == -1) //check to see if there was a fork error
	cerr << "Fork error" << endl;
      //If this is the child process...
      else if(pid == 0)
      {
	//...and the command is a single word...
	if(cmdinput.size() == 1)
	{
	  char* blah = (char*)"";
	  //exec a new process that is the single command 
	  //which is found at cmdinput[0]
	  execlp(cmdinput[0].c_str(), blah, (char*)NULL);
	}
	//...and the command has arguments...
	else 
	{
	  //create a c_str array of the arguments to the command
	  char** argarray = vectortoarray(cmdinput);
	  //exec a new process that is the command at cmdinput[0]
	  //followed by the arguments to that command
	  execvp(cmdinput[0].c_str(), argarray);
	}
      }//end else if(pid...  
      //If this is the parent process...
      else
	wait(&status); //wait for the child process to finish
      continue;
    }
    //carriage return case. continue with the main loop
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
