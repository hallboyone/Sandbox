#include <iostream>
#include <utility>
#include <vector>
#include <math.h>
int main(){
  float num = -123.45;

  FILE * f = fopen("test_file", "w+");
  if (num < 0){
    num = -num;
    fputc(255, f);
  }

  unsigned char next_char = 0;
  for (int i = 3; i>=-4; i--){
    next_char = num / pow(256, i);
    num -= next_char * pow(256, i);
    fputc(next_char, f);  
  }
  
  printf("%0.2f\n", num);
  fclose(f);
  num = 0;
  
  f = fopen("test_file", "r");
  next_char = fgetc(f);
  int neg_flag = 1;
  if (next_char==255){
    neg_flag = -1;
  }

  for (int i = 3; i>=-4; i--){
    next_char = fgetc(f);
    num += next_char * pow(256, i);
  }
  num *=neg_flag;

  fclose(f);
  
  return 1;
}
