#include "InputFlags.hpp"

int main(int argc, char * argv[]){
  HB1::InputFlags flags;
  flags.setFlags(argc, argv);
  return 1;
}
