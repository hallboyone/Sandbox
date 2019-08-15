#include "function_decl.h"

void makeEnvl(){
  char buffer[100];
  size_t idx = 0;

  envolope new_envl = {time(NULL   )};

  //new_envl.ID = 
  printf("Creating a new envolope.\nPlease enter the Envolope's name...\n");

  //Get user input
  fgets(buffer, 100, stdin);
  //Remove newline char
  while(buffer[idx+1] != '\0'){
    if(!isalnum(buffer[idx])){
      printWarn("Please only enter alphanumeric values in the name\n");
      printf("Please enter the Envolope's name...\n");
      fgets(buffer, 100, stdin);
      idx = 0;
    }
    else{
      idx++;
    }
  }
  buffer[idx] = '\0';

  //Malloc space for the name and save it
  new_envl.name = malloc((idx+1)*sizeof(char));
  for(size_t i = 0; i<idx; i++){
    new_envl.name[i] = buffer[i];
  }

  //Get the catagory
  idx = 0;
  printf("Enter the Envolope's catagory\n({0=auto, 1=bills, 2=edu, 3=entertainment, 4=food, 5=gas, 6=gifts, 7=groceries, 8=health, 9=home, 10=personal, 11=services, 12=shopping, 13=travel, 14=tithe, 15=other)\n");

  //Get user input
  fgets(buffer, 100, stdin);
  //Convert to int
  new_envl.cat = 0;
  while(buffer[idx] != '\n'){
    new_envl.cat = new_envl.cat*10 + buffer[idx]-'0';
    idx++;
  }
  //Make sure the int named a valid type
  if(new_envl.cat > 15){
    badCmd();
    free(new_envl.name);
    return;
  }

  //Get balance
  idx = 0;
  printf("Enter the starting balance...\n");
  fgets(buffer, 100, stdin);
  new_envl.bal = 0;
  int neg_flag = 1;
  
  if (buffer[idx]=='-'){
    neg_flag = -1;
    idx++;
  }
  
  while(buffer[idx]!='\n'){
    if(buffer[idx]=='.'){
      idx++;
      size_t point_flag = idx-1;
      while(buffer[idx]!='\n'){
	new_envl.bal += (buffer[idx]-'0')/(float)pow(10,idx - point_flag);
	idx++;
      }
      break;
    }
  new_envl.bal = new_envl.bal*10 + buffer[idx]-'0';
  idx++;
  }

  new_envl.bal *= neg_flag;
  saveEnvl(& new_envl);

  printEnvl(& new_envl);
  
  free(new_envl.name);
  return;
}
