#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcmp
#include <time.h>
#include <math.h> //modf

enum cmd_type {DEPOSIT, WITHDRAW, DISP, DISPALL, BALANCE, MKENVL, RMENVL, BAL};

typedef struct envolope_{
  float bal;
  char * name;
  size_t name_len;
} envolope;


void badCmd();

void parseInput(int argc, char ** argv);

void buildFilename(const char * id, char * filename);


