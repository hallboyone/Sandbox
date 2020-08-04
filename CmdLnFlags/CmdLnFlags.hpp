
#ifndef CMD_LN_FLAGS
#define CMD_LN_FLAGS

#include <string>
#include <vector>
#include <utility> //pair

namespace HB1{
  /**
   * Abstracts the usage of command line flags. Basic workflow is to construct
   * an instance using the command line args (argc and argv) and then check status
   * of flags using provided function calls (isSetWithPara -> check if flag is set
   * and has a parameter of the given type). 
   */
  class CmdLnFlags{
  private:
    /**
     * \brief Type containing arg and bool indicating if arg has been used
     */
    typedef std::pair<std::string, bool> FlagPair; 
    
    /**
     * Vector holding the command line arguments and boolean flags indicating if they have been used
     */
    std::vector<FlagPair> args_;

    /**
     * Find flag matching the key and return an iterator to it. If no matching flag
     * is found, returns args_.end()
     */
    std::vector<FlagPair>::iterator findFlag(const char * key, bool allow_sh = false);
    
    /**
     * Counts the number of chars at the start of the string 'arg' with match
     * the char 'c'. Useful to count the number of dashes in front of an element
     * of args_
     */
    int static numLeadingChar(const std::string & arg, const char c);

    /**
     * Verifies that the string 'arg' contains numeric chars and, if a dash is
     * present, it is at the start of the string
    */
    bool static verifyIntPara(const std::string & arg);

    /**
     * Verifies that the string 'arg' contains only numeric chars, if a dash is
     * present, it is at the start of the string, and, if a period is present,
     * there is only one
    */
    bool static verifyDoublePara(const std::string & arg);

    /**
     * Verifies that the string 'arg' is only a single char
    */
    bool verifyCharPara(const std::string & arg);
    
  public:
    /**
     * Constructor. Builds the argument vector out of the elements of argv.
     * If a flag group is found ("-fvm"), it is split into individual elements
     * in args_ ([-f, -v, -m]).
     */
    CmdLnFlags(int argc, char ** argv);

    /** \brief Check if flag is set.
     *
     *   Checks if a flag matching the key has been set. If it has, return true.
     * Else, return false.
     *   If allow_sh is true, a flag in shorthand notation only need 
     * match the first char. 
     */
    bool isSet(const char * key, bool allow_sh = false);

    ///@{
    /** \brief Check if flag is set and get its required parameter value.
     *
     * Returns true if flag has been set, false otherwise.
     *
     * If the flag is found, it must be followed by a parameter of the appropriate
     * type. If it is not, an invalid_argument exception is thrown. If it is, 
     * assign its value to para.
     *
     * If allow_sh is true, a flag in shorthand notation (i.e., "-f") only need 
     * match the first char or key
     * @param key A char array specifying the full name of flag
     * @param para The variable the parameter should be stored in
     * @param allow_sh Allow the function to match the first char of key to a sh flag
     */
    bool isSetWithPara(const char * key, int & para, bool allow_sh = false);
    /**
     * \overload
     */
    bool isSetWithPara(const char * key, double & para, bool allow_sh = false);
    /**
     * \overload
     */
    bool isSetWithPara(const char * key, char & para, bool allow_sh = false);
    ///@}

    ///@{
    /** \brief Check if flag is set and get its optional parameter value.
     *
     * Returns true if flag has been set, false otherwise.
     *
     * If the flag is found, check if it is followed by a parameter of the 
     * appropriate type. If it is, assign its value to para. Else para is unchanged.
     *
     * If allow_sh is true, a flag in shorthand notation (i.e., "-f") only need 
     * match the first char or key
     * @param key A char array specifying the full name of flag
     * @param para The variable the parameter should be stored in if found
     * @param allow_sh Allow the function to match the first char of key to a sh flag
     */
    bool isSetWithOptPara(const char * key, int & para, bool allow_sh = false);
    /** 
     * \overload
     */
    bool isSetWithOptPara(const char * key, double & para, bool allow_sh = false);
    /** 
     * \overload
     */
    bool isSetWithOptPara(const char * key, char & para, bool allow_sh = false);
    ///@}

    /** \brief Print all argument strings in args_
     *
     * If the argument has not been used, it is printed in red. Else, it is printed in green.
     */
    void printFlags();

    /** \brief Print a warning about any unused arguments
     *
     * Any argument in args_ that is not used is printed alongside a warning message
     * @param msg Char array supplying a warning message. If NULL, default message is used
     * @return The number of unused parameters
     */
    int warnUnused(const char * msg = NULL);
  };
}
#endif //CMD_LN_FLAGS
