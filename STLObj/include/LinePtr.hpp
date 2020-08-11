#ifndef LINE_PTR
#define LINE_PTR

#include "Coord.hpp"
#include "TriPtr.hpp"

class LinePtr{
private:
  const Coord<3> *const v_[2];
  bool first_v_smallest;
  TriPtr * t_[2];
public:
  LinePtr(const Coord<3> * v1, const Coord<3> * v2, TriPtr * t): v_{v1,v2}{
    t_[0] = t;
    t_[1] = NULL;
    if (v_[0] < v_[1]) first_v_smallest = true;
    else first_v_smallest = false;
  }
  
  TriPtr * t(int n) const{
    return t_[n];
  }

  const Coord<3> *const vSmall() const{ return v_[1 - first_v_smallest]; };
  const Coord<3> *const vLarge() const{ return v_[first_v_smallest]; };
  
  
  void merge(const LinePtr & rhs){
    if (*this != rhs) throw std::invalid_argument("Trying to merge unequal edges");
    if (t_[1] != NULL) throw std::invalid_argument("Edge used by more than 2 tri");
    if (rhs.t(1) != NULL) throw std::invalid_argument("Edge used by more than 2 tri");

    t_[1] = rhs.t(0);
  }

  bool operator<(const LinePtr & rhs) const{
    if (*(this->vSmall()) != *(rhs.vSmall()))
      return ((*(this->vSmall())) < (*(rhs.vSmall())));
    else
      return ((*(this->vLarge())) < (*(rhs.vLarge())));
  }
  
  bool operator==(const LinePtr & rhs) const{
    return (!((*this < rhs)) && !(rhs < (*this)));
  }
  bool operator!=(const LinePtr & rhs) const{
    return (*this < rhs || rhs < (*this));
  }
  bool operator>(const LinePtr & rhs) const{
    return rhs < (*this);
  }

  void print() const{
    std::cout<<*(vSmall())<<"--"<<*(vLarge());
    if (t_[0] != NULL && t_[1] != NULL){
      std::cout<<" between t"<<((t_[0])->id())<<" and t"<<((t_[1])->id());
    }
    std::cout<<std::endl;
  }
  //  ~LinePtr(){

  //}
};
#endif
