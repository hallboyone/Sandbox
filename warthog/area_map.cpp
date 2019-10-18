#include "area_map.h"

area_map::pixel * area_map::getPix(const size_t x, const size_t y, pixel * start){
  pixel * pix = start;
  size_t i = 0;

  //Move NE as far as possible
  while(i < x && i < y){
    pix = pix->neighbors[NE];
    if (pix==NULL){
      std::cerr<<"Index out of range\n";
      return NULL;
    }
    i++;
  }
  
  if(x < y){//Move N to the pixel
    for (size_t i = x; i < y; i++){
      pix = pix->neighbors[N];
      if(pix==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
    }
  }
  
  else{//Mov E to the pixel
    for (size_t i = y; i<x; i++){
      pix = pix->neighbors[E];
      if(pix==NULL){
	std::cerr<<"Index out of range\n";
	return NULL;
      }
    }
  }
  return pix;
}

void area_map::read_bmp(std::ifstream & bmp){
  char char_buf[8];
  bool black_is_0 = true;
  int bytes_read = 0;

  int row_size; //Number of bytes per row
  int padding_size;
  
  //Read the file type (bytes 0-1)
  bmp.read(file_header.file_type, 2);
  bytes_read += 2;
  
  //Make sure the file type is correct
  if(file_header.file_type[0] !='B' || file_header.file_type[1]!='M'){
    std::cout<<"Wrong file type!\n";
    throw std::exception();
  }

  //Read the file size (bytes 2-5)
  bmp.read(char_buf, 4);//Read next four bytes (file size)
  bytes_read += 4;
  file_header.file_size = char2Int(char_buf, 4);
  
  //Skip misc information
  bmp.ignore(4);
  bytes_read += 4;

  //Read the offset to the pixel data (bytes 10-13)
  bmp.read(char_buf, 4); //Read the next four bytes indicating distance to start of image data
  bytes_read +=4;
  file_header.bmp_offset = char2Int(char_buf, 4);
  
  //Detailed Header Size
  bmp.read(char_buf, 4);
  bytes_read += 4;
  dib_header.header_size = char2Int(char_buf, 4);
  
  //Read the image's diminsions (bytes 18-25)
  bmp.read(char_buf, 4);
  dib_header.pixel_width = char2Int(char_buf, 4);
  bmp.read(char_buf, 4);
  dib_header.pixel_height = char2Int(char_buf, 4);
  bytes_read+=8;

  //Color plane
  bmp.read(char_buf, 2);
  dib_header.color_planes = char2Int(char_buf, 2);
  bytes_read+=2;

  //Read the number of bits per pixel (bytes 28-29)
  bmp.read(char_buf, 2);
  bytes_read += 2;
  dib_header.color_depth = char2Int(char_buf, 2);
      
  //Skip the compression method
  bmp.read(char_buf, 4);
  bytes_read += 4;
  dib_header.comp_method = char2Int(char_buf, 4);
  if (dib_header.comp_method != 0){
    std::cerr<<"File cannot be compressed\n";
    throw std::exception();
  }

  //Bmp size
  bmp.read(char_buf, 4);
  bytes_read += 4;
  dib_header.image_size = char2Int(char_buf, 4);
  
  //Read the image resolution in pixels/meter (bytes 38-45)
  bmp.read(char_buf, 4);
  dib_header.h_resolution = char2Int(char_buf, 4);
  bmp.read(char_buf, 4);
  dib_header.v_resolution = char2Int(char_buf, 4);
  bytes_read+=8;

  if (dib_header.v_resolution != dib_header.h_resolution){
    std::cerr<<"Resolutions do not match. Using the value of h_resolution\n";
    dib_header.v_resolution = dib_header.h_resolution;
  }
  
  //If binary, see if 0 is white or black
  if (dib_header.color_depth == 1){
    bmp.ignore(14+dib_header.header_size - bytes_read);
    bytes_read += 14 + dib_header.header_size - bytes_read;
    if (char2Gray(bmp, 8)==255){//Check if the first bit in the color map is 0 (implies that 1 => black);
      black_is_0 = false;
    }
    bytes_read += 1;
  }

  //Skip to data
  bmp.ignore(file_header.bmp_offset - bytes_read);
  
  std::cout<<"File size: "<<file_header.file_size<<" bytes"<<std::endl;
  std::cout<<"Diminsion: "<<dib_header.pixel_width<<"w x "<<dib_header.pixel_height<<"h\n";  
  std::cout<<"Bits per Pixel: "<<dib_header.color_depth<<std::endl;
  std::cout<<"Header size: "<<dib_header.header_size<<std::endl;
  std::cout<<"Uncompressed: "<<dib_header.comp_method<<std::endl;
  std::cout<<"Resolution: "<<dib_header.h_resolution<<"x"<<dib_header.v_resolution<<" pixels/meter\n";

  row_size = 4*((dib_header.color_depth*dib_header.pixel_width + 31)/32);
  padding_size = row_size - dib_header.pixel_width*dib_header.color_depth/8;

  std::cout<<"Actual rows are "<<row_size<<" bytes long with "<<padding_size<<" bytes of padding\n";
  
  pixel * cur_row = NULL;
  pixel * new_pix = NULL;
  pixel * prev_pix = NULL;
  pixel * lower_row;

  uint32_t color;

  size_t bit_pos = 0;
    
  for (size_t i = 0; i<dib_header.pixel_height; i++){//Iterate through all the rows
    if(dib_header.color_depth < 8){
      color = bit2Black(bmp, bit_pos);
    }
    else{
      color = char2Gray(bmp, dib_header.color_depth);
    }

    //If binary and unset bit is white, shift the color value
    if(!black_is_0){
      color = 255-color;
    }
    
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

    for(size_t j=1; j < dib_header.pixel_width; j++){//Iterate through all other pixels in a row
      
      if(dib_header.color_depth < 8){
	color = bit2Black(bmp, bit_pos);
      }
      else{
	color = char2Gray(bmp, dib_header.color_depth);
      }
      
      if(!black_is_0){
	color = 255-color;
      }
      
      //Create new pixel
      prev_pix = new_pix;
      new_pix = new pixel(color);
   
      new_pix->coord.first = j;
      new_pix->coord.second = i;

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
    bit_pos = 0;
    bmp.ignore(padding_size);
  }
  map_data->connectDiags();
  //  map_data->computeAllDists();
  return;
}

uint32_t area_map::char2Int(const char * c, int n){
  uint32_t number = 0;
  for (int i=0; i<n; i++){
    number += (unsigned char) c[i]<<(8*i);
  }
  return number;
}

uint32_t area_map::char2Gray(std::ifstream & file, size_t bits_per_pix){
  uint32_t gray = 0;
  switch (bits_per_pix){
  case 32:
    file.ignore(1);
  case 24:
    for (size_t i=0; i<3; i++){
      gray += file.get();
    }
    gray /= 3;
    break;
    
  case 8:
    gray = file.get();
    break;
    
  case 1://Monochrome
    gray = file.get();
    break;

  default:
    std::cerr<<"Color Depth not defined: "<<bits_per_pix<<std::endl;
    break;
  }
  
  return gray; 
}

uint8_t area_map::bit2Black(std::ifstream & file, size_t & bit_pos){
  uint8_t byte_val;
  if (bit_pos == 8){//If we are at the end of a byte
    bit_pos = 0;
    file.ignore();
  }

  byte_val = file.peek();

  byte_val = byte_val<<bit_pos;
  byte_val = byte_val>>7;

  bit_pos++;

  return byte_val * 255;
}     

area_map::area_map(){}

area_map::area_map(char * filename, bool gray_scale_):source_pix(NULL), sink_pix(NULL), grayscale(gray_scale_){
  //Open the bmp file for reading
  std::ifstream bmp(filename, std::ifstream::binary);
  if (!bmp.is_open()){
    std::cout <<"Could not open file\n";
    throw std::exception();
  }
  read_bmp(bmp);
  bmp.close();
  
  resolution = dib_header.h_resolution;
  
  height = dib_header.pixel_height;
  width = dib_header.pixel_width;
}

area_map::pixel * area_map::operator()(size_t x, size_t y){
  return getPix(x, y, map_data);
}

void area_map::getDists(size_t x, size_t y){
  area_map::pixel * pixel = getPix(x, y, map_data);
  pixel -> computeDist();
}

void area_map::printDir(size_t start_x, size_t start_y, size_t end_x, size_t end_y){
  source_pix = getPix(start_x, start_y, map_data);
  sink_pix = getPix(end_x, end_y, map_data);
  if (source_pix == NULL || sink_pix == NULL){
    return;
  }

  pixel * cur_pix = source_pix;
  size_t min_dir;
  float min_dist;
  size_t cur_dir = -1;
  size_t cur_dist = 0;
  std::set<pixel *> prev_pixels;
  waypoints = std::set<pixel *>();
  
  sink_pix->computeDist();

  std::cout<<"Moving "<<source_pix->min_dists[sink_pix]/(float)resolution<<" meters ("<<source_pix->min_dists[sink_pix]<<" units)\n";
  
  while(cur_pix != sink_pix){
    min_dist = INT64_MAX;
    for(int i = N; i<= NW; i++){
      if(cur_pix->neighbors[i] != NULL){
	if((cur_pix->neighbors[i])->min_dists[sink_pix] < min_dist){
	  min_dir = i;
	  min_dist = (cur_pix->neighbors[i])->min_dists[sink_pix];
	}
      }
    }

    cur_pix = cur_pix->neighbors[min_dir];
    waypoints.insert(cur_pix);
    
    if(waypoints.count(cur_pix)>1){
      std::cerr<<"Circular path. Please try with differnet inputs\n";
      return;
    }
    
    if(cur_pix->is_black){
      std::cerr<<"No valid path!\n";
      return;
    }
    
    if(cur_pix == sink_pix){
      cur_dist++;
      switch (min_dir){
      case 0:
	std::cout<<"N:"<<cur_dist<<std::endl;
	break;
      case 1:
	std::cout<<"NE:"<<cur_dist<<std::endl;
	break;
      case 2:
	std::cout<<"E:"<<cur_dist<<std::endl;
	break;
      case 3:
	std::cout<<"SE:"<<cur_dist<<std::endl;
	break;
      case 4:
	std::cout<<"S:"<<cur_dist<<std::endl;
	break;
      case 5:
	std::cout<<"SW:"<<cur_dist<<std::endl;
	break;
      case 6:
	std::cout<<"W:"<<cur_dist<<std::endl;
	break;
      case 7:
	std::cout<<"NW:"<<cur_dist<<std::endl;
	break;
      }
    }

    else if(cur_dir == min_dir || cur_dist == 0){
      cur_dist ++;
    }

    else{
     
      
      switch (cur_dir){
      case 0:
	std::cout<<"N:"<<cur_dist<<"->";
	break;
      case 1:
	std::cout<<"NE:"<<cur_dist<<"->";
	break;
      case 2:
	std::cout<<"E:"<<cur_dist<<"->";
	break;
      case 3:
	std::cout<<"SE:"<<cur_dist<<"->";
	break;
      case 4:
	std::cout<<"S:"<<cur_dist<<"->";
	break;
      case 5:
	std::cout<<"SW:"<<cur_dist<<"->";
	break;
      case 6:
	std::cout<<"W:"<<cur_dist<<"->";
	break;
      case 7:
	std::cout<<"NW:"<<cur_dist<<"->";
	break;
      }
      cur_dist = 1;
    }    
    cur_dir = min_dir;
  }
  printMap();  
  return;
}

void area_map::printMap(){
  //get pointer to the upper edge
  pixel * cur_pix = map_data;
  while(cur_pix->neighbors[0]!=NULL){
    cur_pix = cur_pix->neighbors[0];
  }
  pixel * cur_row = cur_pix;
  size_t row_index = dib_header.pixel_height - 1;
  do{
    do{
      if(cur_pix==source_pix){
	std::cout<<"O";
      }
      else if(cur_pix==sink_pix){
	std::cout<<"X";
      }
      else if(cur_pix->is_black){
	std::cout<<"@";
      }
      else if(waypoints.count(cur_pix)==1){
	std::cout<<"*";
      }
      else{
	std::cout<<" ";
      }
      cur_pix = cur_pix->neighbors[2];
      /*if(cur_pix!=NULL){
	std::cout<<" ";
	}*/
    }while(cur_pix != NULL);
    cur_row = cur_row->neighbors[4];
    cur_pix = cur_row;
    std::cout<<":"<<row_index<<"\n";
    row_index--;
  }while(cur_row!=NULL);
  for (size_t i = 0; i< dib_header.pixel_width; i++){
    std::cout<<i<<" ";
    if(i<10){
      std::cout<<" ";
    }
  }
  std::cout<<std::endl;
}

void area_map::clean(uint8_t trim, uint8_t add, size_t iterations){
  map_data->addBuffer(trim, 0, true);
  map_data->setTemp();
  map_data->addBuffer(add, 1, false);
  map_data->saveTemp();
  map_data->addBuffer(add, 1, false);
  map_data->saveTemp();
  map_data->addBuffer(trim, 0, false);
  map_data->saveTemp();
   
  for (size_t i = 1; i < iterations; i++){
    map_data->addBuffer(trim, 0, false);
    map_data->saveTemp();
    map_data->addBuffer(add, 1, false);
    map_data->saveTemp();
  }
  return;
}

void area_map::setRawRes(uint32_t res){
  dib_header.h_resolution = res;
  dib_header.v_resolution = res;
  resolution = res;
  std::cout<<"Setting Resolution to "<<res<<"pix/m\n";
}

void area_map::setRes(uint32_t res){
  if (res < dib_header.h_resolution){
    std::cerr<<"Cannot create a map with a higher resolution than the original\n";
  }
  return;
}

area_map::~area_map(){
  delete(map_data);
}
