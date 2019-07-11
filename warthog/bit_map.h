#include <stddef>
#include <stdlib>
#include <string>



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
  unsigned int pixels_per_meter;

 public:
  area_map(){}

  area_map(char * filename){
    
