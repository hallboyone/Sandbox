#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void){
  const char * string = "Test\n";
  char * str = strdup(string);
  
printf("%s", str);
  free(str);
  return EXIT_SUCCESS;
}
