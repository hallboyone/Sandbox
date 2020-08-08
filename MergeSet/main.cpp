#include "MooType.hpp"
#include "MergeSet.hpp"

#include <iostream>

int main(){
  MooType var1("This", 1);
  MooType var2(" is", 1);
  MooType var3(" a test", 1);
  MooType var4("Will it pass?", 2);

  std::cout<<"var1 < var2 = "<<var1.compare(var2)<<std::endl;
  std::cout<<"var1 < var3 = "<<var1.compare(var3)<<std::endl;
  std::cout<<"var1 < var4 = "<<var1.compare(var4)<<std::endl;
  std::cout<<"var1 > var2 = "<<var2.compare(var1)<<std::endl;
  std::cout<<"var1 > var3 = "<<var3.compare(var1)<<std::endl;
  std::cout<<"var1 > var4 = "<<var4.compare(var1)<<std::endl;
  std::cout<<"var1 = var2 = "<<(var1==var2)<<std::endl;
  std::cout<<"var1 = var3 = "<<(var1==var3)<<std::endl;
  std::cout<<"var1 = var4 = "<<(var1==var4)<<std::endl;
  
  //  var1.merge(var2);
  //  var1.merge(var3);

  var1.print();
  var2.print();
  var3.print();
  var4.print();
  

  //  var1.merge(var4);
  

  MergeSet<MooType> var;
  (var.insert(var1))->print();
  (var.insert(var2))->print();
  (var.insert(var3))->print();
  (var.insert(var4))->print();
  return 1;
}
