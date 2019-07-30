#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <utility>
#include <queue>
#include <limits>
#include <cstdint>
#include <set>

enum dir {N, NE, E, SE, S, SW, W, NW};

class area_map{
 private:
  class pixel{    
  public:
    //Pointers to the neighboring pixels
    std::vector<pixel *> neighbors;

    //Pointers to the original pixels.
    std::vector<pixel *> neighbors_raw;
    
    //Holds the min distance for each pixel coord pair from the pixel
    std::map<pixel *, float> min_dists;

    std::pair<size_t, size_t> coord;
    
    bool is_black_raw;
    bool is_black_temp;
    bool is_black;
    
    uint32_t color_raw;
    uint32_t color;
      
    pixel();
    pixel(unsigned char color_);

    void computeDist();
    void connectDiags();

    void restore(){
      neighbors = neighbors_raw;
    }
    
    //Function adds/removes set pixels to clean noise
    void addBuffer(uint8_t n, bool state, bool use_raw);

    //Saves the current values of is_black to is_black_temp
    void saveTemp();
    //Sets the values of is_black to be is_black_temp
    void setTemp();
 
    ~pixel();

  private:
    void computeDist(std::queue<pixel *> & pix_q, pixel * target);
    //Variable to map the direction to the distance
    static std::map<size_t, float> one_step;

    //Looks at neighbors up to n away to check if any match the state
    //If use_raw = true, look at the is_black_raw and change is_black
    //Else look at is_black and change is_black_temp
    bool inspectNeighbors(uint8_t n, bool state, bool use_raw);
 };

  
  pixel * map_data; //Points at the SW corner of the bit map
  pixel * source_pix;//The latest pixel that we started from
  pixel * sink_pix; //The lastes pixel that we went to 
  
  typedef struct file_header_{
    char file_type[2];//Offset:0, Size 2
    uint32_t file_size;//Offset:2, Size 4
    uint32_t bmp_offset;//Offset:10, size 4
  } _file_header;

  _file_header file_header;
  
  typedef struct dib_header_{
    uint32_t header_size;
    uint32_t pixel_width;
    uint32_t pixel_height;
    uint16_t color_planes; //Must be 1
    uint16_t color_depth;
    uint32_t comp_method; //Should be 0
    uint32_t image_size;
    uint32_t h_resolution; //pixels/meter
    uint32_t v_resolution; //pixels/meter
    uint32_t palette_size;
    uint32_t important_color_size; //0 for all
  } _dib_header;

  _dib_header dib_header;

  //User set resolution values in pix/m. Defautls to values in dib_header
  uint32_t resolution;

  //Calculated dimensions if the resolution is adjusted
  uint32_t width;
  uint32_t height;

  bool grayscale; //False means the data is binary
  
  void read_bmp(std::ifstream & bmp);
  
  uint32_t char2Int(const char * c, int n);

  uint32_t char2Gray(std::ifstream & file, size_t bits_per_pix);
  uint8_t bit2Black(std::ifstream & file, size_t & bit_pos);
  
  pixel * getPix(size_t x, size_t y, pixel * start);
  
 public:
  area_map();
  
  area_map(char * filename, bool gray_scale_ = false);

  pixel * operator()(size_t x, size_t y);
  
  void clean(uint8_t trim, uint8_t add);  
  
  void setRawRes(uint32_t res);
  void setRes(uint32_t res);
  
  void getDists();
  void getDists(size_t x, size_t y);

  void printDir(size_t start_x, size_t start_y, size_t end_x, size_t end_y);
  void printMap();
  
  ~area_map();
};
