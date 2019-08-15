#include <iostream>
#include <utility>
#include <vector>

int main(){
  std::vector<std::pair<size_t, size_t> > numbers(8);
  size_t num;
  
  for(size_t i=8; i<16; i++){
    numbers[i-8].first = i;
    num = (i-7)/2;
    num *= 2;
    numbers[i-8].second = num;

    num = (num+2+4*(-1*(i%2)))%8;
    
    std::cout<<numbers[i-8].first<<","<<numbers[i-8].second<<","<<num<<std::endl;
  }
  return 1;
}
