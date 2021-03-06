#ifndef CONSOLE_UI
#define CONSOLE_UI

#include <stddef.h>
#include "DictTree.hpp"

//Utility class used as a parent for classes which need to communicate with user
namespace HB1{
  class ConsoleUI{
  public:
    ConsoleUI();
    
    //Ask user yes or no question.
    bool askYesNo(const char * prompt, int displayInstructions = 1);

    //Numerica data type requests. Calls private helper function askFor
    int askForInt(const char * prompt, int displayInstructions = 1);
    float askForFloat(const char * prompt, int displayInstructions = 1);

    //Holds the program until the user presses Enter
    void waitForEnter(int displayInstructions = 1);

    void getInput();
    
    ~ConsoleUI();
  private:
    //Custom Types
    enum class DataType{INT, FLOAT};
    enum class Key{DEL, TAB, RET, ESC, ALNUM};
    
    typedef struct UIOptions_{
      bool echo = true;
      bool autoComplete = true;
    } UIOptions;
    
    //Members
    char * buf_;
    size_t bufSize_;
    size_t bufCap_;
    UIOptions ops_;
    Key lastKey_;
    
    DictTree dict_;
    size_t completionLen_;
    
    //Private methods
    template <typename T>
    T askFor(DataType requestedDataType, const char * prompt, int displayInstructions);
    

    void clearBuf();
    void add2Buf(const char c);
    void delFromBuf();
    int btoi();
    double btod();
    void autoComplete();
    //Keypress functions
    void kpDel();
    void kpTab();
  };
}
#endif
