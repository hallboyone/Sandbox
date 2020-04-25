#include "UINavigator.hpp"
#include <iostream>

int main(){
  HB1::UINavigator ui;
  ui.askYesNo(NULL);
  int num = ui.askForInt("Enter a number, any number", 0);
  std::cout<<num<<std::endl;
  std::cout<<ui.askForFloat("Now enter a real number")<<std::endl;
  ui.waitForEnter();
}
