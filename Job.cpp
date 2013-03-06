#include <cstdlib>
#include <unistd>

using namespace std;

class Job {
private:

  int jobid;
  pid_t pid;
  string command;

public:
  
  Job(int, pid_t, string);
  int getjobid()   {return jobid};
  pid_t getpid()   {return pid};
  string command() {return command};

};

Job::Job(int jid, pid_t p, string comm)
{
  jobid = jid;
  pid = p;
  command = comm;
}
