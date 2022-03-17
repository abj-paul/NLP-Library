#include "Bigram.h"

abj::Bigram::Bigram(){
  this->corpus.initialize(this->extract_content_from_file(DEFAULT_CORPUS));
}
abj::Bigram::Bigram(const char* filename){
  this->corpus.initialize(this->extract_content_from_file(filename));
}

char* abj::Bigram::extract_content_from_file(const char* filename){ //auxiliary function
  FILE* fptr = fopen(DEFAULT_CORPUS,"r");
  if(fptr==NULL){
    printf("Error! %s-File not found!\n",filename);
    exit(1);
  }

  fseek(fptr,0L,SEEK_END);
  int size = ftell(fptr);
  fseek(fptr, 0L, SEEK_SET);
  
  char* content = (char*)calloc(size+1, sizeof(char));
  fread(content, size, 1, fptr);
  content[size]='\0';

  return content;
}

bool abj::Bigram::preprocess_corpus(){
  abj::Punctuation punctuation;
  punctuation.setCorpus(this->corpus);
  punctuation.handle_punctuation();
  this->corpus = punctuation.getUpdatedCorpus();
  this->corpus.print();
  return true;
}

void abj::Bigram::test_function(){
  printf("Testing bigram---------------------------\n");
  abj::Bigram bigram;
  bigram.preprocess_corpus();
}
