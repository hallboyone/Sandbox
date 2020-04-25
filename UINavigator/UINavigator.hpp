#ifndef UINAVIGATOR
#define UINAVIGATOR

//Utility class used as a parent for classes which need to communicate with user
namespace HB1{
  class UINavigator{
  public: 
    //Ask user yes or no question.
    bool askYesNo(const char * prompt, int displayInstructions = 1);

    //Numerica data type requests. Calls private helper function askFor
    int askForInt(const char * prompt, int displayInstructions = 1);
    float askForFloat(const char * prompt, int displayInstructions = 1);

    //Holds the program until the user presses Enter
    void waitForEnter(int displayInstructions = 1);

  private:
    enum class DataType{INT, FLOAT};
    
    template <typename T>
    T askFor(DataType requestedDataType, const char * prompt, int displayInstructions);
  };
}
#endif
