
#include "InputFlags.hpp"

#include <stdexcept> //invalid_arg
#include <limits>//numeric_limits
#include <iostream> //cout, cerr
#include <fstream> //ifstream
//InputFlags();


void HB1::InputFlags::setFlags(int argc, char ** argv){
  //parse the file if not already done
  if(flags_.empty()) parseFlagTemplates();

  //Make a string vector holding the args. Remove any sh notation
  std::vector<std::string> args = formatInputArgs(argc, argv);

  
  //For each arg, process it based on the number of leading '-' chars
  for(auto arg = args.begin(); arg != args.end(); ++arg){
    if(numLeadingDash(*arg) == 2){//if flag
      std::cout<<"Flag  : "<<*arg<<std::endl;
      inputArg2Flag(arg, args.end());
    }
    else{//If not flag, save into 'other_input_
      other_input_.push_back(*arg);
      std::cout<<"Other : "<<*arg<<std::endl;
    }
  }  
}

//Parse flags.tmpl and build an array of the possible flags.
void HB1::InputFlags::parseFlagTemplates(){
  // Open the file
  std::ifstream f ("flags.tmpl");
  
  if(f.is_open()){
    std::string next_block;
    //While we are not at the end of the file,
    //extract the next block and build a flag struct
    while(extractNextBlock(f, next_block)){
      //Build the flag from the tempate string and add it to vector
      try{
	BuildFlag(next_block);
      }
      catch(std::exception & e){
	std::cout<<e.what()<<std::endl;
      }
    }
    f.close();
  }
  else{
    throw std::ifstream::failure("Could not open file");
  }
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
void HB1::InputFlags::BuildFlag(const std::string & tmpl_str){
  CommandLineFlag new_flag = {readName(tmpl_str),
			      readDesc(tmpl_str),
			      readSH(tmpl_str),
			      readPara_t(tmpl_str),
			      readDefaultPara(tmpl_str)};
  
  //Check uniqueness
  for(const CommandLineFlag & f : flags_){
    if(f.name == new_flag.name){//Names match
      throw std::invalid_argument("Attempted to use duplicate flag name");
    }
    if(f.sh == new_flag.sh){//sh names match
       throw std::invalid_argument("Attempted to use duplicate flag name shorthand");
    }
  }
  
  //Chech that the default para matches the para_t
  if(new_flag.default_para.size() != 0){
    switch(new_flag.para_t){
    case NONE:
      throw std::invalid_argument("Specified default parameter with specifying parameter type");
      break;
    case INT:
      std::stoi(new_flag.default_para);
      break;
    case DOUBLE:
      std::stod(new_flag.default_para);
      break;
    case CHAR:
      if(new_flag.default_para.size() != 1){
	throw std::invalid_argument("Specified default char parameter with more than 1 char");
      }
      break;
    default: //STRING
      break;
    }
  }
  
  flags_.push_back(new_flag);
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
  if(!readKeyValue(root_string, "desc=\"", 6, desc, '"')) {//With quotes
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

HB1::InputFlags::DataType HB1::InputFlags::readPara_t(const std::string & root_string){
  std::string para_t;
  if(readKeyValue(root_string, "para_t=", 7, para_t)){
    for(size_t i = 0; i<para_t.size(); i++){
      para_t[i] = tolower(para_t[i]);
    }
    if(para_t == "int") return INT;
    else if (para_t == "double") return DOUBLE;
    else if (para_t == "char") return CHAR;
    else if (para_t == "string") return STRING;
    else return NONE;
  }
  else return NONE;
}

std::string HB1::InputFlags::readDefaultPara(const std::string & root_string){
  std::string default_para;
  //Read default_para. First try with quotes, then without
  if(!readKeyValue(root_string, "default_para=\"", 14, default_para, '"')){
    readKeyValue(root_string, "default_para=", 13, default_para);
  }
  return default_para;
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
  size_t n = 0;
  while(n < arg.size()){
    if(arg[n] != '-'){
      break;
    }
    n++;
  }
  return n;
}

//Reads through an input string vector and converts any sh notation to full names
std::vector<std::string> HB1::InputFlags::formatInputArgs(int argc, char ** argv){
  std::vector<std::string> args;
  std::string cur_arg;
  for(int i = 0; i<argc; i++){
    cur_arg = argv[i];
    
    //If arg is sh notation, convert to lh
    if(numLeadingDash(cur_arg) == 1){
      cur_arg.erase(0,1); //Erase dash
      for(char & c : cur_arg){//For each sh char in arg
	//Get flag with sh 'c' and add its name led by -- to args
	if(getFlagWithName(std::string(1,c), true) == flags_.end()){
	  throw std::invalid_argument("Did not recoginize a sh char");
	}
	args.push_back(std::string("--"));
	args.back() += (getFlagWithName(std::string(1,c), true)->name);
      }
    }
    else{//If not in sh notation, add as is
      args.push_back(std::string(argv[i]));
    }
  }
  return args;
}

//Reads the Flag pointed at by it. Must start with '--'
//it is moved to the last element in args used to process the flag
void HB1::InputFlags::inputArg2Flag(std::vector<std::string>::iterator & it, const std::vector<std::string>::iterator & args_end){
  std::string name = *it;
  name.erase(0,2); //Erase the two leading '--'

  //  try{
    //Find the flag among flags_
    std::vector<CommandLineFlag>::iterator f_it = getFlagWithName(name, false);
    if(f_it->active == true) throw std::invalid_argument("Flag added twice.");
    
    f_it->active = true;
    
    
    //Read the parameter if needed.
    if(f_it->para_t != NONE){
      if(it+1 != args_end && numLeadingDash(*(it+1)) != 2){ // If parameter is given
	switch(f_it->para_t){
	case INT:
	  try{
	    std::stoi(*(it+1)); //Will throw excpetion if invalid
	    ++it;
	    f_it->para = *it;
	  }
	  catch(std::exception & e){
	    if(f_it->default_para.size() == 0){
	      throw std::invalid_argument("Flag requiring parameter missing parameter\n");
	    }
	    std::cerr<<"Could not read int parameter value. Using default\n";
	    f_it->para = f_it->default_para;
	  }
	  break;
	case DOUBLE:
	  try{
	    std::stod(*(it+1)); //Will throw excpetion if invalid
	    ++it;
	    f_it->para = *it;
	  }
	  catch(std::exception & e){
	    if(f_it->default_para.size() == 0){
	      throw std::invalid_argument("Flag requiring parameter missing parameter\n");
	    }
	    std::cerr<<"Could not read double parameter value. Using default\n";
	    f_it->para = f_it->default_para;
	  }
	  break;
	case CHAR:
	  if((it+1)->size() != 1){
	    throw std::invalid_argument("Char parameter with more than 1 char in string");
	  }
	  ++it;
	  f_it->para = (*it)[0];
	  break;
	case STRING:
	  ++it;
	  f_it->para = *it;
	  break;
	default:
	  break;
	}
      }
      else{ //No input flags
	if(f_it->default_para.size() == 0){
	  throw std::invalid_argument("Flag requiring parameter missing parameter\n");
	}
	f_it->para = f_it->default_para;
      }
    }

    printFlag(*f_it);
    //}
    //catch{
    //ADD CATCH STATMENTS
    //}
}

//Searches through flags_ for one that matches "name".
std::vector<HB1::InputFlags::CommandLineFlag>::iterator HB1::InputFlags::getFlagWithName(const std::string & name, bool is_sh){
  //Make sure that, if is_sh, that the name only has a single char
  if(is_sh && name.size() != 1){
    throw std::invalid_argument("Asked for Flag by shorthand notation using more than 1 char");
  }
  
  std::vector<CommandLineFlag>::iterator cur_flag;
  for(cur_flag = flags_.begin(); cur_flag != flags_.end(); ++cur_flag){
    if(is_sh){
      if(name[0] == cur_flag->sh) return cur_flag;
    }
    else{
      if(name == cur_flag->name) return cur_flag;
    }
  }
  return flags_.end();
}

void HB1::InputFlags::printFlag(const CommandLineFlag & flag){
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
  std::cout<<"Default Para   : "<<flag.default_para<<std::endl;
  std::cout<<"Para Value     : "<<flag.para<<std::endl;
}
