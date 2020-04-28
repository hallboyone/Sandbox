

#include <iostream>
#include <utility>
#include <vector>
#include <math.h>

class Wrapper{
private:
  int num_;
  int abs_num_;

public:
  Wrapper(int n){
    num_ = n;
    abs_num_ = abs(n);
  }
  int & get(){
    return num_;
  }
  const int & getAbs(){
    return abs_num_;
  }
  
  void set(int n){
    num_ = n;
    abs_num_ = abs(n);
    return;
  }
};
  
int main(){
  Wrapper w(10);
  std::cout<<w.get()<<std::endl;
  int & num_ref = w.get();
  std::cout<<num_ref<<std::endl;
  w.set(15);
  std::cout<<w.get()<<std::endl;
  std::cout<<num_ref<<std::endl;
  return 1;
}
