
#ifndef CMD_LN_FLAGS
#define CMD_LN_FLAGS

#include <string>
#include <vector>

namespace HB1{
  class CmdLnFlags{
  private:
    //Vector holding each of the command line arguments
    std::vector<std::string> args_;

    /**
     * Counts the number of chars at the start of the string 'arg' with match
     * the char 'c'. Useful to count the number of dashes in front of an element
     * of args_
     */
    int numLeadingChar(const std::string & arg, const char c);

    /**
     * Verifies that the string 'arg' contains numeric chars and, if a dash is
     * present, it is at the start of the string
    */
    bool verifyIntPara(const std::string & arg);

    /**
     * Verifies that the string 'arg' contains only numeric chars, if a dash is
     * present, it is at the start of the string, and, if a period is present,
     * there is only one
    */
    bool verifyDoublePara(const std::string & arg);
  public:
    CmdLnFlags(int argc, char ** argv);

    /**
     *   Checks if a flag matching the key has been set. If it has, return true 
     * and look at the next arg for an int parameter. If it exists, set the 
     * assign para to its value. Otherwise, throw an invalid_argument. 
     *   If a matching para is not found, false is returned and para is left
     * unchanged. 
     *   If allow_sh is true, a flag in shorthand notation only need 
     * match the first char. 
     */
    bool isSetWithPara(const char * key, int & para, bool allow_sh = false);

    /**
     * Checks if a flag matching the key has been set. If it has, return true 
     * and look at the next arg for an int parameter. If it exists, set the 
     * assign para to its value. Otherwise, the value of para remains unchanged.
     * If a matching para is not found, false is returned and para is left
     * unchanged. If allow_sh is true, a flag in shorthand notation only need 
     * match the first char. 
     */
    bool isSetWithOptPara(const char * key, int & para, bool allow_sh = false);
  };
}
#endif //CMD_LN_FLAGS
