#include <stddef.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

int char2Int(const char * c, int number);

typedef struct rgb_{
  int red;
  int green;
  int blue;
}rgb_;

int main(int argc, char * argv[]){
  char file_type[2];
  char char_buf[8];

  //Fields in bmp header
  int file_size;
  int bytes_to_skip;
  int bytes_read = 0;
  int pixel_hres;
  int pixel_vres;
  int pixel_width;
  int pixel_height;
  int bits_per_pixel;

  int row_size; //Number of bytes per row
  
  std::vector<std::vector<rgb_> *> bit_map;

  if (argc != 2){
    std::cout <<"Usage: "<<argv[0]<<" <filename.bmp>\n";
    return 0;
  }

  //Open the bmp file for reading
  std::ifstream bmp(argv[1], std::ifstream::binary);
  if (!bmp.is_open()){
    std::cout <<"Could not open file\n";
    return 0;
  }
  
  //Read the file type (bytes 0-1)
  bmp.read(file_type, 2);
  bytes_read += 2;
  
  //Make sure the file type is correct
  if(file_type[0]!='B' || file_type[1]!='M'){
    std::cout<<"Wrong file type!\n";
    return 1;
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
  std::cout<<"Skipping "<<bytes_to_skip - bytes_read<<" bytes\n";
  bmp.ignore(bytes_to_skip - bytes_read-2);

  std::cout<<"Reading from: "<<argv[1]<<"..."<<std::endl;
  std::cout<<"File size: "<<file_size<<" bytes"<<std::endl;
  std::cout<<"Diminsion: "<<pixel_width<<"w x "<<pixel_height<<"h\n";  
  std::cout<<"Bits per Pixel: "<<bits_per_pixel<<std::endl;
  std::cout<<"Resolution: "<<pixel_hres<<"p/m horiz x "<<pixel_vres<<"p/m vert\n";

  row_size = 4*(bits_per_pixel*pixel_width+31)/32;
  int padding_size = row_size - pixel_width*bits_per_pixel/8;
  std::cout<<row_size<<std::endl;
  std::cout<<padding_size<<std::endl;
  int black_count = 0;

  bit_map.resize(pixel_height); //Resize the bit_map vector to holds a pointer for each row
  
  for (int i=0; i<pixel_height; i++){//Iterate through all the rows
    bit_map[i] = new std::vector<rgb_>;
    (*bit_map[i]).resize(pixel_width);
    for(int j=0; j<pixel_width; j++){//Iterate through all the pixels in a row
      (*bit_map[i])[j].blue = bmp.get();
      (*bit_map[i])[j].green = bmp.get();
      (*bit_map[i])[j].red = bmp.get();
	if ((*bit_map[i])[j].blue <10 && (*bit_map[i])[j].red < 10 && (*bit_map[i])[j].green < 10){
	 black_count++;
	}
    }
    bmp.ignore(padding_size);
  }
  
  std::cout<<"Black Count: "<<black_count<<std::endl;

  for (int i=0; i<pixel_height; i++){
    delete(bit_map[i]);
  }
  
  bmp.close();
  return 0;
}

int char2Int(const char * c, int n){
  int number = 0;
  for (int i=0; i<n; i++){
    number += (unsigned char) c[i]<<(8*i);
  }
  return number;
}
