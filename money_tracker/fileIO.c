#include "function_decl.h"

int openEnvl(const char * id, envolope * e){
  char filename[100];
  buildFilename(id, filename);
  
  FILE * file = fopen(filename, "r");
  if (file == NULL){
    printf("No such file!\n");
    return 0;
  }

  char cur_char;
  size_t idx = 0;
  
  while((cur_char=fgetc(file))!='\n'){
    e->name[idx] = cur_char;
    idx++;
  }
  e->name[idx] = '\0';

  e->bal = getw(file) + getw(file)/100.;
  

  fclose(file);
  return 1;
}

int saveEnvl(envolope * e){
  char filename[100];
  buildFilename(e->name, filename);
  
  double int_part = 0;
  double dec_part = 0;

  FILE * new_file = fopen(filename, "w+");

  //Save the file name 
  fputs(e->name, new_file);
  fputc('\n', new_file);

  //Split the balance into two parts and save both
  dec_part = 100 * modf(e->bal, & int_part);
  dec_part = round(dec_part);
  int_part = round(int_part);
  putw(int_part, new_file);
  putw(dec_part, new_file);

  //Close the file
  fclose(new_file);
  
  return 1;
}
 
void buildFilename(const char * id, char * filename){
  const char * suffix = "./envolopes/envl_";
  size_t name_len = 0;
  size_t suffix_len = 0;
  while(suffix[name_len] != '\0'){
    filename[name_len] = suffix[name_len];
    name_len++;
  }
  suffix_len = name_len;

  while(id[name_len - suffix_len] != '\0'){
    filename[name_len] = id[name_len-suffix_len];
    name_len++;
  }

  filename[name_len] = '.';
  filename[name_len+1] = 'e';
  filename[name_len+2] = 'n';
  filename[name_len+3] = 'v';
  filename[name_len+4] = 'l';
  filename[name_len+5] = '\0';

  return;
} 
