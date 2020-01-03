#include<iostream>
#include <string>
#include <vector>
#include <readline/readline.h>

char ** binNameCompletion(const char *, int, int);
char * binNameGenerator(const char *, int);

std::vector<std::string> e_names;

int main(int argc, char *argv[]) {
  rl_attempted_completion_function = binNameCompletion;

  e_names.push_back(std::string("Automotive"));
  e_names.push_back(std::string("Fun Money"));
  e_names.push_back(std::string("Gas"));
  e_names.push_back(std::string("Groceries"));
  e_names.push_back(std::string("Rent"));

  
  char *buffer = readline("> ");
  if (buffer) {
    printf("You entered: %s\n", buffer);
    free(buffer);
  }
  
  return 0;
}

char ** binNameCompletion(const char * text, int start, int end){
  //Only look at the current bin names. Don't try to complete with file names
  rl_attempted_completion_over = 1;

  //pass the text var and a state var to the binNameGenerator function.
  //The state var is 0 on the first call and non 0 otherwise
  return rl_completion_matches(text, binNameGenerator);
}

char * binNameGenerator(const char * text, int state){
  static size_t idx;
  static int len;
  const char * name;

  if (!state){
    idx = 0;
    len = strlen(text);
  }
  std::cout<<e_names.size();
  if(idx<e_names.size()){    
    name = e_names[idx].c_str();
    //    std::cout<<"Name: "<<name<<", idx: "<<idx<<", Text: "<<text<<". ";
    idx++;
    if (strncmp(name, text, len) == 0) {
      return strdup(name);
    }
  }

  return NULL;
}
