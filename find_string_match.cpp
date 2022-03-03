#ifndef abj
#include <bits/stdc++.h>
#include "String-Library.cpp"
using namespace std;
#endif
// Function Prototypes
bool is_same_string(char* str,char* word);
bool is_same_string(const char* str,char* word);
int find_match(const char* str, const char* filename);

/*int main(){
  //  printf("Match found: %d\n",find_match("you have","korpus/you-have-5.txt"));
  printf("Match found: %d\n",find_match("very good","korpus/stanfordSentimentTreebank/datasetSentences.txt"));
  //printf("Match found: %d\n",find_match("miss you","korpus/stanfordSentimentTreebank/datasetSentences.txt"));
  //printf("Match found: %d\n",find_match("you have","korpus/stanfordSentimentTreebank/datasetSentences.txt"));
  return 0;
  }*/

int find_match(const char* str, const char* filename){
  //printf("Find match function.\n");
  int count=0;
  FILE* fptr = fopen(filename, "r");
  if(fptr==NULL) return -1; // ERROR CODE: NO FILE FOUND
  char two_word[MAX_WORD_SIZE*2], word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
  while(!feof(fptr)){
    fscanf(fptr,"%s %s",word1, word2);
    string_concatenate(word1, word2, two_word);
    //printf("%s\n",two_word);
    if(is_same_string(str,two_word)) count++;
    int n2 = string_len(word2);
    if(!is_same_string(word2,".")) fseek(fptr, n2*(-1), SEEK_CUR);
  }
  return count;
}

int find_match(char* str, char* filename){
  //printf("Find match function.\n");
  int count=0;
  FILE* fptr = fopen(filename, "r");
  if(fptr==NULL) return -1; // ERROR CODE: NO FILE FOUND
  char two_word[MAX_WORD_SIZE*2], word1[MAX_WORD_SIZE], word2[MAX_WORD_SIZE];
  while(!feof(fptr)){
    fscanf(fptr,"%s %s",word1, word2);
    string_concatenate(word1, word2, two_word);
    //printf("%s\n",two_word);
    if(is_same_string(str,two_word)) count++;
    int n2 = string_len(word2);
    if(!is_same_string(word2,".")) fseek(fptr, n2*(-1), SEEK_CUR);
  }
  return count;
}

