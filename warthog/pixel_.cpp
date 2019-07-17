#include "area_map.h"
 
area_map::pixel_::pixel_(){
  neighbors_[area_map::pixel_::dir::NW] = NULL;
  neighbors_[area_map::pixel_::dir::N] = NULL;
  neighbors_[area_map::pixel_::dir::NE] = NULL;
  neighbors_[area_map::pixel_::dir::E] = NULL;
  neighbors_[area_map::pixel_::dir::SE] = NULL;
  neighbors_[area_map::pixel_::dir::S] = NULL;
  neighbors_[area_map::pixel_::dir::SW] = NULL;
  neighbors_[area_map::pixel_::dir::W] = NULL;

  is_black_ = false;
  id_building_ = 0;
}
area_map::pixel_::pixel_(bool is_black){
  neighbors_[area_map::pixel_::dir::NW] = NULL;
  neighbors_[area_map::pixel_::dir::N] = NULL;
  neighbors_[area_map::pixel_::dir::NE] = NULL;
  neighbors_[area_map::pixel_::dir::E] = NULL;
  neighbors_[area_map::pixel_::dir::SE] = NULL;
  neighbors_[area_map::pixel_::dir::S] = NULL;
  neighbors_[area_map::pixel_::dir::SW] = NULL;
  neighbors_[area_map::pixel_::dir::W] = NULL;

  is_black_ = is_black;
  id_building_ = 0;
}

//pixel_::pixel_(bool is_black, std::map<std::string, pixel_ *> neighbors);
area_map::pixel_::~pixel_(){
  if (neighbors_[area_map::pixel_::dir::N]!=NULL){
    delete neighbors_[area_map::pixel_::dir::N];
  }
  if (neighbors_[area_map::pixel_::dir::E]!=NULL){
    delete neighbors_[area_map::pixel_::dir::E];
  }
  if (neighbors_[area_map::pixel_::dir::W]!=NULL){
    (*neighbors_[area_map::pixel_::dir::W]).neighbors_[area_map::pixel_::dir::W] = NULL;
  }

  if (neighbors_[area_map::pixel_::dir::SW]!=NULL){
    (*neighbors_[area_map::pixel_::dir::SW]).neighbors_[area_map::pixel_::dir::NW] = NULL;
  }
  if (neighbors_[area_map::pixel_::dir::S]!=NULL){
    (*neighbors_[area_map::pixel_::dir::S]).neighbors_[area_map::pixel_::dir::N] = NULL;
}
}
