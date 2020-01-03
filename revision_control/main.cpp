#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

enum class actType {APPEND = 0, INSERT, DELETE, MODIFY, ERROR};

std::ostream & operator << (std::ostream &out, const actType c)
{
  if (c == actType::APPEND){
    out<<"APPEND";
  }
  else if (c == actType::INSERT){
    out<<"INSERT";
  }
  else if (c == actType::DELETE){
    out<<"DELETE";
  }
  else if (c == actType::MODIFY){
    out<<"MODIFY";
  }
  else{
    out<<"ERROR";
  }
  return out;
}

int main(){
  // actType var = actType::DELETE;
  //actType var_in;
  //int var = 64;
  //int var_in;

  std::string var = "Test Words";
  char * var_buff = new char[256];
  std::string var_in;
  
  std::ofstream file;
  std::ifstream file_in;
  file.open("test.mytest", std::ios::out | std::ios::binary);

  size_t size = var.size();;
  if(size>255){
    std::cout<<"Name to large!\n";
    file.close();
    return 1;
  }
  
  file.write((char*)&size, sizeof(size_t));
  file.write(var.c_str(), size);
  file.close();

  file_in.open("test.mytest", std::ios::in  | std::ios::binary);
  file_in.read((char*)&size, sizeof(size_t));
  file_in.read(var_buff, size);
  file_in.close();

  var_in.assign(var_buff);
  std::cout<<var<<" = "<<var_in<<std::endl;
  delete[](var_buff);
  return 1;
}
