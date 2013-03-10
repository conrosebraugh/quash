#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Job.cpp"

using namespace std;

string* parseinput(string input);
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
    
    string* cmdinput = parseinput(input);

    int numcmds = sizeof(cmdinput)/sizeof(string);
    
    if(numcmds == 1)
    {
      if(cmdinput[0] == "quit" || cmdinput[0] == "exit")
	exit(0);
      else if(cmdinput[0] == "\n")
	continue;
      else
      {
	
      }
    }//end if(numcmds == 1)

  }
}

string* parseinput(string input)
{
  int pos1, pos2 = 0;

  pos1 = input.find(" ");

  string* cmds;
  cmds = new string[countwords(input)+1];

  if(countwords(input) == 1)
  {
    cmds[0] = input;
    return cmds;
  }
  else
  {
    cmds[0] = input.substr(0, pos1);

    int i = 1;
    int len = 0;
    while(len < input.length())
      {
	pos1++;
	pos2 = input.substr(pos1).find(" ");
	cmds[i] =  input.substr(pos1, pos2);
	len += input.substr(pos1, pos1-pos2).length();
	pos1 = pos1 + pos2;
	i++;
      }

    //  for(int j = 0; j < countwords(input)+1; j++)
    //    cout << cmds[j] << endl;

    return cmds;
  }
}

int countwords(string str)
{
  int nSpaces = 0;
  unsigned int i = 0;

  while(isspace(str[i]))
    i++;

  for(; i < str.length(); i++)
  {
    if(isspace(str[i]))
    {
      nSpaces++;
      while(isspace(str[i++]))
        if(str.at(i) == '\0')
          nSpaces--;
    }
  }

  return nSpaces + 1;
}
