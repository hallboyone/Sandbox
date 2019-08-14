#include "function_decl.h"

void parseInput(int argc, char ** argv){
  argc -= 1;
  enum cmd_type cmd;

  //Identify the command type
  if(!strcmp(argv[1], "deposit")){
    cmd = DEPOSIT;
  }
  else if (!strcmp(argv[1], "withdraw")){
    cmd = WITHDRAW;
  }
  else if (!strcmp(argv[1], "disp")){
    cmd = DISP;
  }
  else if (!strcmp(argv[1], "disp-all")){
    cmd = DISPALL;
  }
  else if (!strcmp(argv[1], "bal")){
    cmd = BAL;
  }
  else if (!strcmp(argv[1], "mkenvl")){
    cmd = MKENVL;
  }
  else if (!strcmp(argv[1], "rmenvl")){
    cmd = RMENVL;
  }
  else{
    badCmd();
    return;
  }
  
  return;
}
