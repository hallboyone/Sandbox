#include "area_map.h"

#define SQ2 1.41421

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
}

void area_map::pixel_::connectDiags(){
  //Recursivly call all the other pixels  
  if(neighbors[area_map::pixel_::dir::N]!=NULL && coord.first==0){
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

void area_map::pixel_::dist2Here(){
  std::queue <area_map::pixel_ *> pix_q;
  
  pix_dist[coord] = 0;

  //Call on yourself
  this->checkAround(pix_q, coord);
  
  while(pix_q.size() != 0){
    (pix_q.front())->checkAround(pix_q, coord);
    pix_q.pop();
  }
}

void area_map::pixel_::checkAround(std::queue<area_map::pixel_ *> & pix_q, std::pair<size_t, size_t> & target){
  pixel_* n  = neighbors[area_map::pixel_::dir::N];
  pixel_* ne = neighbors[area_map::pixel_::dir::NE];
  pixel_* e  = neighbors[area_map::pixel_::dir::E];
  pixel_* se = neighbors[area_map::pixel_::dir::SE];
  pixel_* s  = neighbors[area_map::pixel_::dir::S];
  pixel_* sw = neighbors[area_map::pixel_::dir::SW];
  pixel_* w  = neighbors[area_map::pixel_::dir::W];
  pixel_* nw = neighbors[area_map::pixel_::dir::NW];
  
  //Is there another pixel up
  if(n != NULL){
    //Is the pixel NOT black
    if(~n->is_black){
      //Has the pixel already been inspected or is the last distance longer than it could be?
      if (n->pix_dist.count(target)==0 || n->pix_dist[target] > pix_dist[target] + 1){
	n->pix_dist[target] = pix_dist[target] + 1;
	pix_q.push(n);
      }
    }
  }

  if(ne != NULL){
    if(~ne->is_black){
      if (ne->pix_dist.count(target)==0 || ne->pix_dist[target] > pix_dist[target] + SQ2){
        ne->pix_dist[target] = pix_dist[target] + SQ2;
	pix_q.push(ne);
      }
    }
  }
  
  if(e!=NULL){
    if(~e->is_black){
      if (e->pix_dist.count(target)==0 || e->pix_dist[target] > pix_dist[target] + 1){
        e->pix_dist[target] = pix_dist[target] + 1;
	pix_q.push(e);
      }
    }
  }
  
  if(se!=NULL){
    if(~se->is_black){
      if (se->pix_dist.count(target)==0 ||se->pix_dist[target] > pix_dist[target] + SQ2){
        se->pix_dist[target] = pix_dist[target] + SQ2;
	pix_q.push(se);
      }
    }
  }
  
  if(s!=NULL){
    if(~s->is_black){
      if (s->pix_dist.count(target)==0 || s->pix_dist[target] > pix_dist[target] + 1){
        s->pix_dist[target] = pix_dist[target] + 1;
	pix_q.push(s);
      }
    }
  }
  
  if(sw!=NULL){
    if(~sw->is_black){
      if (sw->pix_dist.count(target)==0 ||sw->pix_dist[target] > pix_dist[target] + SQ2){
	sw->pix_dist[target] = pix_dist[target] + SQ2;
	pix_q.push(sw);
      }
    }
  }
  
  if(w!=NULL){
    if(~w->is_black){
      if (w->pix_dist.count(target)==0 ||w->pix_dist[target] > pix_dist[target] + 1){
        w->pix_dist[target] = pix_dist[target] + 1;
	pix_q.push(w);
      }
    }
  }
  if(nw!=NULL){
    if(~nw->is_black){
      if (nw->pix_dist.count(target)==0 || nw->pix_dist[target] > pix_dist[target] + SQ2){
        nw->pix_dist[target] = pix_dist[target] + SQ2;
	pix_q.push(nw);
      }
    }
  }
}

void area_map::pixel_::initDists(size_t w, size_t h){
  std::cout<<"("<<coord.first<<","<<coord.second<<")\n";
 std::pair<size_t, size_t> cur_coord;
  //Recursivly call all the other pixels  
  if(neighbors[area_map::pixel_::dir::N] != NULL && coord.first==0){
    neighbors[area_map::pixel_::dir::N]->initDists(w, h, cur_coord);
  }
  
  if(neighbors[area_map::pixel_::dir::E]!=NULL){
    neighbors[area_map::pixel_::dir::E]->initDists(w, h, cur_coord);
  }
  
 
  for (size_t row = 0; row < h; row++){
    //    std::cout<<row<<std::endl;
    cur_coord.second = row;
    for (size_t col = 0; col < w; col++){
      cur_coord.first = col;
      pix_dist[cur_coord] = w*h;
    }
  }
  pix_dist[coord] = 0;
  return;
}


void area_map::pixel_::initDists(size_t w, size_t h, std::pair<size_t, size_t> & cur_coord){
  std::cout<<"("<<coord.first<<","<<coord.second<<")\n";
  //Recursivly call all the other pixels  
  if(neighbors[area_map::pixel_::dir::N] != NULL && coord.first==0){
    neighbors[area_map::pixel_::dir::N]->initDists(w, h);
  }
  
  if(neighbors[area_map::pixel_::dir::E]!=NULL){
    neighbors[area_map::pixel_::dir::E]->initDists(w, h);
  }
  
  //  std::pair<size_t, size_t> cur_coord;
  for (size_t row = 0; row < h; row++){
    //    std::cout<<row<<std::endl;
    cur_coord.second = row;
    for (size_t col = 0; col < w; col++){
      cur_coord.first = col;
      pix_dist[cur_coord] = w*h;
    }
  }
  pix_dist[coord] = 0;
  return;
}

//pixel_::pixel_(bool is_black, std::map<std::string, pixel_ *> neighbors);
area_map::pixel_::~pixel_(){
  if (neighbors[area_map::pixel_::dir::W]==NULL){//If we are in the first col
    delete neighbors[area_map::pixel_::dir::N];
  }
  delete neighbors[area_map::pixel_::dir::E];
}
