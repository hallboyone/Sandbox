
/*
Objective - Provide functions to read an input and seek any flags of the form -[chars] or --[chars].

The developer should be able to indicate what chars and strings are valid. Perhaps the user can make a flags class and an internal method can do the parsing. This could set internal flags so then the user could call flag.is_set(v) which would return true or false depending on if the flag was used. 

A challange is still letting the user define the flags they wish to recoginize. Obviously somthing like
flag.add_new("v", "verbose", "Display additional output") is possible but not very user freindly. 
Alternitivly, there could be a base Flags class that implements the is_set functions and many standard flag keys. The user, if they wished to customize it, could then inherit from the class and set their own values.  
How would the developer index to the flags? The chorthand char could be used (i.e. flag.is_set('v')). This is probably the only option that would work well. That means that this method is
bool is_set(const char sh); //Shorthand index
bool is_set(const char * lh);//Longhand index

What if the flags have parameters as well? For example, "./a.out --itr 5". The some flags need inputs and others do not. Further, the types of the paras may change. What if there were getter functions that would work like
int get_i(const char sh);
double get_d(const char sh);
char get_d(const char sh);
const char * get_s(const char sh);

Calling get_i, for example, would check if the flag indexed by the input parameter has data type int. If so,
it would return the parameter. Otherwise, it would throw an error. 

Maybe a flag struct could be useful to hold all of this. 

enum DataType {NONE, INT, DOUBLE, CHAR, STRING}

struct Flag{
const char nameSH;
const char * nameLH;
const char * desc;
const char * data; //Data is stored as a c string but is checked when stored
const DataType para_t;
}


There could also be a flag template file. This would have fields such as
{
 name-LH : itr                  // Long hand name of parameter
 name-SH : n                    // Short hand name of parameter
 desc    : Number of iterations // Description of flag. Used by helper functions
 para    : none                 // What type is the para. (int, double, string, char, or none)
}
for every desired flag. When the InputFlags object gets created, it could use this file
to create a vector of Flags. The names in the template file must be unique and they could
be skipped by adding a '\' in front of them. 
 */

#include <string>
#include <vector>

class InputFlags {
public:
  enum DataType {NONE, INT, DOUBLE, CHAR, STRING};

  typedef struct Flag_{
    const char nameSH;
    const std::string nameLH;
    const std::string desc;
    const std::string data;
    const DataType para_t;
  } Flag;

  std::vector<Flag> flags;

  InputFlags(int argc, char ** argv){
    
