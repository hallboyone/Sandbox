#include <stdlib.h>
#include <stdio.h>

const char * printFirst(int* digits){
  *digits += 5;
  return "First";
}
const char * printSecond(int* digits){
  *digits += 6;
  return "Second";
}

int main(void){
  int digit = 0;
  printf("%-10s | %-15s ||\n", printFirst(&digit), printSecond(&digit));
  for(int i =0; i<28; i++){
    printf("-");
    if(i==10 || i==27){
      printf("|");
    }
  }
  printf("|\n%-10s | %-15s ||\n", printSecond(&digit), printFirst(&digit));
  return 0;
}
	 
