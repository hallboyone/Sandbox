#include <stdio.h>
#include <string.h> //strcmp
#include <time.h>

enum cmd_type {DEPOSIT, WITHDRAW, DISP, DISPALL, BALANCE, MKENVL, RMENVL, BAL};

void badCmd();

void parseInput(int argc, char ** argv);
