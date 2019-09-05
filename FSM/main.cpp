#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "node.h"

int main(int argc, char ** argv){
  if(argc != 2){
    std::cerr<<"Incorrect input.\nUsage: /nsf [FILE NAME]\n";
    return 1;
  }
  
  std::fstream f (argv[1], std::fstream::in);
  if(!f.is_open()){
    std::cerr<<"Could no open file\n";
    return 1;
  }

  //Parse input
  std::string new_line;
  getline(f, new_line);
  while(!new_line.empty()){
    std::cout<<new_line<<std::endl;
    getline(f, new_line);
  }
  
  f.close();
  return 0;
}
