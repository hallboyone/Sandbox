#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcmp
#include <time.h>
#include <math.h> //modf
#include <time.h>
#include <ctype.h> //isalnum

enum cmd_type {DEPOSIT, WITHDRAW, DISP, DISPALL, BALANCE, MKENVL, RMENVL, BAL};

enum catagory {AUTO, BILLS, EDU, ENTERTAINMENT, FOOD, GAS, GIFTS, GROCERIES, HEALTH, HOME, PERSONAL, SERVICES, SHOPPING, TRAVEL, TITHE, OTHER};

typedef struct envolope_{
  const time_t ID;
  float bal;
  char * name;
  size_t name_len;
  enum catagory cat;
} envolope;


void badCmd();

void parseInput(int argc, char ** argv);

void buildFilename(const char * id, char * filename);

int saveEnvl(envolope * e);
int openEnvl(const char * id, envolope * e);

void makeEnvl();

void printEnvl();

size_t printCat(enum catagory c);

void printWarn(const char * msg);

void redText();
void blackText();
void yellowText();
