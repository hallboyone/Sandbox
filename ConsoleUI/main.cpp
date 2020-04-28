#include "ConsoleUI.hpp"
#include "DictTree.hpp"
#include <iostream>

int main(){
  HB1::ConsoleUI ui;
  
  //  printf("%s\n", completion);
  
  ui.getInput();
  ui.askYesNo(NULL);
  ui.askForInt("Enter a whole number");
  ui.askForFloat("Now enter a real number");
  ui.waitForEnter();
  
}
