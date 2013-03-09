#include <cstdlib>
#include <unistd.h>
#include <string>

using namespace std;

class Job {
private:

  int jobid;
  pid_t pid;
  string command;

public:
  
  Job(int jid, pid_t p, string comm)
  {
    this->jobid = jid;
    this->pid = p;
    this->command = comm;   
  }
  int getjobid()   {return jobid;}
  pid_t getpid()   {return pid;}
  string getcommand() {return command;}

};

