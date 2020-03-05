#include "ncurses_display.h"
#include "system.h"

#include <vector>
#include "process.h"
#include <iostream>
#include "string.h"

int main() {
  System system;

  
  NCursesDisplay::Display(system);
}