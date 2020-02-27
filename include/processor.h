#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    std::vector<std::string> prev_cpu = std::vector<std::string>(10,"0");
    std::vector<std::string> curr_cpu = std::vector<std::string>(10,"0");
};

#endif