#include "lib_punctuation.h"

abj::Punctuation::Punctuation(){
  this->get_punctuation_list();
}

abj::Punctuation::Punctuation(abj::String text){
  this->get_punctuation_list();
  this->corpus.initialize(text);
}

void abj::Punctuation::setCorpus(abj::String text){
  //this->corpus.removeData();
  this->corpus.initialize(text);
}

void abj::Punctuation::get_punctuation_list(){
  FILE* fptr = fopen(this->punctuation_filename,"r");
  if(fptr==NULL){
    printf("Punctuation list file not found!Exiting...\n");
    exit(1);
  }
  char p;
  while(!feof(fptr)){
    fscanf(fptr,"%c\n",&p);
    this->punctuation_list.push(p);
  }
  //this->punctuation_list.print();
  fclose(fptr);
}

int abj::Punctuation::get_file_length(FILE* fptr){
  fseek(fptr, 0L,SEEK_END);
  int size = ftell(fptr);
  fseek(fptr, 0L,SEEK_SET);
  return size;
}

bool abj::Punctuation::isPunctuation(char c){
  for(int i=0; i<this->punctuation_list.size(); i++){
    if(this->punctuation_list[i]==c) return true;
  }
  return false;
}

void abj::Punctuation::handle_punctuation(){
  for(int i=0; i<this->corpus.size(); i++){
    //printf("%d) %c==punctuation?\n",i+1,this->corpus.get(i));
    if(isPunctuation(this->corpus.get(i))) {
      char c = corpus[i];
      if(c=='.' || c==',' || c=='?' || c==':' || c=='!' || c==';' || c==')')this->corpus.insert_char_at_point(i, this->separator);
      else if(c=='.' || c=='\"' || c=='(')this->corpus.insert_char_at_point(i+1, this->separator); // insert space next
      else if(c=='\'') {
	this->corpus.set(i,'i'); //s->is
	this->corpus.insert_char_at_point(i, this->separator);
      }
      i++;
    }
  }
}

void abj::Punctuation::print(){
  this->corpus.print();
}

abj::Punctuation::~Punctuation(){
  //this->punctuation_list.~Vector<char>();
  //this->corpus.~String();

}

abj::String abj::Punctuation::getUpdatedCorpus(){
  return this->corpus;
}

void abj::Punctuation::test_function(){
  printf("Testing Punctuation.-----------------\n");
  abj::String str = abj::String::getFileContent(*new abj::String("sed-corpus.txt"));

  abj::Punctuation p;
  printf("\" is punctuation?%d\n",p.isPunctuation('\"'));
  printf("- is punctuation?%d\n",p.isPunctuation('-'));
  printf("( is punctuation?%d\n",p.isPunctuation('('));

  p.setCorpus(str);
  p.handle_punctuation();
  p.print();
}
