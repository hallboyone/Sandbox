#include "function_decl.h"

int saveEnvl(envolope * e);
int openEnvl(const char * id, envolope * e);

int main(int argc, char ** argv){
  if (argc == 1){
    badCmd();
  }

  else{
    parseInput(argc, argv);
  }

  envolope e1;
  envolope e2;
  
  e1.bal = 123.21;
  e1.name = malloc(100*sizeof(char));
  e2.name = malloc(100*sizeof(char));
  e1.name[0] = 'T';
  e1.name[1] = 'e';
  e1.name[2] = 's';
  e1.name[3] = 't';
  e1.name[4] = '\0';
  e1.name_len = 5;
  
  saveEnvl(& e1);
  openEnvl("Test", & e2);
  
  free(e1.name);
  free(e2.name);
  return 1;
}

void badCmd(){
  printf("Invalid command. Use money_tracker -h for additionl help.\n");
  return;
}
