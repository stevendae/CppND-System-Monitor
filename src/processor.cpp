#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {

    curr_cpu = LinuxParser::CpuUtilization();

    unsigned long previdle = std::stoul (prev_cpu[3], nullptr, 0);
    unsigned long previowait = std::stoul (prev_cpu[4], nullptr, 0);

    unsigned long idle = std::stoul (curr_cpu[3], nullptr, 0);
    unsigned long iowait = std::stoul (curr_cpu[4], nullptr, 0);

    unsigned long prevuser = std::stoul (prev_cpu[0], nullptr, 0);
    unsigned long prevnice = std::stoul (prev_cpu[1], nullptr, 0);
    unsigned long prevsystem = std::stoul (prev_cpu[2], nullptr, 0);
    unsigned long previrq = std::stoul (prev_cpu[5], nullptr, 0);
    unsigned long prevsoftirq = std::stoul (prev_cpu[6], nullptr, 0);
    unsigned long prevsteal = std::stoul (prev_cpu[7], nullptr, 0);

    unsigned long user = std::stoul (curr_cpu[0], nullptr, 0);
    unsigned long nice = std::stoul (curr_cpu[1], nullptr, 0);
    unsigned long system = std::stoul (curr_cpu[2], nullptr, 0);
    unsigned long irq = std::stoul (curr_cpu[5], nullptr, 0);
    unsigned long softirq = std::stoul (curr_cpu[6], nullptr, 0);
    unsigned long steal = std::stoul (curr_cpu[7], nullptr, 0);

    unsigned long int PrevIdle = previdle + previowait;
    unsigned long int Idle = idle + iowait;

    unsigned long int PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    unsigned long int NonIdle = user + nice + system + irq + softirq + steal;

    unsigned long int PrevTotal = PrevIdle + PrevNonIdle;
    unsigned long int Total = Idle + NonIdle;

    unsigned long int totald = Total - PrevTotal;
    unsigned long int idled = Idle - PrevIdle;

    float CPU_Percentage = (totald - idled)/(float)totald;

    prev_cpu = curr_cpu;

    return CPU_Percentage;
}
