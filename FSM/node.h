#include <string>
#include <map>


class node{
 private:
  std::map<size_t, node *> trans_fun_;
  std::string name_;
  int accepting_;

 public:
 node(std::string name):name_(name){
    accepting_ = 0;
  }


  
  ~node(){
    std::cout<<"Destroying "<<name_<<std::endl;
  }
};
