#include <iostream>
#include <stddef.h>
#include "area_map.h"


int main(int argc, char ** argv){
      if (argc != 2){
    std::cout <<"Usage: "<<argv[0]<<" <filename.bmp>\n";
    return 0;
      }

    area_map test(argv[1]);
    test.cleanBMP(3, 5);
    
    return 0;
}
