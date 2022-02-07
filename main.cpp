
#include<bits/stdc++.h>
#define MAX_SIZE 30


// Global Variables
char sentence[MAX_SIZE];

// function prototype
int get_string_len(char* x);
int minimum_edit_distance(char x[], char target_word[]);

int main(){
  char  x[] = "this";
  char target[] = "there";

  int ans = minimum_edit_distance(x,target);
  std::cout<<"MED is: "<<ans<<std::endl;

  return 0;
}

int minimum_edit_distance(char x[], char target_word[]){

  int n1 = get_string_len(x);
  int n2 = get_string_len(target_word);

  // x axis = j = target_word
  // y axis = i = x word
  int m[MAX_SIZE][MAX_SIZE];
  for(int i=0; i<=n1; i++) m[i][0]=i;
  for(int j=0; j<=n2; j++) m[0][j]=j;

  for(int i=1; i<=n1; i++){
    for(int j=1; j<=n2; j++){
      if(x[i]==target_word[j]) m[i][j]=m[i-1][j-1];
      else m[i][j] = std::min(m[i-1][j-1],std::min(m[i-1][j],m[i][j-1]))+1;
    }
  }
  return m[n1][n2];
}

int get_string_len(char* x){
  int i=0;
  while(x[i]!='\0'){
    i++;
  }
  return i;
}

char* correct_spelling(char* target_word, char* filename){
  FILE* fptr = fopen(filename,"r");

  char *current_word, *previous_word, *next_word;
  current_word = (char*)malloc(MAX_SIZE);
  previous_word = (char*)malloc(MAX_SIZE);
  next_word = (char*)malloc(MAX_SIZE);
  previous_word = NULL;
  current_word = NULL;
  next_word = NULL;

  while(!feof(fptr)){
    str_copy(current_word, previous_word);
    fscanf(fptr, "%s", current_word);
    bigram(previous_word, current_word);
  }
}

void str_copy(char* source, char* destination){
  if(source==NULL){
    destinatio=NULL;
    return;
  }

  int i=0;
  while(source[i]!='\0'){
    destination[i] = source[i];
    i++;
  }
  destination[i]='\0';
  return;
}

void str_concatenate(char* first, char* second){
  int i=0;
  while(first[i]!='\0'){
    sentence[i] = first[i];
    i++;
  }
  first[i]=' ';
  i++;
  int j=0;
  while(second[j]!='\0'){
    sentence[i]=second[j];
    i++;
    j++;
  }
  sentence[i]='\0';
}

int phrase_count(char* str, char* filename){
  FILE *fptr = fopen(filename, "r");
  if(fptr==NULL) return -2;

  char first_str[MAX_SIZE], second_str[MAX_SIZE];
  int count=0;
  while(!feof(fptr)){
    fscanf(fptr,"%s",second_str);
  }
}

void bigram(char* first_word, char* second_word, char* filename){
  
}
