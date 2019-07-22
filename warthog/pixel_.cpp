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

void area_map::pixel_::connectDiags(){
  //Recursivly call all the other pixels  
  if(neighbors[area_map::pixel_::dir::N]!=NULL && x_coord==0){
    neighbors[area_map::pixel_::dir::N]->connectDiags();
  }
  
  if(neighbors[area_map::pixel_::dir::E]!=NULL){
    neighbors[area_map::pixel_::dir::E]->connectDiags();
  }
  

  //Defined diagonals
  if(neighbors[area_map::pixel_::dir::N]!=NULL){
    if(neighbors[area_map::pixel_::dir::W]!=NULL){
      neighbors[area_map::pixel_::dir::NW] = (neighbors[area_map::pixel_::dir::W])->neighbors[area_map::pixel_::dir::N];
    }
    if(neighbors[area_map::pixel_::dir::E]!=NULL){
      neighbors[area_map::pixel_::dir::NE] = (neighbors[area_map::pixel_::dir::E])->neighbors[area_map::pixel_::dir::N];
    }
  }
  
  if(neighbors[area_map::pixel_::dir::S]!=NULL){
    if(neighbors[area_map::pixel_::dir::W]!=NULL){
      neighbors[area_map::pixel_::dir::SW] = neighbors[area_map::pixel_::dir::W]->neighbors[area_map::pixel_::dir::S];
    }
    if(neighbors[area_map::pixel_::dir::E]!=NULL){
      neighbors[area_map::pixel_::dir::SE] = neighbors[area_map::pixel_::dir::E]->neighbors[area_map::pixel_::dir::S];
    }
  }
  return;
}
  
//pixel_::pixel_(bool is_black, std::map<std::string, pixel_ *> neighbors);
area_map::pixel_::~pixel_(){
  if (neighbors[area_map::pixel_::dir::W]==NULL){//If we are in the first col
    delete neighbors[area_map::pixel_::dir::N];
  }
  delete neighbors[area_map::pixel_::dir::E];
}
