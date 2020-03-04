#include "ncurses_display.h"
#include "system.h"

#include <vector>
#include "process.h"
#include <iostream>
#include "string.h"

int main() {
  System system;
  /*
  std::vector <Process> test = system.Processes();
  std::string variable = test[0].Command();
  std::cout << variable << std::endl;
  */
  NCursesDisplay::Display(system);
}