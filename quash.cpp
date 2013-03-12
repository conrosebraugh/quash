#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <signal.h>
#include "Job.cpp"

using namespace std;

vector<string> parseinput(string input);
int countwords(string strString);
char** vectortoarray(vector<string> &thestrings);
//void basicParse(string input, string found, int splitPoint);
void cd( vector<string> cmds);

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
    //Check to see if user issued the cd command
    else if(cmdinput[0] == "cd")
    	cd(cmdinput);
	//Check to see if user issued the set command
//    else if(cmdinput[0] == "set")
//    	set(cmdinput);
	//Check to see if user issued the kill command
//    else if(cmdinput[0] == "kill")
//    	kill(cmdinput);
    
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

void cd(vector<string> cmds)
{
  if(!cmds[1].empty())
  {
      //absolute path given
      if(cmds[1][0] == '/')
      {
	if(chdir(cmds[1].c_str()) != 0)
	  cerr << "Error, invalid directory: " << cmds[1] << endl;
      }
      //dosen't start with '/' so relitive path given
      else
      {
	string workingdir = get_current_dir_name();
	if(chdir((workingdir + "/" + cmds[1]).c_str()) != 0)
	  cerr << "Error, invalid directory: " << cmds[1] << endl;
      }
  }
  //only cd given as argument so change to home directory
  else
    if(chdir(getenv("HOME")) != 0)
      cerr << "Error, couldn't change directory to: " << getenv("HOME") << endl;
			
}
/*
void set( string *cmds)
{

	if(cmds[1].empty())
	{
		cerr << "Error, No enviroment specified" << endl;
		return;
	}
	
	if(strncmp(cmds[1].c_str(), "HOME=", 5) == 0)
	{
		if(setenv("HOME", &cmds[1][5],1) == -1)
			cerr << "Error, could not set HOME" << endl;
	}
	if(strncmp(cmds[1].c_str(), "PATH=", 5) == 0)
	{
		if(setenv("PATH", &cmds[1][5],1) == -1)
			cerr << "Error, could not set PATH << endl;
	}

}

void kill( string *cmds)
{

	if(cmds[1].empty())
	{
		cerr << "Must pass ID number of process to kill" << endl;
		return;
	}
	if(kill(atoi(cmds[1].c_str()), SIGKILL) != 0)
	{
		cerr << "Error, Process could not be killed" << endl;
	}

}*/
