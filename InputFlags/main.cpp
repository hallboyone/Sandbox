#include "InputFlags.hpp"
#include "CmdLnFlags.hpp"
#include <iostream>

int main(int argc, char * argv[]){
  HB1::CmdLnFlags flags(argc, argv);

  if(flags.isSet("verbose", true)){
    std::cout<<"Found the verbose flag.\n";
  }
  else{
    std::cout<<"Verbose flag not found\n";
  }

  double verbose_level = 0;
  if(flags.isSetWithPara("verbose", verbose_level, true)){
    std::cout<<"Found the verbose flag with value of "<<verbose_level<<"\n";
  }
  else{
    std::cout<<"Verbose flag not found\n";
  }
  return 1;
}
