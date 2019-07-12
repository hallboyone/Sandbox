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

  for (size_t row_itr = row-range_row_low; row_itr<=row+range_row_high; row_itr++){
    for (size_t col_itr = col-range_col_low; col_itr<=col+range_col_high; col_itr++){
      if (row_itr != row || col_itr!=col){
	if ((*bit_map[row_itr])[col_itr].is_black == state){
	  return true;
	}
      }
    }
  }
  return false;
}
      
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
	    (*bit_map[i])[j].is_black = true;
	  }
	  else{
	    (*bit_map[i])[j].is_black = false;
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

void area_map::writeHex(std::ofstream & file, size_t num, size_t byte_count, bool little ){
  //char n = (char) num;
  int32_t n = num;
  char data[byte_count];
  for (size_t i=0; i<byte_count; i++){
    data[i] = static_cast<char>((n >> (i*8)) & 0xFF);
  }
  file.write(data, byte_count);
  /*if (num > pow(16, byte_count)-1){
    std::cerr<<num<<" cannot be stored in "<<byte_count<<" bytes\n";
    return;
  }
  
  std::vector<int> hex_mults(byte_count);
  
  //Get each part of the number
  for (size_t i=byte_count; i > 0; i--){
    hex_mults[i-1] = num/pow(16, i-1);
    num = num - pow(16, i-1) * hex_mults[i-1];
    std::cout<<"multiple = "<<hex_mults[i-1]<<std::endl<<"New Num = "<<num<<std::endl;
  }
  
  if(little){
    for(size_t i = 0; i<byte_count; i+=2){
      file.write(hex_mults << std::hex << hex_mults[i+1]<<hex_mults[i];
    }
  }*/
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
  area_map::~area_map(){
    for(std::vector<std::vector<pixel> * >::iterator it = bit_map.begin(); it != bit_map.end(); ++it){
      delete(*it);
    }
  }
