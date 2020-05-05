
#include "InputFlags.hpp"

#include <stdexcept> //invalid_arg
#include <limits>//numeric_limits
#include <iostream> //cout, cerr
#include <fstream> //ifstream
//InputFlags();


void HB1::InputFlags::setFlags(int argc, char ** argv){
  //parse the file if not already done
  if(flags_.empty()) parseFlagTemplates();

  //Make a string vector holding the args
  std::vector<string> args;
  for(int i = 0; i<argc; i++){
    args.push_back(argv[i]);
  }

  for(auto arg = args.begin(); arg != args.end(); ++args){
    switch(numLeadingDash(*arg)){
    case 1:
      readFlagSH(arg, args);
      break;
    case 2:
      readFlag(arg, args);
      break;
    case 0:
    default:
      other_input_.push_back(*arg);
    }
  }
}

//Parse flags.tmpl and build an array of the possible flags.
void HB1::InputFlags::parseFlagTemplates(){
  // Open the file
  std::ifstream f ("flags.tmpl");
  
  if(f.is_open()){
    std::string nextBlock;
    //While we are not at the end of the file,
    //extract the next block and build a flag struct
    while(extractNextBlock(f, nextBlock)){
      //Build the flag from the tempate string and add it to vector
      flags_.push_back(BuildFlag(nextBlock));
    }
    f.close();
  }
  else{
    throw std::ifstream::failure("Could not open file");
  }

  ensureUniqueFlags();
}


//Moves forward in the ifstream to the begining of the first '{' not in a comment
int HB1::InputFlags::move2BlockStart(std::ifstream & f){
  char next_char;

  //Move to start of block, skipping any comments or extra chars
  while(f.get(next_char)){
    if(next_char == '{'){
      break;
    }
    else if(next_char == '/' && f.peek()=='/'){
      //Move to end of comment
      f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  //If no valid open brace was found before EOF
  if(f.eof()) return 0;
  return 1;
}

//Finds the next block in the file and saves the valid chars into block
int HB1::InputFlags::extractNextBlock(std::ifstream & f, std::string & block){
  //Move to the start of the block
  if(!move2BlockStart(f)){
    return 0;
  }
  
  char next_char;
  bool in_quotes = false;
  
  block.clear();
  while(f.get(next_char)){
    if(next_char == '"'){
      in_quotes = !in_quotes;
    }

    if(!in_quotes){
      if(next_char == '}'){
	break;
      }
      else if(next_char == '/' && f.peek()=='/'){
	//Move to end of comment
	f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else if(validBlockChar(next_char)){ 
	block.append(&next_char);
      }
    }
    else{
      block.append(&next_char);
    }
  }
  
  //If no valid close brace was found before EOF
  if(f.eof()) return 0;
  return 1;
}

//Checks if char is one that should be saved from within flag template block
bool HB1::InputFlags::validBlockChar(const char & c){
  return (isalnum(c) || c=='=' || c==';' || c=='"' || c=='_');
}
  
//Takes the block template string and uses it to make a new flag
HB1::InputFlags::Flag HB1::InputFlags::BuildFlag(std::string & s){
  Flag flag = {readName(s), readDesc(s), readSH(s), readPara(s)};
  return flag;
}
  
//Finds and varifies the the indicated field from a block template string
std::string HB1::InputFlags::readName(const std::string & root_string){
  std::string name;
  //Read name
  if(!readKeyValue(root_string, "name=", 5, name)) {
    throw std::invalid_argument("Could not find any name key");
  }
  //Make sure only valid chars are used
  if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyz_0123456789") != std::string::npos){
    throw std::invalid_argument("Name not valid");
  }
  //Make sure the name begins and ends with alpha
  if(!isalpha(name[0]) || !isalpha(name.back())){
    throw std::invalid_argument("Name not valid. Must start and and with alpha char");
  }
  return name;
}

std::string HB1::InputFlags::readDesc(const std::string & root_string){
  std::string desc;
  //Read desc
  if(!readKeyValue(root_string, "desc=\"", 6, desc)) {//With quotes
    if(!readKeyValue(root_string, "desc=", 5, desc)) {//without quotes
    throw std::invalid_argument("No description found for flag");
    }
  }
  return desc;
}

char HB1::InputFlags::readSH(const std::string & root_string){
  std::string sh;
  if(readKeyValue(root_string, "sh=", 3, sh)){
    if(sh.size() != 1 || !isalpha(sh[0])){
      return '\0';
    }
    return sh[0];
  }
  else{
    return '\0';
  }
}

HB1::InputFlags::DataType HB1::InputFlags::readPara(const std::string & root_string){
  std::string para;
  if(readKeyValue(root_string, "para=", 5, para)){
    for(size_t i = 0; i<para.size(); i++){
      para[i] = tolower(para[i]);
    }
    if(para == "int") return INT;
    else if (para == "double") return DOUBLE;
    else if (para == "char") return CHAR;
    else if (para == "string") return STRING;
    else return NONE;
  }
  else return NONE;
}

//Finds the key in the string and extracts the chars up to the desired delim char
int HB1::InputFlags::readKeyValue(const std::string & s, const char * key, size_t len, std::string & val, char delim ){
  
  size_t start_of_key = s.find(key);
  if(start_of_key == std::string::npos){
    return 0;
  }
  
  size_t start_of_val = start_of_key + len;
  size_t end_of_val = s.find_first_of(delim, start_of_val);
  if(end_of_val == std::string::npos){
    return 0;
  }
  
  val = s.substr(start_of_val, end_of_val-start_of_val);
  return 1;
}

//Counts the number of leading '-' in the string 
int HB1::InputFlags::numLeadingDash(const std::string & arg){
  int n = 0;
  while(n < arg.size()){
    if(arg[n] != '-'){
      break;
    }
    n++;
  }
  return n;
}

//Reads the Flag pointed at by it. Must start with '--'
//it is moved to the last element in args used to process the flag
void HB1::InputFlags::inputArg2Flag(std::vector<string>::iterator & it, const std::vector<string>::iterator & args_end, bool sh){
  std::string name = *it;
  if(sh) name.erase(0,1); //Erase the leading '-'
  else   name.erase(0,2); //Erase the two leading '--'

  try{
    //Find the flag among flags_
    std::vector<Flag>::iterator f_it = getFlagWithName(name, sh);
    f_it->active = true;

    //Read the parameter if needed.
    if(f_it->para_t != NONE){
      if(it+1 != args_end){ // If parameter is given
	switch(f_it->para_t){
	case INT:
	  f_it->data = readIntPara(*(it+1));
	  break;
	case DOUBLE:
	  f_it->data = readDoublePara(*(it+1));
	  break;
	case CHAR:
	  f_it->data = readCharPara(*(it+1));
	  break;
	case STRING:
	  f_it->data = readStringPara(*(it+1));
	  break;
	}
      }
    }
  }
  catch{
    //ADD CATCH STATMENTS
  }
}

void HB1::InputFlags::printFlag(const Flag & flag){
  std::cout<<"Name           : "<<flag.name<<std::endl;

  std::cout<<"Description    : "<<flag.desc<<std::endl;

  std::cout<<"Shorthand      : ";
  if(flag.sh != '\0') std::cout<<flag.sh<<std::endl;
  else std::cout<<"None\n";
  
  std::cout<<"Parameter type : ";
  switch(flag.para_t){
  case INT:
    std::cout<<"Int\n";
    break;
  case DOUBLE:
    std::cout<<"Double\n";
    break;
  case CHAR:
    std::cout<<"Char\n";
    break;
  case STRING:
    std::cout<<"String\n";
    break;
  default:
    std::cout<<"None\n";
  }   
}
