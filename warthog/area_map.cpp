#include "area_map.h"

area_map::pixel_ * area_map::getPix(const size_t x, const size_t y, pixel_ * start){
  pixel_ * pixel = start;
  
  if(x<y){
    for (size_t i = 0; i < x; i++){
      if(pixel==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pixel = pixel->neighbors[pixel_::dir::NE];
    }
    for (size_t i = x; i < y; i++){
      if(pixel==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pixel = pixel->neighbors[pixel_::dir::N];
    }
  }
  
  else{
    for (size_t i = 0; i < y; i++){
      if(pixel==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pixel = pixel->neighbors[pixel_::dir::NE];
    }
    for (size_t i = y; i<x; i++){
      if(pixel==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
      pixel = pixel->neighbors[pixel_::dir::E];
    }
  }
  
  return pixel;
}

bool area_map::inspectNeighbors(pixel_ * pix, size_t range, bool state){

  size_t row = pix->y_coord;
  size_t col = pix->x_coord;
  
  int y_coord_low = row - range;
  int y_coord_high = row + range;
  int x_coord_low = col - range;
  int x_coord_high = col + range;
  
  //Make sure the range doesn't push us outside the boundries
  if (y_coord_low < 0){//Negative row index
    y_coord_low = 0;
  }
  if (y_coord_high > pixel_height_raw - 1){//To large row index
    y_coord_heigh = pixel_height_raw - 1;
  }
  if (x_coord_low < 0){//Negative col index
    x_coord_low = 0;
  }
  if (x_coord_high > pixel_width_raw - 1){//To large col index
    x_coord_high = pixel_width_raw - 1;
  }

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
    if (cur_pix->is_black ==state){
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
    if (cur_pix.is_black ==state){
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

/*
void area_map::trimNoise(size_t n){
  size_t trimmed = 0;
  std::vector<std::vector<pixel>* > new_bit_map;
  new_bit_map.resize(pixel_height);
  for(size_t row = 0; row<pixel_height; row++){
    new_bit_map[row] = new std::vector<pixel>;
    (*new_bit_map[row]).resize(pixel_width);
    for(size_t col = 0; col < pixel_width; col++){
      (*new_bit_map[row])[col] = (*bit_map[row])[col]; 
      if ((*bit_map[row])[col].is_black && inspectNeighbors(row, col, n, false)){
	(*new_bit_map[row])[col].is_black = false;
	trimmed++;
      }
    }
  }
  deleteBitMap();
  bit_map = new_bit_map;
  std::cout<<"Trimmed "<<trimmed<<" black pixels\n";
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
  pixel_width_raw = char2Int(char_buf, 4);
  bmp.read(char_buf, 4);
  pixel_height_raw = char2Int(char_buf, 4);
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
  pixel_hres_raw = char2Int(char_buf, 4);
  bmp.read(char_buf, 4);
  pixel_vres_raw = char2Int(char_buf, 4);
  bytes_read+=8;

  //Skip to the pixel data
  bmp.ignore(bytes_to_skip - bytes_read-2);

  std::cout<<"File size: "<<file_size<<" bytes"<<std::endl;
  std::cout<<"Diminsion: "<<pixel_width_raw<<"w x "<<pixel_height_raw<<"h\n";  
  std::cout<<"Bits per Pixel: "<<bits_per_pixel<<std::endl;
  std::cout<<"Resolution: "<<pixel_hres_raw<<"p/m horiz x "<<pixel_vres_raw<<"p/m vert\n";

  row_size = 4*(bits_per_pixel*pixel_width_raw+31)/32;
  padding_size = row_size - pixel_width_raw*bits_per_pixel/8;

  pixel_ * cur_row = NULL;
  pixel_ * new_pix = NULL;
  pixel_ * prev_pix = NULL;
  pixel_ * lower_row;
  
  for (size_t i = 0; i<pixel_height_raw; i++){//Iterate through all the rows
    //Create the first pixel in a row
    lower_row = cur_row;
    cur_row = new pixel_;
    new_pix = cur_row;

    if (i==0){//Set the head pointer to be the first corner (SW)
      raw_data = cur_row;
    }
    else{  
      //Set the pointers
      //N-S
      new_pix->neighbors[pixel_::dir::S] = lower_row;
      lower_row->neighbors[pixel_::dir::N] = new_pix;
    }
    
    //Set its value
    new_pix->color = char2Gray(bmp);
    if (new_pix->color < 20){
      new_pix->is_black = true;
    }
    else{
      new_pix->is_black = false;
    }
    new_pix->x_coord = 0;
    new_pix->y_coord = i;
	
    for(size_t j=1; j < pixel_width_raw; j++){//Iterate through all other pixels in a row
      //Create new pixel
      prev_pix = new_pix;
      new_pix = new pixel_;
      //Set the pixel's value
      new_pix->color = char2Gray(bmp);
      if (new_pix->color < 20){
	new_pix->is_black = true;
	std::cout<<"Black pixel at ("<<j<<","<<i<<")\n";
      }
      else{
	new_pix->is_black = false;
      }
      new_pix->x_coord = j;
      new_pix->y_coord = i;

      //Set the pointers
      //W-E
      new_pix->neighbors[pixel_::dir::W] = prev_pix;
      prev_pix->neighbors[pixel_::dir::E] = new_pix;
      if (i>0){//Check if we are above the first row
	//N-S
	lower_row = lower_row->neighbors[pixel_::dir::E];
	
	new_pix->neighbors[pixel_::dir::S] = lower_row;
	lower_row->neighbors[pixel_::dir::N] = new_pix;
      }
    }
    bmp.ignore(padding_size);
  }
  return;
}

int area_map::char2Int(const char * c, int n){
  int number = 0;
  for (int i=0; i<n; i++){
    number += (unsigned char) c[i]<<(8*i);
  }
  return number;
}

int area_map::char2Gray(std::ifstream & file){
  int gray = 0;
  for (size_t i=0; i<3; i++){
    gray += (unsigned char)file.get();
  }
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
  
  raw_data->connectDiags();

  pixel_ * test = getPix(0, 0, raw_data);
    std::cout<<test->color<<std::endl;
  test = getPix(500, 500, raw_data);
  test = getPix(25, 35, raw_data);
    std::cout<<test->color<<std::endl;
  test = getPix(76, 93, raw_data);
  std::cout<<test->color<<std::endl;
}

/*
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

area_map::~area_map(){
  delete(raw_data);
  delete(map_data);
}
