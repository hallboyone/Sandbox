
#include "CmdLnFlags.hpp"
#include <iostream>
HB1::CmdLnFlags::CmdLnFlags(int argc, char ** argv) : args_(std::vector<std::string>(argc, "")){
  //Save each argument in its raw form into args_
  for(int i = 0; i < argc; i++){
    args_[i] = argv[i];
  }
}

bool HB1::CmdLnFlags::isSetWithPara(const char * key, int & para, bool allow_sh){
  std::string potential_match;
  std::vector<std::string>::iterator cur_arg;
  
  for(cur_arg = args_.begin(); cur_arg != args_.end(); ++cur_arg){
    if(numLeadingChar(*cur_arg, '-') == 2){ //Full flag argument
      potential_match = *cur_arg;
      potential_match.erase(0,2);

      if(potential_match == key) break;
    }
    else if(allow_sh && numLeadingChar(*cur_arg, '-') == 1){ //SH flag arg
      potential_match = *cur_arg;
      potential_match.erase(0,1);

      //If sh char is last char in sh flag group, then we found the match
      if(key[0] == potential_match.back()) break;

      //If match not found, make sure none of the other chars match since
      //we need a parameter
      for(char & c : potential_match){
	if(key[0] == c)//if first char in key matches
	  throw std::invalid_argument("Flag needing integer parameter set without parameter");
      }
    }
  }

  if(cur_arg != args_.end()){//if a match was found, look for parameter in following arg
    ++cur_arg;
    if(cur_arg == args_.end())
      throw std::invalid_argument("Flag needing integer parameter set without parameter");

    if(!verifyIntPara(*cur_arg))
      throw std::invalid_argument("Flag needing integer parameter set with invalid parameter");

    para = std::stoi(*cur_arg);
    return true;
  }
  else return false;
}


//Counts the number of leading '-' in the string 
int HB1::CmdLnFlags::numLeadingChar(const std::string & arg, const char c){
  size_t n = 0;
  while(n < arg.size()){
    if(arg[n] != c){
      break;
    }
    n++;
  }
  return n;
}

bool HB1::CmdLnFlags::verifyDoublePara(const std::string & arg){
  //Make sure that, if '-' exists, it is at the start of string
  if(arg[0]=='-' && arg.find_last_of('-') != 0) return false;

  //Make sure that, if '.' exists, only one exists
  if(arg.find_last_of(".") != arg.find_first_of(".")) return false;

  //Make sure all chars are decimal, dash, or numeric
  if(arg.find_first_not_of("0123456789-.") != std::string::npos) return false;

  return true;
}

bool HB1::CmdLnFlags::verifyIntPara(const std::string & arg){
  //Make sure that, if '-' exists, it is at the start of string
  if(arg[0]=='-' && arg.find_last_of('-') != 0) return false;

  //Make sure all chars are the dash, or are numeric
  if(arg.find_first_not_of("0123456789-") != std::string::npos) return false;

  return true;
}
 
