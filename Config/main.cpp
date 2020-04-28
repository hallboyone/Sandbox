
#include <iostream>
#include <vector>
#include <string>

//enum class typeName {STR, INT, DBL, U_INT, U_DBL};

template <class T>
class Field{
private:
  T data_;
  std::string name_;
public:
  Field(T data, std::string name): data_(data), name_(name){}

  T get(){
    return data_;
  }
  bool isNamed(const char * name){
    return name_==name;
  }
  std::string name(){
    return name_;
  }
};

class ConfigData{
private:
  std::vector<Field<int>> i_vect_;
  std::vector<Field<double>> d_vect_;

  //Set of functions to get the correct data vector
  template <class T>
  std::vector<Field<T>> & getVect(){
    throw "Unknown config variable type\n";
  }
  template <> std::vector<Field<int>> & getVect<int>(){
    return i_vect_;
  }
  template <> std::vector<Field<double>> & getVect<double>(){
    return d_vect_;
  }
  
public:
  ConfigData(){
    std::string name("I1");    
    i_vect_.push_back(Field<int>(3, name));
    name = "I2";
    i_vect_.push_back(Field<int>(-3, name));
    name = "D1";
    d_vect_.push_back(Field<double>(3.14159265, name));
    name = "D2";
    d_vect_.push_back(Field<double>(3.14159265, name));
  }

  template <class T>
  void add(const char * name, T val){
    std::vector<Field<T>> & vec = getVect<T>();
    for(Field<T> & f : vec){
      if(f.isNamed(name)){
	std::cout<<"Already a parameter named "<<name<<"\n";
	return;
      }
    }
    vec.push_back(Field<T>(val, std::string(name)));
    return;
  }
  
  template <class T>
  T get(const char * name){
    for(Field<T> & f : getVect<T>()){
      if(f.isNamed(name)){
	return f.get();
      }
    }
    std::cerr<<"No matches found for "<<name<<std::endl;
    throw "No matching parameter";    
  }
};
    
  
int main(){
  ConfigData c;
  int i = c.get<int>("I1");
  double d = c.get<double>("D1");
  std::cout<<i<<" "<<d<<std::endl;
  c.add<double>("D3", 2.7);
  c.add<double>("D3", 2.7);
  std::cout<<c.get<double>("D3")<<"\n";
  return 0;
}
