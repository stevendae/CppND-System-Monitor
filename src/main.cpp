#include "ncurses_display.h"
#include "system.h"

#include <vector>
#include "process.h"
#include <iostream>
#include "string.h"

int main() {
  System system;
  //std::vector <Process> test = system.Processes();
  //float cpu = test[0].CpuUtilization();
  //std::cout << cpu << std::endl;
  NCursesDisplay::Display(system);
}