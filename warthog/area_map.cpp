#include "area_map.h"

area_map::pixel * area_map::getPix(const size_t x, const size_t y, pixel * start){
  pixel * pix = start;
  
  if(x<y){
    for (size_t i = 0; i < x; i++){
      if(pix==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pix = pix->neighbors[1];
    }
    for (size_t i = x; i < y; i++){
      if(pix==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pix = pix->neighbors[0];
    }
  }
  
  else{
    for (size_t i = 0; i < y; i++){
      if(pix==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pix = pix->neighbors[1];
    }
    for (size_t i = y; i<x; i++){
      if(pix==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pix = pix->neighbors[2];
    }
  }
  
  return pix;
}

/*
bool area_map::inspectNeighbors(pixel_ * pix, size_t range, bool state){

  size_t row = pix->y_coord;
  size_t col = pix->x_coord;
  
  size_t y_coord_low = (row > range ? row - range : 0);
  size_t y_coord_high = (row + range < height_clean - 1 ? row + range : height_clean - 1);
  size_t x_coord_low = (col > range ? col - range : 0);
  size_t x_coord_high = (col + range < width_clean-1 ? col + range : width_clean-1);

  pixel_ * cur_pix = pix;

  //Move down to the lower edge
  while(cur_pix->y_coord != y_coord_low){
    cur_pix = cur_pix->neighbors[pixel_::dir::S];
  }

  //Move along the lower edge to the left
  while(cur_pix->x_coord != x_coord_low){
    if (cur_pix->is_black ==state){
      return true;
    }
    cur_pix = cur_pix->neighbors[pixel_::dir::W];
  }

  //Move up the left edge
  while(cur_pix->y_coord != y_coord_high){
    if (cur_pix->is_black == state){
      return true;
    }
    cur_pix = cur_pix->neighbors[pixel_::dir::N];
  }
  
  //Move across the top
    while(cur_pix->x_coord != x_coord_high){
    if (cur_pix->is_black ==state){
      return true;
    }
    cur_pix = cur_pix->neighbors[pixel_::dir::E];
  }

  //Move down the right
    while(cur_pix->y_coord != y_coord_low){
    if (cur_pix->is_black == state){
      return true;
    }
    cur_pix = cur_pix->neighbors[pixel_::dir::S];
  }

  //Move across the bottom till inline with pix
    while(cur_pix->x_coord != col){
    if (cur_pix->is_black ==state){
      return true;
    }
    cur_pix = cur_pix->neighbors[pixel_::dir::W];
    }

    //Recursivly call
    if (range > 1){
      return area_map::inspectNeighbors(pix, range-1, state);
    }
    else{
      return false;
    }
}


void area_map::trimNoise(unsigned int n){
  pixel_ * cur_row = map_data;
  pixel_ * cur_pix = map_data;

  do {
    cur_row = cur_row->neighbors[area_map::pixel_::dir::N];

    do {

      if(inspectNeighbors(cur_pix, n, true)){
	
      }
      cur_pix = cur_pix->neighbors[area_map::pixel_::dir::E];

    }while (cur_pix->neighbors[area_map::pixel_::dir::E] != NULL);
    
    cur_pix = cur_row;
  }while (cur_row->neighbors[area_map::pixel_::dir::N] != NULL);

}

      
void area_map::addBuffer(size_t n){
  size_t added = 0;
  std::vector<std::vector<pixel>* > new_bit_map;
  new_bit_map.resize(pixel_height);
  for(size_t row = 0; row<pixel_height; row++){
    new_bit_map[row] = new std::vector<pixel>;
    (*new_bit_map[row]).resize(pixel_width);
    for(size_t col = 0; col < pixel_width; col++){
      (*new_bit_map[row])[col] = (*bit_map[row])[col]; 
      if (!(*bit_map[row])[col].is_black && inspectNeighbors(row, col, n, true)){
	(*new_bit_map[row])[col].is_black = true;
	added++;
      }
    }
  }
  deleteBitMap();
  bit_map = new_bit_map;
  std::cout<<"Added "<<added<<" black pixels\n";
}


 void area_map::deleteBitMap(){
   for(std::vector<std::vector<pixel> * >::iterator it = bit_map.begin(); it != bit_map.end(); ++it){
      delete(*it);
    }
 }
*/

void area_map::read_bmp(std::ifstream & bmp){
  char file_type[2];
  char char_buf[8];

  //Fields in bmp header
  int file_size;
  int bytes_to_skip;
  int bytes_read = 0;
  int bits_per_pixel;

  int row_size; //Number of bytes per row
  int padding_size;
      
  //Read the file type (bytes 0-1)
  bmp.read(file_type, 2);
  bytes_read += 2;
  
  //Make sure the file type is correct
  if(file_type[0]!='B' || file_type[1]!='M'){
    std::cout<<"Wrong file type!\n";
    throw std::exception();
  }

  //Read the file size (bytes 2-5)
  bmp.read(char_buf, 4);//Read next four bytes (file size)
  bytes_read += 4;
  file_size = char2Int(char_buf, 4);
  
  //Skip misc information
  bmp.ignore(4);
  bytes_read += 4;

  //Read the offset to the pixel data (bytes 10-13)
  bmp.read(char_buf, 4); //Read the next four bytes indicating distance to start of image data
  bytes_read +=4;
  bytes_to_skip = char2Int(char_buf, 4);
  
  //Skip the header size info
  bmp.ignore(4);
  bytes_read += 4;
  
  //Read the image's diminsions (bytes 18-25)
  bmp.read(char_buf, 4);
  width_raw = char2Int(char_buf, 4);
  bmp.read(char_buf, 4);
  height_raw = char2Int(char_buf, 4);
  bytes_read+=8;

  //Skip the color plane
  bmp.ignore(2);
  bytes_read+=2;

  //Read the number of bits per pixel (bytes 28-29)
  bmp.read(char_buf, 2);
  bits_per_pixel = char2Int(char_buf, 2);
      
  //Skip the compression method and image size
  bmp.ignore(8);
  bytes_read += 8;
  
  //Read the image resolution in pixels/meter (bytes 38-45)
  bmp.read(char_buf, 4);
  res_raw = char2Int(char_buf, 4);
  bmp.read(char_buf, 4);
  if (res_raw != (unsigned int) char2Int(char_buf, 4)){
    std::cerr<<"Resolutions must match. Using horiz res.\n";
  }
  bytes_read+=8;

  //Skip to the pixel data
  bmp.ignore(bytes_to_skip - bytes_read-2);

  std::cout<<"File size: "<<file_size<<" bytes"<<std::endl;
  std::cout<<"Diminsion: "<<width_raw<<"w x "<<height_raw<<"h\n";  
  std::cout<<"Bits per Pixel: "<<bits_per_pixel<<std::endl;
  std::cout<<"Resolution: "<<res_raw<<" pixels/meter\n";

  row_size = 4*(bits_per_pixel*width_raw+31)/32;
  padding_size = row_size - width_raw*bits_per_pixel/8;

  pixel * cur_row = NULL;
  pixel * new_pix = NULL;
  pixel * prev_pix = NULL;
  pixel * lower_row;

  size_t black_counter = 0;
  unsigned char color;
  
  for (size_t i = 0; i<height_raw; i++){//Iterate through all the rows
    color = char2Gray(bmp);
    //Create the first pixel in a row
    lower_row = cur_row;
    cur_row = new pixel(color);
    new_pix = cur_row;

    if (i==0){//Set the head pointer to be the first corner (SW)
      map_data = cur_row;
    }
    else{  
      //Set the pointers
      //N-S
      new_pix->neighbors_raw[4] = lower_row;
      lower_row->neighbors_raw[0] = new_pix;
    }
    
    new_pix->coord.first = 0;
    new_pix->coord.second = i;
    //    std::cout<<0<<","<<i<<"="<<(unsigned int)color<<std::endl;
    for(size_t j=1; j < width_raw; j++){//Iterate through all other pixels in a row
      color = char2Gray(bmp);
      
      //Create new pixel
      prev_pix = new_pix;
      new_pix = new pixel(color);

      //Set the pixel's value
      //new_pix->color = char2Gray(bmp);
      if (new_pix->is_black){
	
	black_counter++;
      }
      
      new_pix->coord.first = j;
      new_pix->coord.second = i;
      //std::cout<<j<<","<<i<<"="<<(unsigned int)color<<std::endl;
      //Set the pointers
      //W-E
      (new_pix->neighbors_raw)[6] = prev_pix;
      (prev_pix->neighbors_raw)[2] = new_pix;
      if (i>0){//Check if we are above the first row
	//N-S
	lower_row = lower_row->neighbors_raw[2];
	
	new_pix->neighbors_raw[4] = lower_row;
	lower_row->neighbors_raw[0] = new_pix;
      }
    }
    bmp.ignore(padding_size);
  }

  std::cout<<black_counter<<std::endl;
  map_data->connectDiags();
  return;
}

int area_map::char2Int(const char * c, int n){
  int number = 0;
  for (int i=0; i<n; i++){
    number += (unsigned char) c[i]<<(8*i);
  }
  return number;
}

unsigned char area_map::char2Gray(std::ifstream & file){
  unsigned char gray = 0;
  unsigned char new_gray = 0;
  for (size_t i=0; i<3; i++){
    new_gray = file.get();
    std::cout<<(unsigned int)new_gray<<",";
    gray += new_gray;
  }
  std::cout<<"="<<(unsigned int)gray<<std::endl;
  gray /= 3;
  return gray;
}
/*
void area_map::writeHex(std::ofstream & file, size_t num, size_t byte_count, bool little ){
  int32_t n = num;
  char data[byte_count];
  for (size_t i=0; i<byte_count; i++){
    data[i] = static_cast<char>((n >> (i*8)) & 0xFF);
  }
  file.write(data, byte_count);
}
*/
      

area_map::area_map(){}

area_map::area_map(char * filename, bool gray_scale_):map_data(NULL), grayscale(gray_scale_){

  //Open the bmp file for reading
  std::ifstream bmp(filename, std::ifstream::binary);
  if (!bmp.is_open()){
    std::cout <<"Could not open file\n";
    throw std::exception();
  }
  read_bmp(bmp);
  bmp.close();
  
  res = res_raw;  
  height = height_raw;
  width = width_raw;
}

area_map::area_map(char * filename, size_t res, bool gray_scale_): grayscale(gray_scale_){
  //Open the bmp file for reading
  std::ifstream bmp(filename, std::ifstream::binary);
  if (!bmp.is_open()){
    std::cout <<"Could not open file\n";
    throw std::exception();
  }
  read_bmp(bmp);
  bmp.close();
  
  res = res_raw;
  height = height_raw;
  width = width_raw;
}

area_map::pixel * area_map::operator()(size_t x, size_t y){
  return getPix(x, y, map_data);
}

/*
//Make a new set of cleaned data
void area_map::clean(unsigned int trim, unsigned int add, unsigned int res){
  //Check if we inherit the resolution
  if (res==0){
    res = vres_raw;
  }
  
  //If there is already cleaned data, delete it
  if (map_data != raw_data){
    delete(map_data);
  }

  map_data = new area_map::pixel_;
  * map_data = raw_data;

  area_map::trimNoise(trim);
  area_map::addBuffer(add);
  area_map::setRes(res);
}

  

void area_map::writeBMP(char * filename, int type){
    std::ofstream new_file (filename, std::ofstream::out);
    new_file << "BM";
    //2:   File Size       4 bytes
    writeHex(new_file, 1000, 4);
    //6:   Not used        4
    writeHex(new_file, 0, 4);
    //10:  bit_map offset  4
    writeHex(new_file, 138, 4);
    //14:  size of DIB     4
    //18:  bmp width       4
    //22:  bmp hieght      4
    //
    new_file.close();
  }
*/

void area_map::getDists(size_t x, size_t y){
  area_map::pixel * pixel = getPix(x, y, map_data);
  pixel -> computeDist();
}

void area_map::printDir(size_t start_x, size_t start_y, size_t end_x, size_t end_y){

  area_map::pixel * source_pix = getPix(start_x, start_y, map_data);
  area_map::pixel * sink_pix = getPix(end_x, end_y, map_data);
  area_map::pixel * cur_pix = source_pix;

  sink_pix->computeDist();

  std::cout<<"Moving "<<source_pix->min_dists[sink_pix]<<" units\n";

  size_t min_dir;
  float min_dist;
  while(cur_pix != sink_pix){
    min_dist = 1000;
    for(size_t i = 0; i<=7; i++){
      if(cur_pix->neighbors[i]!=NULL){
	if((cur_pix->neighbors[i])->min_dists[sink_pix] < min_dist){
	  min_dir = i;
	  min_dist = (cur_pix->neighbors[i])->min_dists[sink_pix];
	}
      }
    }
    cur_pix = cur_pix->neighbors[min_dir];
    std::cout<<min_dir<<":"<<cur_pix->is_black<<", ";
  }
  std::cout<<std::endl;
  return;
}
    

area_map::~area_map(){
    delete(map_data);
}
