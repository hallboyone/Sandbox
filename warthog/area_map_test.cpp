#include "area_map.h"

area_map::area_map(){
  head = new area_map::pixel_;
}

area_map::~area_map(){
  delete head;
}
