#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include <iostream>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {

    int pid = Pid();
    long uptime = LinuxParser::UpTime();

    vector<string> proc_cpu_val = LinuxParser::ProcessCpuUtilization(to_string(pid));

    unsigned long utime = std::stoul (proc_cpu_val[0], nullptr, 0);
    unsigned long stime = std::stoul (proc_cpu_val[1], nullptr, 0);
    unsigned long cutime = std::stoul (proc_cpu_val[2], nullptr, 0);
    unsigned long cstime = std::stoul (proc_cpu_val[3], nullptr, 0);
    unsigned long starttime = std::stoul (proc_cpu_val[4], nullptr, 0);

    long hertz = sysconf(_SC_CLK_TCK);

    unsigned long total_time = utime + stime + cutime + cstime;
    unsigned long seconds = uptime - (starttime / hertz);

    float cpu_usage = 100 * ((total_time / (float) hertz) / (float) seconds);
    
    /*std::cout << "process ID " << pid<<std::endl; 
    for (auto i : proc_cpu_val){
        std::cout << i << " ";
    }
    std::cout << "cpu_usage " << cpu_usage;
    std::cout << std::endl;
    */
    cpuutil_ = cpu_usage;
    return cpu_usage;
    
}

// TODO: Return the command that generated this process
string Process::Command() { return  }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a ) const {
    return cpuutil_ < a.cpuutil_;}