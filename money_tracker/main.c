#include <stdio.h>

void badCmd();

void parseInput(int argc, char ** argv);


int main(int argc, char ** argv){
  if (argc == 1){
    badCmd();
  }

  else{
    parseInput(argc, argv);
  }
  
  return 1;
}

void badCmd(){
  printf("Invalid command. Use money_tracker -h for additionl help.\n");
  return;
}

void parseInput(int argc, char ** argv){
  argv += 1;
  argc -= 1;

  if(*argv == "add"){
    printf("Adding\n");
  }
  return;
}
