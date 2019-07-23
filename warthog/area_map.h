#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include<map>

class area_map{
 private:
  class pixel_{
  public:
    enum class dir {NW, N, NE, E, SE, S, SW, W};
    std::map<dir, pixel_*> neighbors;
    
    std::map<pixel_*, size_t> pix_dist;
    
    bool is_black;
    int color; //0-20 = black
    unsigned int id_building_;
    size_t x_coord;
    size_t y_coord;
    

    
    pixel_();
    pixel_(bool is_black);

    void dist2Here();
    //    pixel_(bool is_black, std::map<std::string, pixel_ * neighbors);

    void connectDiags();
    ~pixel_();
  };

  
  pixel_ * raw_data;
  pixel_ * map_data;
  
  
  //Holds all the unique buildings as vectors of their indicies. 
  //std::vector<std::vector<std::pair<size_t, size_t> >* >
  
  
  //The resolution of the image. 
  unsigned int vres_raw;
  unsigned int hres_raw;
  unsigned int vres_clean;
  unsigned int hres_clean;

  unsigned int width_raw;
  unsigned int height_raw;
  unsigned int width_clean;
  unsigned int height_clean;

  bool grayscale; //False means the data is binary
  
  //unsigned int next_id;
  
  void read_bmp(std::ifstream & bmp);
  
  int char2Int(const char * c, int n);
  int char2Gray(std::ifstream & file);
  
  //void writeHex(std::ofstream & file, size_t num, size_t byte_count, bool little = true);
  
  //Looks in all neighbors within n spaces to see if any matches state
  //  bool inspectNeighbors(pixel_ * pix, size_t n, bool state);

  //void deleteBitMap();
  
  //Function to clean noise by setting all black pixels n spaces from a clear pixel clear
  //void trimNoise(unsigned int n);
  
  //Switch all clear pixels within n spaces of a black pixel black
  //void addBuffer(unsigned int n);

  pixel_ * getPix(size_t x, size_t y, pixel_ * start);
  
 public:
  area_map();
  
  area_map(char * filename, bool gray_scale_ = false);

  area_map(char * filename, size_t res, bool gray_scale = false);

  pixel_ * operator()(size_t x, size_t y);
  /*
  void clean(unsigned int trim, unsigned int add, unsigned int res = 0){
    trimNoise(trim);
    addBuffer(add);
    return;
  }
  */
  
  void rawVRes(unsigned int v_res){
    vres_raw = v_res;
  }

  void rawHRes(unsigned int h_res){
    hres_raw = h_res;
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
  
  ~area_map();
};
