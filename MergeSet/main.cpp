#include "MooType.hpp"
#include "MergeSet.hpp"

#include <iostream>

int main(){
  MooType var1("This", -10);
  MooType var2(" is", -10);
  MooType var3(" a test", -10);
  MooType var4("Will it pass?", -2);
  MooType var5("I hope", 1);
  MooType var6(" it will", 1);
  MooType var7("But we will", 2);
  MooType var8(" have to see", 2);
  /*
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
  */

  MergeSet<MooType> var;
  var.insert(var1);
  var.insert(var2);
  var.insert(var7);
  var.insert(var5);
  var.insert(var3);
  var.insert(var4);
  var.insert(var6);
  var.insert(var8);

  var.printSet();
  return 1;
}
