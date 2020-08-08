#ifndef MOO_CLASS_NAME
#define MOO_CLASS_NAME

#include <exception>
#include <stdexcept>

class MooClassName{
private:
  /*############################################################################
    ########################### Member Definitions #############################
    ##########################################################################*/
  const //[TYPE AND NAME OF MEMBER TO SORT BY]

  /*[ALL OTHER MEMBERS NEEDED]
    :
    :
  */

  /*############################################################################
    ############################ Private Functions #############################
    ##########################################################################*/
  /*
    :
    :
  */
  
public:
  /*############################################################################
    ############################ Public Functions ##############################
    ##########################################################################*/
  /*
  /* Constructor. */
  MooType(const /*## SORTING VAR ##*/ /*## ALL OTHER VARS ##*/): /*## INITIALIZE SORTING MEMBER ##*/{
    /*## ANYTHING ELSE ##*/
  }

  /* Mergeing function */
  void merge(const MooClassName & rhs){
    if (*this != rhs) throw std::invalid_argument("Trying to merge unequal objects");

    /*## Do any merge operations  ##*/
  }

  bool operator<(const MooClassName & rhs) const{
    return /*## Operation comparing this to rhs  ##*/;
  }
  bool operator==(const MooClassName & rhs) const{
    return (!((*this < rhs)) && !(rhs < (*this)));
  }
  bool operator!=(const MooClassName & rhs) const{
    return (*this < rhs || rhs < (*this));
  }
  bool operator>(const MooClassName & rhs) const{
    return rhs < (*this);
  }

  void print() const{
    /*## Code to print data in class instance ##*/
  }

  /*
    :
    :
    :
  */
};

#endif
