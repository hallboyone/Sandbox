#include "UINavigator.hpp"
#include <string>
#include <iostream>

bool HB1::UINavigator::askYesNo(const char * prompt, int displayInstructions){
  std::string input;
  bool firstTimeAsking = true;
  do
    {
      if(firstTimeAsking){ //then prompt the user for input
	if(prompt != NULL){
	  std::cout << prompt;
	}
	if(displayInstructions!=0){
	  std::cout<<" [y/n]";
	}
	std::cout<<"\n > ";
    	firstTimeAsking = false;
      }

      //If we have asked before, than clearly the input was not valid. Re-prompt
      else{
	std::cout<<"Could not recoginize input. Please only enter 'y' or 'n'.\n > ";
      }

      //Get input
      getline(std::cin, input);
    }
  while( !std::cin.fail() && input!="y" && input!="n");

  //Return result
  if(input=="y"){
    return true;
  }
  else{
    return false;
  }
}

void HB1::UINavigator::waitForEnter(int displayInstructions){
  if(displayInstructions != 0){
    std::cout<<" [press Enter to continue] ";
  }
  std::cin.ignore();
}
  

//Wrapper functions to ask for numeric data types
int HB1::UINavigator::askForInt(const char * prompt, int displayInstructions){
  return askFor<int>(DataType::INT, prompt, displayInstructions);
}

float HB1::UINavigator::askForFloat(const char * prompt, int displayInstructions){
    return askFor<float>(DataType::FLOAT, prompt, displayInstructions);
}


//Private method called by wrapper functions above. Type T must match the requestedDataType
template <typename T>
T HB1::UINavigator::askFor(DataType requestedDataType, const char * prompt, int displayInstructions){
  std::string input;
    
  //Prompt the user
  if(prompt != NULL){
    std::cout << prompt;
  }
  if(displayInstructions!=0){
    switch (requestedDataType){
    case DataType::INT:
      std::cout<<" [enter a whole number]";
      break;
    case DataType::FLOAT:
      std::cout<<" [enter a number]";
      break;
    }
  }
  std::cout<<"\n > ";
    
  do {
    //Get input
    getline(std::cin, input);
      
    try{// to conver to the requestedDataType
      T num;
      switch (requestedDataType){
      case DataType::INT:
	num = std::stoi(input);
	if(input.find_first_not_of("1234567890-")!=std::string::npos){
	  std::cout<<"Ignored some chars\n";
	}
	break;
      case DataType::FLOAT:
	num = std::stof(input);
	if(input.find_first_not_of("1234567890-.")!=std::string::npos){
	  std::cout<<"Ignored some chars\n";
	}
	break;
      }

      return num;
    }
    //If input was invalid, re-prompt and repeat
    catch (std::exception& e){
      switch (requestedDataType){
      case DataType::INT:
	std::cout<<"Did not recoginize input. Please enter a whole number like '-14' or '31415'.\n > ";
	break;
      case DataType::FLOAT:
	std::cout<<"Did not recoginize input. Please enter a number like '-14' or '3.1415'.\n > ";
	break;
      }
    }
  }
  while(1);
}
