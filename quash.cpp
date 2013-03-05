#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

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
    
    if(input == "quit" || input == "exit")
      exit(0);
    else if(input == "\n")
      continue;
  }
}
