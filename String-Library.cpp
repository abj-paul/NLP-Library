#include "String-Library.h"

/*int main(){
  string_len("Abhi");
  return 0;
  }*/

int string_len(char* x){
  int i=0;
  while(x[i]!='\0'){
    i++;
  }
  return i;
}
int string_len(const char* x){
  if(x==NULL){
    printf("Error occurred at - %s\n",x);
    return 0;
  }
  int i=0;
  while(x[i]!='\0'){
    i++;
  }
  return i;
}


void string_concatenate(char first[], char second[], char sentence[]){
  int i=0;
  while(first[i]!='\0'){
    sentence[i] = first[i];
    i++;
  }
  sentence[i]=' ';
  i++;
  int j=0;
  while(second[j]!='\0'){
    sentence[i]=second[j];
    i++;
    j++;
  }
  sentence[i]='\0';
}

bool is_same_string(const char* str,char word[]){
  //printf("Compare Strings Function.\n");
  int n1 = string_len(str);
  int n2 = string_len(word);

  if(n1!=n2) return false;
  //  printf("%s\n",word);
  for(int i=0; i<n1; i++){
    if(str[i]!=word[i]) return false;
  }
  return true;
}

bool is_same_string(const char* str,const char* word){
  //printf("Compare Strings Function.\n");
  int n1 = string_len(str);
  int n2 = string_len(word);

  if(n1!=n2) return false;
  //  printf("%s\n",word);
  for(int i=0; i<n1; i++){
    if(str[i]!=word[i]) return false;
  }
  return true;
}

bool is_same_string(char* str,const char* word){
  //printf("Compare Strings Function.\n");
  int n1 = string_len(str);
  int n2 = string_len(word);

  if(n1!=n2) return false;
  //printf("%s\n",word);
  for(int i=0; i<n1; i++){
    if(str[i]!=word[i]) return false;
  }
  return true;
}

bool is_same_string(char* str, char* word){
  //printf("Compare Strings Function.\n");
  int n1 = string_len(str);
  int n2 = string_len(word);

  if(n1!=n2) return false;
  //printf("%s\n",word);
  for(int i=0; i<n1; i++){
    if(str[i]!=word[i]) return false;
  }
  return true;
}


char** tokenizer_revamp(const char* str){
  char** word_list = (char**)calloc(MAX_WORD_IN_A_SENTENCE, sizeof(char));

  word_list[0] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
  word_list[1] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));

  int str_index=0, word_index=0, word_list_index=1;
  while(str[str_index]!='\0'){
    if(str[str_index]==' '){
      word_list[word_list_index][word_index] = '\0';;
      word_list_index++;
      word_index=0;

      word_list[word_list_index] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
    }else{
      word_list[word_list_index][word_index] = str[str_index];
      word_index++;
    }
    str_index++;
  }

  word_list[word_list_index][word_index] = '\0';
  word_list_index++;

  word_list[word_list_index]=NULL;
  return word_list;
}
char** tokenizer_revamp(char* str){
  char** word_list = (char**)calloc(MAX_WORD_IN_A_SENTENCE, sizeof(char));

  word_list[0] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
  word_list[1] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));

  int str_index=0, word_index=0, word_list_index=1;
  while(str[str_index]!='\0'){
    if(str[str_index]==' '){
      word_list[word_list_index][word_index] = '\0';;
      word_list_index++;
      word_index=0;

      word_list[word_list_index] = (char*)calloc(MAX_WORD_SIZE, sizeof(char));
    }else{
      word_list[word_list_index][word_index] = str[str_index];
      word_index++;
    }
    str_index++;
  }

  word_list[word_list_index][word_index] = '\0';
  word_list_index++;

  word_list[word_list_index]=NULL;
  return word_list;
}

void print_word_list(char** x){
  int i=1;
  while(x[i]!=NULL){
    printf("%d) %s\n",i,x[i]);
    i++;
  }
}

void print_string(char* str){
  int i=0;
  while(str[i]!='\0'){
    printf("%c",str[i]);
    i++;
  }
  printf("\n");
}

void print_string(const char* str){
  int i=0;
  while(str[i]!='\0'){
    printf("%c",str[i]);
    i++;
  }
  printf("\n");
}

void string_copy(char* source_array, const char* the_word){
  int i=0;
  while(the_word[i]!='\0'){
    if(source_array[i]=the_word[i]);
    i++;
  }
  source_array[i]='\0';
  return;
}

bool string_concatenate(char* corpus, char* word, const char separator){
  int index = string_len(corpus);
  corpus[index]=separator;

  int i=0,j=0;
  for(i=index+1, j=0; word[j]!='\0'; i++, j++){
    corpus[i]=word[j];
  }
  corpus[i]='\0';
  return true;
}
bool string_insert_behind(char* str,int* index, char c){
  //  printf("Running for index=%d!\n",*index);
  char behind_char=c;

  int i=*index;
  while(str[i]!='\0'){
    char temp=str[i];
    str[i]=behind_char;
    behind_char = temp;
    i++;
  }
  str[i]=behind_char;
  str[i+1]='\0';

  (*index)++;
  return true;
}

char capitalize(char c){
  int offset = 'a' - 'A';
  if(c>='a' && c<='z') c=c-offset;
  return c;
}


char* capitalize(char* str){
  int i=0;
  while(str[i]!='\0'){
    str[i]=capitalize(str[i]);
    i++;
  }
  return str;
}

void string_copy(char* source_array, char* the_word){
  int i=0;
  while(the_word[i]!='\0'){
    if(source_array[i]=the_word[i]);
    i++;
  }
  source_array[i]='\0';
  return;
}
