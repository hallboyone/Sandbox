#include "MooType.hpp"
#include "MergeSet.hpp"

#include <iostream>

int main(){
  /*
  MooType var1("This", -10);
  MooType var2(" is", -10);
  MooType var3(" a test", -10);
  MooType var4("Will it pass?", -2);
  MooType var5("I hope", 1);
  MooType var6(" it will", 1);
  MooType var7("But we will", 2);
  MooType var8(" have to see", 2);
  
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

  MooType v1("1", 64);
  MooType v2("2", 32);
  MooType v3("3", 96);
  MooType v4("4", 16);
  MooType v5("5", 48);
  MooType v6("6", 80);
  MooType v7("7", 112);
  MooType v8("8", 8);
  MooType v9("9", 24);
  MooType v10("10", 40);
  MooType v11("11", 56);
  MooType v12("12", 72);
  MooType v13("13", 88);
  MooType v14("14", 104);
  MooType v15("15", 120);
  MooType v16("16", 28);
  MooType v17("17", 52);
  MooType v18("18", 60);
  MooType v19("19", 100);
  MooType v20("20", 108);
  MooType v21("21", 124);
  MooType v22("22", 26);
  MooType v23("23", 30);
  MooType v24("24", 62);
  MooType v25("25", 98);
  MooType v26("26", 102);
  MooType v27("27", 106);
  MooType v28("28", 110);
  MooType v29("29", 126);
  MooType v30("30", 25);
  MooType v31("31", 27);
  MooType v32("32", 31);
  MooType v33("33", 61);
  MooType v34("34", 63);
  MooType v35("35", 105);
  MooType v36("36", 125);
  MooType v37("37", 127);
  
  MergeSet<MooType> var;
  var.insert(v1);
  var.insert(v2);
  var.insert(v3);
  var.insert(v4);
  var.insert(v5);
  var.insert(v6);
  var.insert(v7);
  var.insert(v8);
  var.insert(v9);
  var.insert(v10);
  var.insert(v11);
  var.insert(v12);
  var.insert(v13);
  var.insert(v14);
  var.insert(v15);
  var.insert(v16);
  var.insert(v17);
  var.insert(v18);
  var.insert(v19);
  var.insert(v20);
  var.insert(v21);
  var.insert(v22);
  var.insert(v23);
  var.insert(v24);
  var.insert(v25);
  var.insert(v26);
  var.insert(v27);
  var.insert(v28);
  var.insert(v29);
  var.insert(v30);
  var.insert(v31);
  var.insert(v32);
  var.insert(v33);
  var.insert(v34);
  var.insert(v35);
  var.insert(v36);
  var.insert(v37);
  var.erase(v9);
  var.printSet();
  return 1;
}
