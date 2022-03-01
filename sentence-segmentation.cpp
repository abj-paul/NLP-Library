#include<iostream>
#include "auxiliary.cpp"

#define punctuation_file_name "punctuation.txt"

// Functio Prototypes
bool use_decision_tree_to_segment_sentence(char str[]);
bool isPunctuation(char c);
char* getPunctuationList(const char* filename);
void test_function();

int main(){
  char main_string[] = "I am only human. Dr. Albert told me to fetch him. PhD. professors are often very helpful. Selena is a great singer!";
  test_function();
  return 0;
}

bool use_decision_tree_to_segment_sentence(char str[]){
  // Detedct punctuation in the string
  int i=0;
  while(str[i]!='\0'){
    if(isPunctuation(str[i]))
    i++;
  }
  return true;
}

bool isPunctuation(char c){
return true;
}

char* getPunctuationList(const char* filename){
  FILE* fptr = fopen(filename, "r");
  if(fptr==NULL){
    printf("File not found.\n");
    exit(1);
  }

  int total_punctuations=0;
  fseek(fptr, 0L, SEEK_END);
  total_punctuations=ftell(fptr);

  fseek(fptr, 0L, SEEK_SET);
  char* punctuation_list = (char*)calloc(total_punctuations+1, sizeof(char));

  for(int i=0; i<total_punctuations; i++){
    fscanf(fptr,"%c\n",&punctuation_list[i]);
  }
  fclose(fptr);
  return punctuation_list;
}

void test_function(){
  char* punctuation_list = getPunctuationList(punctuation_file_name);

  int size=0;
  FILE* fptr = fopen(punctuation_file_name,"r");
  if(fptr==NULL) exit(1);
  
  fseek(fptr, 0L, SEEK_END);
  size=ftell(fptr);
  fclose(fptr);
  print_array(punctuation_list, size);
  //  printf("Done printing.\n");

  // Punctuation List
  free(punctuation_list);
}
