#include "ConsoleUI.hpp"
#include "DictTree.hpp"
#include <iostream>

int main(){
  HB1::ConsoleUI ui;
  HB1::DictTree dict;
  dict.addWord("cat", 3);
  dict.addWord("cats", 4);
  dict.addWord("crate", 5);
  dict.addWord("cab", 3);
  dict.addWord("crack", 5);
  dict.addWord("crack01", 7);
  dict.addWord("crack20", 7);
  dict.addWord("fat", 3);
  
  std::cout<<"#1 "<<dict.findCompletion("c", 1, false)<<std::endl;
  std::cout<<"#2 "<<dict.findCompletion("c", 1, false)<<std::endl;
  std::cout<<"#3 "<<dict.findCompletion("c", 1, false)<<std::endl;
  std::cout<<"#4 "<<dict.findCompletion("c", 1, false)<<std::endl;
  std::cout<<"#5 "<<dict.findCompletion("c", 1, false)<<std::endl;
  std::cout<<"#6 "<<dict.findCompletion("c", 1, false)<<std::endl;
  std::cout<<"#5 "<<dict.findCompletion("c", 1, false)<<std::endl;
  std::cout<<"#6 "<<dict.findCompletion("c", 1, false)<<std::endl;
  
  //  printf("%s\n", completion);
  /*
  //ui.getInput();
  ui.askYesNo(NULL);
  int num = ui.askForInt("Enter a number, any number", 0);
  std::cout<<num<<std::endl;
  std::cout<<ui.askForFloat("Now enter a real number")<<std::endl;
  ui.waitForEnter();
  */
}
