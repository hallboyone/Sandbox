
#include "CmdLnFlags.hpp"
#include <iostream>

HB1::CmdLnFlags::CmdLnFlags(int argc, char ** argv) : args_(std::vector<std::string>(argc, "")){
  //Save each argument in its raw form into args_
  for(int i = 0; i < argc; i++){
    args_[i] = argv[i];
  }

  //Split up sh flag groups ([...,-fvm,...] becomes [...,-f,-v,-m,...])
  for(auto it = args_.begin(); it != args_.end(); ++it){
    //If current string is sh group, split it
    if (numLeadingChar(*it, '-') ==  1 && !verifyDoublePara(*it) && it->size() > 2){
      std::vector<std::string> split_sh_group;
     
      for (auto it_char = it->begin() + 1; it_char != it->end(); ++it_char){
	//Make sure all chars after the first are letters
	if(!std::isalpha(*it_char)) throw std::invalid_argument("Invalid SH group found");
	
	//Add new element to group vector. Start with a dash and then add the char
	split_sh_group.push_back(std::string("-"));
	split_sh_group.back() += *it_char; 
      }

      //Erase old group, insert split group, reset 'it'
      it = args_.erase(it);
      args_.insert(it, split_sh_group.begin(), split_sh_group.end());
      it = args_.begin();
    }
  }
}

bool HB1::CmdLnFlags::isSet(const char * key, bool allow_sh){
  return (findFlag(key, allow_sh) != args_.end());
}

bool HB1::CmdLnFlags::isSetWithPara(const char * key, int & para, bool allow_sh){
  std::vector<std::string>::iterator matching_arg = findFlag(key, allow_sh);
  
  if (matching_arg != args_.end()){//if a match was found, look for parameter in following arg
    ++matching_arg;
    if (matching_arg == args_.end())
      throw std::invalid_argument("Flag needing integer parameter set without parameter");

    if (!verifyIntPara(*matching_arg))
      throw std::invalid_argument("Flag needing integer parameter set with invalid parameter");

    para = std::stoi(*matching_arg);
    return true;
  }
  else return false;
}

bool HB1::CmdLnFlags::isSetWithPara(const char * key, double & para, bool allow_sh){
  std::vector<std::string>::iterator matching_arg = findFlag(key, allow_sh);
  
  if (matching_arg != args_.end()){//if a match was found, look for parameter in following arg
    ++matching_arg;
    if (matching_arg == args_.end())
      throw std::invalid_argument("Flag needing integer parameter set without parameter");

    if (!verifyDoublePara(*matching_arg))
      throw std::invalid_argument("Flag needing integer parameter set with invalid parameter");

    para = std::stod(*matching_arg);
    return true;
  }
  else return false;
}

std::vector<std::string>::iterator HB1::CmdLnFlags::findFlag(const char * key, bool allow_sh){
  std::string potential_match;
  std::vector<std::string>::iterator cur_arg;
  
  for (cur_arg = args_.begin(); cur_arg != args_.end(); ++cur_arg){
    if (numLeadingChar(*cur_arg, '-') == 2){ //Full flag argument
      potential_match = *cur_arg;
      potential_match.erase(0,2);

      if (potential_match == key) return cur_arg;
    }
    else if (allow_sh && numLeadingChar(*cur_arg, '-') == 1){ //SH flag arg
      //Check argument only if it is not a negative numeric parameter
      if (!verifyDoublePara(*cur_arg)){
	//If sh char matches the sh flag, then we found the match
	if (key[0] == cur_arg->back()) return cur_arg;
      }
    }
  }

  return cur_arg;
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
 
