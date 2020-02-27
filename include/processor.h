#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    unsigned long int PrevIdle {0};
    unsigned long int Idle;

    unsigned long int PrevNonIdle {0};
    unsigned long int NonIdle;

    unsigned long int PrevTotal{0};
    unsigned long int Total;

    unsigned long int totald;
    unsigned long int idled;

    float CPU_Percentage;



};

#endif