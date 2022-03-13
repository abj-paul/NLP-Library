#include "Tokenizer.h"

abj::Tokenizer::Tokenizer(){
  // Do nothing
  this->start_token.initialize("<s>");
  this->end_token.initialize("</s>");
}
abj::Tokenizer::Tokenizer(abj::String sentence){
  this->sentence = sentence;

  this->start_token.initialize("<s>");
  this->end_token.initialize("</s>");
}
void abj::Tokenizer::setString(abj::String sentence){
  this->sentence = sentence;
}

abj::Tokenizer::~Tokenizer(){
  // Do Nothing
}

void abj::Tokenizer::tokenize(){
  this->tokens.push(this->start_token);

  int start_index=0;
  for(int i=0; i<sentence.size(); i++){
    if(sentence.get(i)==this->separator){
      this->tokens.push(this->make_token(start_index, i-1));
      if(i+1<=sentence.size()) start_index=i+1;
    }
  }
  this->tokens.push(this->end_token);
}

abj::String abj::Tokenizer::make_token(int start_index, int end_index){
  char* t = (char*)calloc(end_index-start_index+1+1, sizeof(char));
  for(int i=start_index; i<=end_index; i++) t[i]=this->sentence.get(start_index+i);
  t[end_index+1]='\0';

  abj::String token(t,ALLOCATE_NEW_MEMORY);
  //free(t);
  return token;
}

abj::Vector<abj::String> abj::Tokenizer::getTokens(){
  return this->tokens;
}

void abj::Tokenizer::print(){
  for(int i=0; i<tokens.size(); i++){
    printf("[%s]",tokens.get(i));
    if(i!=tokens.size()-1) printf(",");
  }
  printf("\n");
}


void abj::Tokenizer::test_function(){
  printf("Testing tokenizer!-----------\n");
  abj::String str("I am only human and I feel pain when I fall down .");
  
  abj::Tokenizer tokenizer;
  tokenizer.setString(str);
  tokenizer.tokenize();
  tokenizer.print();
}
