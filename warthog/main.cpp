#include "area_map.h"

int main(int argc, char** argv){
  size_t x = 0;
  size_t y;
  size_t x0;
  size_t y0;
  area_map map(argv[1], false);
  map.clean(1, 1, 5);
  map.setRawRes(4);
  map.setRes(3);
  
  while(true){
    std::cout<<"Starting x (1000 to end): ";
    std::cin>>x0;
    if (x0==1000){
      return 1;
    }
    std::cout<<"Starting y: ";
    std::cin>>y0;
    std::cout<<"Ending x: ";
    std::cin>>x;
    std::cout<<"Ending y: ";
    std::cin>>y;
    std::cout<<"\n";
    map.printDir(x0, y0, x, y);
  }
}
