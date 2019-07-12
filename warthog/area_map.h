#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

class area_map{
 private:
  typedef struct pixel_{
    bool is_black;
    unsigned int id_building;
    
  } pixel;

  
  //Holds the pixel structs. The std::vector<pixel>s are dynamically allocated
  std::vector<std::vector<pixel>* > bit_map;

  /*
  //Holds all the unique buildings as vectors of their indicies. 
  std::vector<std::vector<std::pair<size_t, size_t> >* >
  */
  
  //The resolution of the image. 
  unsigned int pixel_vres;
  unsigned int pixel_hres;
  unsigned int pixel_width;
  unsigned int pixel_height;
  unsigned int next_id;
  
  void read_bmp(std::ifstream & bmp);
  
  int char2Int(const char * c, int n);

  void writeHex(std::ofstream & file, size_t num, size_t byte_count, bool little = true);
  
  //Looks in all neighbors within n spaces to see if any matches state
  bool inspectNeighbors(size_t row, size_t col, size_t n, bool state);

  void deleteBitMap();
  
  //Function to clean noise by setting all black pixels n spaces from a clear pixel clear
  void trimNoise(size_t n);
  
  //Switch all clear pixels within n spaces of a black pixel black
  void addBuffer(size_t n);
  
 public:
  area_map();

  area_map(char * filename);
  
  //Function first trims noise and then adds buffer
  void cleanBMP(size_t noise_level, size_t buffer_level){
    trimNoise(noise_level);
    addBuffer(buffer_level);
    return;
      }

  //Creates a bmp with the current bit_map
  void writeBMP(char * filename, int type = 0);
  
  ~area_map();
};
