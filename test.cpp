#include <iostream>
#include <vector>
#include <map>
#include <queue>

class pixel{
protected:
  std::vector<pixel *> neighbors; //Holds the 8 pointers
  unsigned char color;
  bool is_black;
  std::map<pixel *, float> dists;  


  void computeDist(std::queue<pixel *> & pix_q, pixel * target){
    for(size_t i = N; i<=NW; i++){
      if(neighbors[i] != NULL){//Does the neighbor exist
	if(!neighbors[i]->is_black){//Is the neighbor passable
	  if(neighbors[i]->dists.count(target) == 0 || neighbors[i]->dists[target] > dists[target] + one_step[i]){//Is it shorter?
	    pix_q.push(neighbors[i]);
	    neighbors[i]->dists[target] = dists[target] + one_step[i];
	  }
	}
	else{
	  neighbors[i]->dists[target] = 1000;
	}
      }
    }
    return;
  }
  
public:
  //Variable to map the direction to the distance
  static std::map<size_t, float> one_step;
  
  pixel(){
    neighbors.resize(8);
    for (size_t i = N; i <= NW; i++){
      neighbors[i] = NULL;
    }

    color = 255;
    is_black = false;
  }

  pixel(unsigned char color_){
    neighbors.resize(8);
    for (size_t i = N; i <= NW; i++){
      neighbors[i] = NULL;
    }

    color = color_;
    if (color_ < 20){
      is_black = true;
    }
    else{
      is_black = false;
    }
  }
  
  pixel * operator[](int i){
    return neighbors[i];
  }

  void setNeighbor(pixel * n, int d){
    int d_back = (d+4) % 8;
    if(neighbors[d] != NULL || n->neighbors[d_back] != NULL){//Check if there is already a neighbor
      std::cerr<<"Already a neighbor!\n";
      return;
    }
    neighbors[d] = n;
    n->neighbors[d_back] = this;
    return;
  }
  
  void computeDist(){
    std::queue<pixel *> pix_q;
    pix_q.push(this);

    dists[this] = 0;

    while(pix_q.size()!=0){
      pix_q.front()->computeDist(pix_q, this);
      pix_q.pop();
    }
  }

   
  void printDir(pixel * dest){
    if(dists.count(dest) == 0){//Have we computed the distance yet?
      dest -> computeDist();
    }

    pixel * cur_pix = this;
    size_t min_dir;
    size_t min_dist;
    while(cur_pix != dest){
      min_dist = 1000;
      for(size_t i = 0; i<=7; i++){
	if(cur_pix->neighbors[i]!=NULL){
	  if((cur_pix->neighbors[i])->dists[dest] < min_dist){
	    min_dir = i;
	    min_dist = (cur_pix->neighbors[i])->dists[dest];
	  }
	}
      }
      cur_pix = cur_pix->neighbors[min_dir];
      std::cout<<min_dir<<", ";
    }
    std::cout<<std::endl;
  }

  
  ~pixel(){
    if (neighbors[W]==NULL){//if we are in the first col
	delete(neighbors[N]);
    }

    delete(neighbors[E]);
  }
    
  enum dir{N, NE, E, SE, S, SW, W, NW};
};

std::map<size_t, float> pixel::one_step =  {{0, 1}, {1,  1.4}, {2, 1}, {3, 1.4}, {4, 1}, {5, 1.4}, {6, 1}, {7, 1.4}};
    
int main(){
  pixel * pix_00 = new pixel;
  pixel * pix_01 = new pixel;
  pixel * pix_02 = new pixel;
  pixel * pix_10 = new pixel;
  pixel * pix_11 = new pixel(0);
  pixel * pix_12 = new pixel;
  pixel * pix_20 = new pixel;
  pixel * pix_21 = new pixel;
  pixel * pix_22 = new pixel;

  pix_00->setNeighbor(pix_01, pixel::N);
  pix_00->setNeighbor(pix_11, pixel::NE);
  pix_00->setNeighbor(pix_10, pixel::E);

  pix_01->setNeighbor(pix_02, pixel::N);
  pix_01->setNeighbor(pix_12, pixel::NE);
  pix_01->setNeighbor(pix_11, pixel::E);
  pix_01->setNeighbor(pix_10, pixel::SE);
  
  pix_02->setNeighbor(pix_12, pixel::E);
  pix_02->setNeighbor(pix_11, pixel::SE);

  pix_10->setNeighbor(pix_11, pixel::N);
  pix_10->setNeighbor(pix_21, pixel::NE);
  pix_10->setNeighbor(pix_20, pixel::E);

  pix_11->setNeighbor(pix_12, pixel::N);
  pix_11->setNeighbor(pix_22, pixel::NE);
  pix_11->setNeighbor(pix_21, pixel::E);
  pix_11->setNeighbor(pix_20, pixel::SE);
  
  pix_12->setNeighbor(pix_22, pixel::E);
  pix_12->setNeighbor(pix_21, pixel::SE);
  
  pix_20->setNeighbor(pix_21, pixel::N);
  
  pix_21->setNeighbor(pix_22, pixel::N);

  pix_00->printDir(pix_22);

  delete(pix_00);
  
  return 1;
}
