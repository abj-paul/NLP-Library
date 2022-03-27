#include "Tokenizer.h"

abj::Tokenizer::Tokenizer(){
  this->start_token.initialize((char*)"<s>");
  this->end_token.initialize((char*)"</s>");
 // Do nothing
}
abj::Tokenizer::Tokenizer(abj::String sentence){
  this->sentence = sentence;

  this->start_token.initialize((char*)"<s>");
  this->end_token.initialize((char*)"</s>");
}

abj::Tokenizer::~Tokenizer(){
  this->tokens.~Vector();
  // this->sentence.~String();
}

void abj::Tokenizer::setString(abj::String sentence){
  this->sentence = sentence;
}

void abj::Tokenizer::tokenize(){
  this->tokens.push(this->start_token);

  int start_index=0,i=0;
  for(i=0; i<sentence.size(); i++){
    if(sentence.get(i)==this->separator){
      abj::String t(this->make_token(start_index, i-1));
      this->tokens.push(t);
      if(i+1<=sentence.size()) start_index=i+1;
    }
  }

  abj::String t(this->make_token(start_index, i-1));
  this->tokens.push(t);
  this->tokens.push(this->end_token);
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

abj::Vector<abj::String> abj::Tokenizer::getTokens(){
  return this->tokens;
}

void abj::Tokenizer::print(){
  printf("Number of tokens: %d\n",this->tokens.size());
  for(int i=0; i<this->tokens.size(); i++){
    this->tokens.get(i).print();
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
