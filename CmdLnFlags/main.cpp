#include "CmdLnFlags.hpp"
#include <iostream>

int main(int argc, char * argv[]){
  HB1::CmdLnFlags flags(argc, argv);
  int i = 0;
  char c = 'n';
  double d = 3.1415;
  
  if(flags.isSet("bool", true)){
    std::cout<<"Found the bool flag.\n";
  }
  else{
    std::cout<<"bool flag not found\n";
  }

  if(flags.isSetWithOptPara("int", i, true)){
    std::cout<<"Found the int flag with value of "<<i<<"\n";
  }
  else{
    std::cout<<"Int flag not found\n";
  }

  if(flags.isSetWithOptPara("double", d, true)){
    std::cout<<"Found the double flag with value of "<<d<<"\n";
  }
  else{
    std::cout<<"Double flag not found\n";
  }

  if(flags.isSetWithOptPara("char", c, true)){
    std::cout<<"Found the char flag with value of "<<c<<"\n";
  }
  else{
    std::cout<<"Char flag not found\n";
  }

  flags.warnUnused();
  flags.warnUnused("Unused flags!!");
  return 1;
}
