#include "area_map.h"


bool area_map::inspectNeighbors(size_t row, size_t col, size_t range, bool state){
  size_t range_row_low = range;
  size_t range_row_high = range;
  size_t range_col_low = range;
  size_t range_col_high = range;
  
  //Make sure the range won't push us outside the boundries
  if (row < range){//Negative row index
    range_row_low = row;
  }
  if (pixel_height-1 < row + range){//To large row index
    range_row_high = pixel_height - row-1;
  }
  if (col < range){//Negative col index
    range_col_low = col;
  }
  if (pixel_width-1 < col + range){//To large col index
    range_col_high = pixel_width - col-1;
  }

  for (size_t row_itr = range_row_low; row_itr<=range_row_high; row_itr++){
    for (size_t col_itr = range_col_low; col_itr<=range_col_high; col_itr++){
      if (row_itr != row || col_itr!=col){
	if ((*bit_map[row_itr])[col_itr].is_black == state){
	  return true;
	}
      }
    }
  }

  return false;
}
      
	
    
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
      std::cout<<bytes_to_skip<<std::endl;
      //Skip the header size info
      bmp.ignore(4);
      bytes_read += 4;
  
      //Read the image's diminsions (bytes 18-25)
      bmp.read(char_buf, 4);
      pixel_width = char2Int(char_buf, 4);
      bmp.read(char_buf, 4);
      pixel_height = char2Int(char_buf, 4);
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
      pixel_hres = char2Int(char_buf, 4);
      bmp.read(char_buf, 4);
      pixel_vres = char2Int(char_buf, 4);
      bytes_read+=8;

      //Skip to the pixel data
      bmp.ignore(bytes_to_skip - bytes_read-2);

      std::cout<<"File size: "<<file_size<<" bytes"<<std::endl;
      std::cout<<"Diminsion: "<<pixel_width<<"w x "<<pixel_height<<"h\n";  
      std::cout<<"Bits per Pixel: "<<bits_per_pixel<<std::endl;
      std::cout<<"Resolution: "<<pixel_hres<<"p/m horiz x "<<pixel_vres<<"p/m vert\n";

      row_size = 4*(bits_per_pixel*pixel_width+31)/32;
      padding_size = row_size - pixel_width*bits_per_pixel/8;
     
      bit_map.resize(pixel_height); //Resize the bit_map vector to holds a pointer for each row

      int blue;
      int green;
      int red;
      
      for (size_t i=0; i<pixel_height; i++){//Iterate through all the rows
	bit_map[i] = new std::vector<pixel>;
	(*bit_map[i]).resize(pixel_width);
	for(size_t j=0; j<pixel_width; j++){//Iterate through all the pixels in a row
	  blue = bmp.get();
	  green = bmp.get();
	  red = bmp.get();
	  (*bit_map[i])[j].id_building = 0;
	  if (red < 10 && green < 10 && blue < 10){
	    (*bit_map[i])[j].is_black = 1;
	  }
	  else{
	    (*bit_map[i])[j].is_black = 0;
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

  area_map::area_map(){}

  area_map::area_map(char * filename){

  //Open the bmp file for reading
  std::ifstream bmp(filename, std::ifstream::binary);
  if (!bmp.is_open()){
    std::cout <<"Could not open file\n";
    throw std::exception();
  }
  
  read_bmp(bmp);
  bmp.close();
  }
/*
  unsigned int area_map::groupBuildings(){
    //Iterate through each pixel
    //Check if pixel's row/col neighbors are part of a building group
    //If at least one has a building id and all neighbors match, set pixels id to match
    //If there are multiple id's in the pixel's neighbors, merge the id's and set the pixels id to match
    for (size_t col = 0; col<pixel_height; col++){
      for (size_t row = 0; row<pixel_width; row++){
*/	
  area_map::~area_map(){
    for(std::vector<std::vector<pixel> * >::iterator it = bit_map.begin(); it != bit_map.end(); ++it){
      delete(*it);
    }
  }
