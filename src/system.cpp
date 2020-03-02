#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
// Ordered based on CpuUtilization
vector<Process>& System::Processes() { 
    
    vector<int> pids{LinuxParser::Pids()};

    // Create a set
    // Go through extant (still in existance) Processes
    set<int> extant_pids;
    for (Process &process : processes_) {
        extant_pids.insert(process.Pid());
    }

    // Emplace (put into place) all new processes
    for (int pid : pids) {
        // set.find(val) searches the container for an element equivalent to val
        // and returns an iterator to it if found, otherwise it returns an
        // iterator to set::end

        // this is asking is the pid in the PID vector an existing PID,
        // if not than add it to the end of processes vector
        if (extant_pids.find(pid) == extant_pids.end()){
            Process process(pid);
            processes_.push_back(process);
        }
    }

    // Update CPU utilization
    for (auto& process : processes_) {
        process.CpuUtilization();
    }
    
    std::sort(processes_.begin(), processes_.end(), std::less<Process>());
    return processes_; 
    }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses();}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }