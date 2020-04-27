#include "ConsoleUI.hpp"
#include "DictTree.hpp"
#include <iostream>

int main(){
  HB1::ConsoleUI ui;
  HB1::DictTree dict;
  dict.addWord("test", 4);
  dict.addWord("tests", 5);
  /*
  //ui.getInput();
  ui.askYesNo(NULL);
  int num = ui.askForInt("Enter a number, any number", 0);
  std::cout<<num<<std::endl;
  std::cout<<ui.askForFloat("Now enter a real number")<<std::endl;
  ui.waitForEnter();
  */
}
