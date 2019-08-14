#include "function_decl.h"

void printEnvl(envolope * e){
  size_t idx = 0;
  
  while(e->name[idx]!='\0'){
    idx++;
  }
  printf("'%s' in ", e->name);

  idx += 4;
  idx += printCat(e->cat);
  
  for(size_t i = idx; i<35; i++){
    printf("-");
  }

  if(e->bal <= 0){
    redText();
    printf(" -$%0.2f\n", -(e->bal));
    blackText();
  }
  else{
    printf(" $%0.2f\n", (e->bal));
  }
  
  return;
}

size_t printCat(enum catagory c){
  switch (c){
  case AUTO:
    printf("Auto");
    return 4;
  case BILLS:
    printf("Bills");
    return 5;
  case EDU:
    printf("Edu");
    return 3;
  case ENTERTAINMENT:
    printf("Entertainment");
    return 13;
  case FOOD:
    printf("Food");
    return 4;
  case GAS:
    printf("Gas");
    return 3;
  case GIFTS:
    printf("Gifts");
    return 5;
  case GROCERIES:
    printf("Groceries");
    return 9;
  case HEALTH:
    printf("Health");
    return 6;
  case HOME:
    printf("Home");
    return 4;
  case PERSONAL:
    printf("Personal");
    return 8;
  case SERVICES:
    printf("Services");
    return 8;
  case SHOPPING:
    printf("Shopping");
    return 8;
  case TRAVEL:
    printf("Travel");
    return 6;
  case TITHE:
    printf("Tithe");
    return 5;
  case OTHER:
    printf("Other");
    return 5;
  }
  return 0;
}

void badCmd(){
  redText();
  printf("Invalid command. Use money_tracker -h for additionl help.\n");
  blackText();
  return;
}

void redText(){
  printf("\033[1;31m");
}

void blackText(){
  printf("\033[0m");
}
