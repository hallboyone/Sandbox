#include "function_decl.h"


int main(int argc, char ** argv){
  if (argc == 1){
    badCmd();
  }

  else{
    parseInput(argc, argv);
  }
  
  return 1;
}
