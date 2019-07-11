#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include <vector>

class area_map{
 private:
  typedef struct pixel_{
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
    bool is_black;
  } pixel;

  //Holds the pixel structs. The std::vector<pixel>s are dynamically allocated
  std::vector<std::vector<pixel>* > bit_map;

  //The resolution of the image. 
  unsigned int pixel_vres;
  unsigned int pixel_hres;
  unsigned int pixel_width;
  unsigned int pixel_height;
  
  void read_bmp(std::ifstream & bmp);
     
  int char2Int(const char * c, int n);

 public:
  area_map();

  area_map(char * filename);

  ~area_map();
};
