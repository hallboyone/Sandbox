#include "area_map.h"
 
area_map::pixel_::pixel_(){
  neighbors[area_map::pixel_::dir::NW] = NULL;
  neighbors[area_map::pixel_::dir::N] = NULL;
  neighbors[area_map::pixel_::dir::NE] = NULL;
  neighbors[area_map::pixel_::dir::E] = NULL;
  neighbors[area_map::pixel_::dir::SE] = NULL;
  neighbors[area_map::pixel_::dir::S] = NULL;
  neighbors[area_map::pixel_::dir::SW] = NULL;
  neighbors[area_map::pixel_::dir::W] = NULL;

  is_black = false;
  id_building_ = 0;
}
area_map::pixel_::pixel_(bool is_black_){
  neighbors[area_map::pixel_::dir::NW] = NULL;
  neighbors[area_map::pixel_::dir::N] = NULL;
  neighbors[area_map::pixel_::dir::NE] = NULL;
  neighbors[area_map::pixel_::dir::E] = NULL;
  neighbors[area_map::pixel_::dir::SE] = NULL;
  neighbors[area_map::pixel_::dir::S] = NULL;
  neighbors[area_map::pixel_::dir::SW] = NULL;
  neighbors[area_map::pixel_::dir::W] = NULL;

  is_black = is_black_;
  id_building_ = 0;
}

//pixel_::pixel_(bool is_black, std::map<std::string, pixel_ *> neighbors);
area_map::pixel_::~pixel_(){
  if (neighbors[area_map::pixel_::dir::W]==NULL){//If we are in the first col
    delete neighbors[area_map::pixel_::dir::N];
  }
  delete neighbors[area_map::pixel_::dir::E];
}
