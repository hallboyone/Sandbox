#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

enum class actType {APPEND = 0, INSERT, DELETE, MODIFY, ERROR};

typedef struct action_{
  size_t ID;
  size_t idx;
  actType type;
  int amount;
} action;
  
class myClass{
private:
  std::vector<int> v;
  size_t v_size;
  std::vector<action> log;
  size_t log_ID;
public:
  myClass():v_size(0), log_ID(0){
    return;
  }

  myClass(std::vector<action> & full_log):v_size(0), log_ID(0){
    for (std::vector<action>::iterator it = full_log.begin(); it<full_log.end(); ++it){
      switch(it->type){
      case actType::APPEND:
	createBin(it->amount);
	break;
      case actType::INSERT:
	createBin(it->amount, it->idx);
	break;
      case actType::DELETE:
	deleteBin(it->idx);
	break;
      case actType::MODIFY:
	modBin(it->amount, it->idx);
      default:
	break;
      }
    }
    return;
  }

  myClass(const char * filename):v_size(0), log_ID(0){
    std::vector<action> tmp_log;
    loadClass(filename, tmp_log);
    for (std::vector<action>::iterator it = tmp_log.begin(); it<tmp_log.end(); ++it){
      switch(it->type){
      case actType::APPEND:
	createBin(it->amount);
	break;
      case actType::INSERT:
	createBin(it->amount, it->idx);
	break;
      case actType::DELETE:
	deleteBin(it->idx);
	break;
      case actType::MODIFY:
	modBin(it->amount, it->idx);
      default:
	break;
      }
    }
    return;
  } 
    
  
  action modBin(int amount, size_t loc){
    action act;
    act.ID = log_ID;
    log_ID++;
    act.idx = loc;
    act.amount = amount;
    act.type = actType::MODIFY;
    if(loc>=v_size){
      std::cout<<"Could not access element\n";
      act.type = actType::ERROR;
    }
    else{
      v[v_size-loc-1] += amount;
    }
    log.push_back(act);
    return act;
  }
  
  action deleteBin(size_t loc = 0){
    action act;
    act.ID = log_ID;
    log_ID++;
    act.idx = loc;
    act.amount = 0;
    act.type = actType::DELETE;
    if(v_size==0 || loc>v_size){
      std::cout<<"Could not delete element\n";
      act.type = actType::ERROR;
    }
    else if (loc==0){
      v.pop_back();
      v_size--;
    }
    else{
      std::vector<int>::iterator it = v.end();
      for (size_t i = 0; i<loc; i++){
	--it;
      }
      v.erase(--it);
      v_size--;
    }
    log.push_back(act);
    return act;
  }
      
  action createBin(int amount, size_t loc = 0){
    action act;
    act.ID = log_ID;
    log_ID++;
    act.idx = loc;
    act.amount = amount;
    
    if (loc==0){//Append a new bin
      v.push_back(amount);
      v_size++;
      act.type = actType::APPEND;
    }
    else if (loc > v_size){//the location was out of scope
      std::cout<<"That location is invalid!\n";
      act.type = actType::ERROR;
    }
    else{
      std::vector<int>::iterator it = v.end();
      for (size_t i = 0; i<loc; i++){
	--it;
      }
      v.insert(it, amount);
      v_size++;
      act.type = actType::INSERT;
    }
    log.push_back(act);
    return act;
  }

  void saveClass(const char * filename){
    std::cout<<"Saving the class into "<<filename<<".myclass\n";
    std::ofstream f;
    std::string full_name(filename);
    full_name.append(".myclass");
    f.open(full_name, std::ios::out | std::ios::binary);
    size_t n = log.size();
    f.write((char*) &n, sizeof(n));
    for (std::vector<action>::iterator it = log.begin(); it<log.end(); ++it){
      f.write((char*)&(it->ID), sizeof(it->ID));
      f.write((char*)&(it->type), sizeof(it->type));
      f.write((char*)&(it->idx), sizeof(it->idx));
      f.write((char*)&(it->amount), sizeof(it->amount));
      std::cout<<"ID:"<<it->ID<<", Type:"<<int(it->type)<<", Amount:"<<it->amount<<std::endl;
    }
    f.write("\0", sizeof("\0"));
    f.close();
    return;
  }

  void loadClass(const char * filename, std::vector<action> & tmp_log){
    std::ifstream f;
    std::string full_name(filename);

    full_name.append(".myclass");
    f.open(full_name, std::ios::in  | std::ios::binary);
    
    //int enum_flag = 0;
    size_t n;
    f.read((char*) &n, sizeof(n));
    for(size_t i=0; i<n; i++){
      action new_act;
      f.read((char*)&new_act.ID, sizeof(new_act.ID));
      f.read((char*)&new_act.type, sizeof(new_act.type));
      f.read((char*)&new_act.idx, sizeof(new_act.idx));
      f.read((char*)&new_act.amount, sizeof(new_act.amount));      
      std::cout<<"ID:"<<new_act.ID<<", Type:"<<int(new_act.type)<<", Amount:"<<new_act.amount<<std::endl;
      tmp_log.push_back(new_act);
    }
    f.close();
    return;
  }

  friend std::ostream & operator << (std::ostream &out, const myClass &c);
};

std::ostream & operator << (std::ostream &out, const myClass &c)
{
  out << "[ ";
  for(size_t i = 0; i<c.v_size; i++){
    out<<c.v[i];
    if (i<c.v_size-1){
      out<<", ";
    }
  }
  out<<" ]";
  return out;
}

int main(){
  myClass test;
  std::vector<action> log;
  log.push_back(test.createBin(100));
  log.push_back(test.createBin(-30));
  log.push_back(test.createBin(650));
  log.push_back(test.createBin(0, 1));
  log.push_back(test.deleteBin(3));
  log.push_back(test.modBin(100, 2));

  log.push_back(test.createBin(100));
  log.push_back(test.createBin(-30));
  log.push_back(test.createBin(650));
  log.push_back(test.createBin(0, 1));
  log.push_back(test.deleteBin(3));
  log.push_back(test.modBin(100, 2));

  log.push_back(test.createBin(100));
  log.push_back(test.createBin(-30));
  log.push_back(test.createBin(650));
  log.push_back(test.createBin(0, 1));
  log.push_back(test.deleteBin(3));
  log.push_back(test.modBin(100, 2));

  log.push_back(test.createBin(100));
  log.push_back(test.createBin(-30));
  log.push_back(test.createBin(650));
  log.push_back(test.createBin(0, 1));
  log.push_back(test.deleteBin(3));
  log.push_back(test.modBin(100, 2));

  log.push_back(test.createBin(100));
  log.push_back(test.createBin(-30));
  log.push_back(test.createBin(650));
  log.push_back(test.createBin(0, 1));
  log.push_back(test.deleteBin(3));
  log.push_back(test.modBin(100, 2));

  log.push_back(test.createBin(100));
  log.push_back(test.createBin(-30));
  log.push_back(test.createBin(650));
  log.push_back(test.createBin(0, 1));
  log.push_back(test.deleteBin(3));
  log.push_back(test.modBin(100, 2));

  std::cout<<test<<"\n"<<myClass(log)<<"\n";
  test.saveClass("test");
  std::cout<<myClass("test")<<std::endl;
  // std::vector<action> log_2;
  // std::ifstream f;
  // f.open("test.myClass", std::ios::in);
  // f >> log_2;
  // std::cout<<myClass(log_2)<<std::endl;
  // f.close;
  return 1;
}
