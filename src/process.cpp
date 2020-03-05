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

    
    double utime = std::stod (proc_cpu_val[13]);
    double stime = std::stod (proc_cpu_val[14]);
    double cutime = std::stod (proc_cpu_val[15]);
    double cstime = std::stod (proc_cpu_val[16]);
    double starttime = std::stod (proc_cpu_val[21]);

    
    
    long hertz = sysconf(_SC_CLK_TCK);

    double total_time = utime + stime + cutime + cstime;
    double seconds = uptime - (starttime / hertz);

    float cpu_usage = (total_time / hertz) / seconds;
    
    
    cpuutil_ = cpu_usage;
    
    
    return cpu_usage;
    
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    long int up = LinuxParser::UpTime(pid_);
    long hertz = sysconf(_SC_CLK_TCK);
    return up/hertz;
    }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator>(Process const& a ) const {
    return cpuutil_ > a.cpuutil_;}