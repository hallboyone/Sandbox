#include "area_map.h"

int main(int argc, char** argv){
  size_t x = 5;
  size_t y = 3;
  size_t x0 = 0;
  size_t y0 = 0;
  
  area_map map(argv[1], 4, false);
  map.getDists(x, y);
  map.printDir(x0, y0, x, y);
  //1) Deletes the current map_data grid (unless map_data==raw_data)
  //2) Creates a new grid from the raw data that trims noise and adds a buffer to the black objects
  //  map.clean(3, 5);
  
  //map.setRes(1); //Simplifies the map_data to have just 1 pixel/meter. This res must be less than the constructor res
}
