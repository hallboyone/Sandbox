#include "ConsoleUI.hpp"
#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdexcept> //invalid_argument
//=========================================================================
//====================== Constructors/Destructors =========================
//=========================================================================

HB1::ConsoleUI::ConsoleUI(){
  bufCap_ = 4095;
  bufSize_ = 0;
  buf_ = new char [bufCap_];
  buf_[0] = '\0';
  ops_.echo = true;
}

HB1::ConsoleUI::~ConsoleUI(){
  delete[] buf_;
}

//=========================================================================


//=========================================================================
//========================= Buffer Operations =============================
//=========================================================================

/* Resets the buf size to 0 and writes the terminating char to first spot */
void HB1::ConsoleUI::clearBuf(){
  bufSize_ = 0;
  buf_[0] = '\0';
}

/*Add a single char to the buffer. Double buffer's capacity if needed*/
void HB1::ConsoleUI::add2Buf(const char c){
  //Resize if needed
  if(bufCap_ == bufSize_ + 1){
    char * newBuf = new char [bufCap_ * 2];
    memcpy(newBuf, buf_, bufCap_*sizeof(char));
    delete[] buf_;
    buf_ = newBuf;
    bufCap_ *= 2;
  }

  //Add char to buf
  buf_[bufSize_] = c;
  bufSize_++;
  buf_[bufSize_] = '\0';
}

/* Deletes the last inserted char from the buf. If buf is empty, nothing is deleted */
void HB1::ConsoleUI::delFromBuf(){
  if(bufSize_ > 0){
    bufSize_--;
    buf_[bufSize_] = '\0';
  }
}

/* Convert the contents of the buffer to an integer */
int HB1::ConsoleUI::btoi(){
  int num = 0;           //integer to be returned
  int nextDigit = 0;     //the current digit in the buf
  char * curChar = buf_; //the current char in the buf
  bool negVal = false;   //flag indicating if the value is negative

  //Move past white space
  while(*curChar == ' ') curChar++;
  
  //Check if value is negative
  if(*curChar == '-'){
    negVal = true;
    curChar++;
  }

  while(*curChar != '\0' && *curChar != '\n'){
    nextDigit = (*curChar) - '0';
    if(nextDigit<0 || nextDigit>9){
      throw std::invalid_argument("Non numeric digit found");
    }
    curChar++;
    num = num*10 + nextDigit;
  }

  if(negVal){
    num *= -1;
  }
  
  return num;
}

/* Convert the contents of the buffer to a double */
double HB1::ConsoleUI::btod(){
  double num = 0;        //number to be returned
  double pwrOfTen = 0.1; //multiple for the fractional component
  int nextDigit = 0;     //next digit read from buffer
  char * curChar = buf_; //pointer to the current char in buffer
  bool negVal = false;   //flag indicating negative value
  bool foundDec = false; //flag indicating if a dec point was read
  
  //Move initial past white space
  while(*curChar == ' ') curChar++;
  
  //Check if value is negative
  if(*curChar == '-'){
    negVal = true;
    curChar++;
  }

  //Read all chars up to null of new line
  while(*curChar != '\0' && *curChar != '\n'){
    //Response at decimal point
    if(*curChar == '.'){
      if(foundDec){
	throw std::invalid_argument("Two decimal points found");
      }
      foundDec = true;
    }
    else{
      //shift by the int value of the char 0
      nextDigit = (*curChar) - '0';

      //Make sure number is a digit
      if(nextDigit < 0 || nextDigit > 9){
	throw std::invalid_argument("Non numeric digit found");
      }
      //If in fractional portion
      if(foundDec){
	num = num + nextDigit*pwrOfTen;
	pwrOfTen /= 10;
      }
      //If in integer portion
      else{
	num = num*10 + nextDigit;
      }
    }
    curChar++;
  }

  if(negVal){
    num *= -1;
  }
  
  return num;
}

//=========================================================================


//=========================================================================
//=========================== IO Operations ===============================
//=========================================================================

/*
 Reads each key press from the user and processes the input. Most chars are stored in the
 buffer but special chars are handled by the respective key-press functions. 
 Uses info from https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar
 */
void HB1::ConsoleUI::getInput(){
  clearBuf();
  
  int c;
  static struct termios oldTermSettings;
  static struct termios newTermSettings;

  //Save the old terminal settings 
  tcgetattr(STDIN_FILENO, &oldTermSettings);

  //Make new terminal settings from old
  newTermSettings = oldTermSettings;
  newTermSettings.c_lflag &= ~(ICANON | ECHO); //Set local modes
  
  //Use new settings
  tcsetattr(STDIN_FILENO, TCSANOW, &newTermSettings);
  
  do{// Loop reading, processing, and responding to input
    c = getchar();
    switch(c){
    case 9://Tab
      kpTab();
      break;
    case 127://Del
      kpDel();
      break;
    default:
      if(ops_.echo) putchar(c); //write to terminal
      add2Buf(c); //Save into buffer
    }
  } while(c != '\n');
  
  //Set back to old settings
  tcsetattr(STDIN_FILENO, TCSANOW, &oldTermSettings);
  return;
}

//=========================================================================


//=========================================================================
//======================== User Input Requests ============================
//=========================================================================

bool HB1::ConsoleUI::askYesNo(const char * prompt, int displayInstructions){
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

      getInput();
    }
  while(buf_[0]!='y' && buf_[0]!='n');

  //Return result
  if(buf_[0]=='y'){
    return true;
  }
  else{
    return false;
  }
}

void HB1::ConsoleUI::waitForEnter(int displayInstructions){
  if(displayInstructions != 0){
    std::cout<<" [press Enter to continue] \n > ";
  }
  ops_.echo = false;
  getInput();
  ops_.echo = true;
}
  

//Wrapper functions to ask for numeric data types
int HB1::ConsoleUI::askForInt(const char * prompt, int displayInstructions){
  return askFor<int>(DataType::INT, prompt, displayInstructions);
}

float HB1::ConsoleUI::askForFloat(const char * prompt, int displayInstructions){
    return askFor<float>(DataType::FLOAT, prompt, displayInstructions);
}


//Private method called by wrapper functions above. Type T must match the requestedDataType
template <typename T>
T HB1::ConsoleUI::askFor(DataType requestedDataType, const char * prompt, int displayInstructions){
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
    //Get user input and save in buf_
    getInput();

    //Switch based on data type requested
    switch (requestedDataType){
      
    case DataType::INT:
      try{// to return stored integer value
	return btoi();
      }
      catch(std::exception& e){
	std::cout<<"Did not recoginize input. Please enter a whole number like '-14' or '31415'.\n > ";
      }
      break;
      
    case DataType::FLOAT:
      try{// to return stored floating point value
	return btod();
      }
      catch(std::exception& e){
	std::cout<<"Did not recoginize input. Please enter a number like '-14' or '3.1415'.\n > ";
      }
      break;
    }

    //Continue running until user enters valid input
  } while(1);
}

//=========================================================================


//=========================================================================
//======================== Key-press handelers ============================
//=========================================================================

void HB1::ConsoleUI::kpDel(){
  if(ops_.echo){
    printf("\b \b");
  }
  delFromBuf();
}

void HB1::ConsoleUI::kpTab(){
  /*
  if(ops_.autoComplete != NULL){
    autoComplete();
    return;
  }
  */
  
  if(ops_.echo) printf("\t");
  
  add2Buf('\t');
}

