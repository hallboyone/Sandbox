#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include<map>
#include <utility>
#include <queue>
#include <limits>

class area_map{
 private:
  class pixel{    
  public:
    enum dir {NW, N, NE, E, SE, S, SW, W};
    std::vector<pixel *> neighbors;
    std::vector<pixel *> neighbors_raw;
    //Holds the min distance for each pixel coord pair from the pixel
    std::map<pixel *, float> min_dists;
    std::pair<size_t, size_t> coord;
    bool is_black;
    unsigned char color;

    
    //Variable to map the direction to the distance
    static std::map<size_t, float> one_step;
     
    pixel();
    pixel(unsigned char color_);

    void computeDist();
    void connectDiags();
    void restore(){
      neighbors = neighbors_raw;
    }
    
    ~pixel();

    //private:
    void computeDist(std::queue<pixel *> & pix_q, pixel * target);
  };

  
  pixel * map_data;//Points at the SW corner of the bit map

  
  
  //Holds all the unique buildings as vectors of their indicies. 
  //std::vector<std::vector<std::pair<size_t, size_t> >* >
  
  
  //The resolution of the image. 
  unsigned int res_raw;
  unsigned int res;

  unsigned int width_raw;
  unsigned int height_raw;
  unsigned int width;
  unsigned int height;

  bool grayscale; //False means the data is binary
  
  void read_bmp(std::ifstream & bmp);
  
  int char2Int(const char * c, int n);
  unsigned char char2Gray(std::ifstream & file);
  
  //Looks in all neighbors within n spaces to see if any matches state
  //  bool inspectNeighbors(pixel_ * pix, size_t n, bool state);

  //void deleteBitMap();
  
  //Function to clean noise by setting all black pixels n spaces from a clear pixel clear
  //void trimNoise(unsigned int n);
  
  //Switch all clear pixels within n spaces of a black pixel black
  //void addBuffer(unsigned int n);

  pixel * getPix(size_t x, size_t y, pixel * start);
  
 public:
  area_map();
  
  area_map(char * filename, bool gray_scale_ = false);

  area_map(char * filename, size_t res, bool gray_scale = false);

  pixel * operator()(size_t x, size_t y);
  /*
  void clean(unsigned int trim, unsigned int add, unsigned int res = 0){
    trimNoise(trim);
    addBuffer(add);
    return;
  }
  */
  
  void rawRes(unsigned int res_){
    res_raw = res_;
  }

    
  //Function first trims noise and then adds buffer
  /*void cleanBMP(size_t noise_level, size_t buffer_level){
    trimNoise(noise_level);
    addBuffer(buffer_level);
    return;
    }*/

  //Creates a bmp with the current bit_map
  //void writeBMP(char * filename, int type = 0);

  void getDists();
  void getDists(size_t x, size_t y);

  void printDir(size_t start_x, size_t start_y, size_t end_x, size_t end_y);
  
  ~area_map();
};
