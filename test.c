#include <stdlib.h>
#include <stdio.h>

const char * printFirst(int* digits){
  *digits += 5;
  return "First";
}

void printSecond(char * buff, int num, size_t * idx){
  //"The number is %d"
  sprintf(buff+(*idx), "%15s %-4d", "The number is", num);
  *idx += 20;
}

int main(void){
  int digit = 0;
  char buff[1000];
  size_t idx = 0;

  printSecond(buff, 4, &idx);
  sprintf(buff+idx, "|");
  idx++;
  printSecond(buff, 8, &idx);
  printf("%s", buff);
  return 0;
}
	 
