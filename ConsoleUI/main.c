//#include "ConsoleUI.hpp"
//#include "DictTree.hpp"
#include <stdio.h>

enum Colors {BLACK, RED, NONE};

void set_color(Colors cl){
  switch(cl){
  case BLACK:
    printf("\u001b[30m");
    break;
  case RED:
    printf("\u001b[31m");
    break;
  case NONE:
  default:
    printf("\u001b[0m");
  }
  return;
}

int main(){
  set_color(RED);
  printf("This is a test, Hello World\n");
  set_color(BLACK);
  /*
  //HB1::ConsoleUI ui;
  
  //  printf("%s\n", completion);
  
  ui.getInput();
  ui.askYesNo(NULL);
  ui.askForInt("Enter a whole number");
  ui.askForFloat("Now enter a real number");
  ui.waitForEnter();
  */
}
