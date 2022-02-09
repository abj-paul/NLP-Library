
#include<bits/stdc++.h>
using namespace std;

int string_len(char* x){
  int i=0;
  while(x[i]!='\0'){
    i++;
  }
  return i;
}
int string_len(const char* x){
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
  //printf("%s\n",word);
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
