#include "area_map.h"

#define SQ2 1.41421356237


area_map::pixel::pixel(){
  neighbors_raw.resize(8);
  for (size_t i = N; i <= NW; i++){
    neighbors_raw[i] = NULL;
  }

  color = 255;
  is_black = false;
  //std::cout<<min_dists.size()<<std::endl;
}

area_map::pixel::pixel(unsigned char color_){
  neighbors_raw.resize(8);
  for (size_t i = N; i <= NW; i++){
    neighbors_raw[i] = NULL;
  }

  color = color_;
  if ((unsigned int)color_ < 20){
    is_black = true;
  }
  else{
    is_black = false;
  }

  //std::cout<<min_dists.size()<<std::endl;
}
  

void area_map::pixel::connectDiags(){
  //Recursivly call all the other pixels  
  if(neighbors_raw[0] != NULL && coord.first==0){
    neighbors_raw[0]->connectDiags();
  }
  
  if(neighbors_raw[2]!=NULL){
    neighbors_raw[2]->connectDiags();
  }

  //Define diagonals
  if(neighbors_raw[0]!=NULL){
    if(neighbors_raw[6]!=NULL){
      neighbors_raw[7] = (neighbors_raw[6])->neighbors_raw[0];
    }
    if(neighbors_raw[2]!=NULL){
      neighbors_raw[1] = (neighbors_raw[2])->neighbors_raw[0];
    }
  }
  
  if(neighbors_raw[4]!=NULL){
    if(neighbors_raw[6]!=NULL){
      neighbors_raw[5] = neighbors_raw[6]->neighbors_raw[4];
    }
    if(neighbors_raw[2]!=NULL){
      neighbors_raw[3] = neighbors_raw[2]->neighbors_raw[4];
    }
  }

  neighbors = neighbors_raw;
  return;
}

void area_map::pixel::computeDist(){
  if(min_dists.count(this) != 0){
    std::cout<<"Already computed the distances to ("<<coord.first<<","<<coord.second<<")\n";
    return;
  }

  std::queue <area_map::pixel *> pix_q;
  pix_q.push(this); //This pixel will be where we start looking
  min_dists[this] = 0;//It is 0 spaces from here to here
  
  //Call on yourself
  this->computeDist(pix_q, this);
  
  while(pix_q.size() != 0){
    (pix_q.front())->computeDist(pix_q, this);
    pix_q.pop();
  }
}

void area_map::pixel::computeDist(std::queue <area_map::pixel *> & pix_q, area_map::pixel * target){
  for(size_t i = 0; i<=7; i++){
    if(neighbors[i] != NULL){//Does the neighbor exist
      if(!(neighbors[i]->is_black)){//Is the neighbor passable
	if(neighbors[i]->min_dists.count(target) == 0 || neighbors[i]->min_dists[target] > min_dists[target] + one_step[i]){//Is it shorter?
	  pix_q.push(neighbors[i]);
	  neighbors[i]->min_dists[target] = min_dists[target] + one_step[i];
	}
      }
      else{//If the neighbor is not passible
	neighbors[i]->min_dists[target] = 10000000;
      }
    }
  }
  return;
}

area_map::pixel::~pixel(){
  if (neighbors_raw[0] != NULL && coord.first==0){//If we are in the first col
    delete neighbors_raw[0];
  }
  if (neighbors_raw[2]!=NULL){
    delete neighbors_raw[2];
  }
}


//Static variable
std::map<size_t, float> area_map::pixel::one_step = {{0, 1}, {1, SQ2}, {2, 1}, {3, SQ2}, {4, 1}, {5, SQ2}, {6, 1}, {7, SQ2}};
