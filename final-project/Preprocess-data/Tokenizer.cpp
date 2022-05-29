#include "Tokenizer.h"

abj::Tokenizer::Tokenizer(){
  this->start_token.initialize((char*)"<s>");
  this->end_token.initialize((char*)"</s>");
}
abj::Tokenizer::Tokenizer(abj::String sentence){
  this->sentence = sentence;

  this->start_token.initialize((char*)"<s>");
  this->end_token.initialize((char*)"</s>");
}

abj::Tokenizer::~Tokenizer(){
  for(int i=0; i<tokens.size(); i++) tokens[i].~String();
}

void abj::Tokenizer::setString(abj::String sentence){
  this->sentence = sentence;
}

void abj::Tokenizer::tokenize(){
  this->tokens.push_back(this->start_token);

  int start_index=0,i=0;
  for(i=0; i<sentence.size(); i++){
    if(sentence.get(i)==this->separator){
      abj::String t(this->make_token(start_index, i-1));
      this->tokens.push_back(t);
      if(i+1<=sentence.size()) start_index=i+1;
    }
  }

  abj::String t(this->make_token(start_index, i-1));
  this->tokens.push_back(t);
  this->tokens.push_back(this->end_token);
}

abj::String abj::Tokenizer::make_token(int start_index, int end_index){
  char* t = (char*)calloc(end_index-start_index+1+1, sizeof(char));
  int j=0;
  for(int i=start_index; i<=end_index; i++,j++)
    t[j]=this->sentence.get(i);
  t[j]='\0';

  abj::String token(t,ALLOCATE_NEW_MEMORY);
  free(t);
  t=NULL;
  return token;
}

std::vector<abj::String>& abj::Tokenizer::getTokens(){
  return this->tokens;
}

void abj::Tokenizer::print(){
  FILE* fptr = fopen(this->DEBUG_FILENAME, "w");
  if(fptr==NULL){
    printf("%s File not found. Exiting...\n", this->DEBUG_FILENAME);
    exit(1);
  }
  fprintf(fptr,"Number of tokens: %d\n",this->tokens.size());
  for(int i=0; i<this->tokens.size(); i++){
    char* tokenChar = this->tokens[i].get_raw_data();
    fprintf(fptr,"\"%s\",", tokenChar);
    free(tokenChar);
  }
  fprintf(fptr,"\n");
  fclose(fptr);
}


void abj::Tokenizer::test_function(){
  printf("Testing tokenizer!-----------\n");
  abj::String str = abj::String::getFileContent(*new abj::String("./Resources/sed-corpus.txt")); 
  abj::Tokenizer tokenizer;
  tokenizer.setString(str);
  tokenizer.tokenize();
  tokenizer.print();
}
