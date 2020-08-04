#ifndef MOOTYPE
#define MOOTYPE

#include <string>
#include <exception>
#include <stdexcept>

class MooType{
private:
  std::string str_;
  int num_;
public:
  MooType(const char * s, int n){
    str_ = s;
    num_ = n;
  }
  
  std::string str() const { return str_; }
  int num() const { return num_; }

  /**
   * Merges the object, rhs, into *this. The function must leave
   * the comparison field unchanged.
   **/
  void merge(MooType & rhs){
    if (*this != rhs) throw std::invalid_argument("Trying to merge unequal objects");
    str_.append(rhs.str());
  }

  /**
   * Base comparison function. All others are derived from this.
   * Function must have the property that, if a.compare(b) is true, 
   * b.compare(a) will also return true if and only if a and b are
   * equivalent. 
   **/
  bool compare(const MooType & rhs) const{ // this < rhs
    return (num_ < rhs.num());
  }

  bool operator==(const MooType & rhs) const{
    return ((!compare(rhs)) && (!rhs.compare(*this)));
  }
  bool operator!=(const MooType & rhs) const{
    return (compare(rhs) || rhs.compare(*this));
  }
  bool operator<(const MooType & rhs) const{
    return compare(rhs);
  }
  bool operator>(const MooType & rhs) const{
    return !compare(rhs);
  }
};

#endif
