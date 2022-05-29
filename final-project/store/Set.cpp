#include "Set.h"

abj::Set::Set(){
  this->ngram = 0;
}
abj::Set::~Set(){
  for(int i=0; i<storage.size(); i++)
    for(int j=0; j<storage[i].size(); j++) storage[i][j].~String();
}

void abj::Set::defineNGram(int ngram){
  this->ngram = ngram;
}

bool abj::Set::insert(std::vector<abj::String>& element){
  //Finding match
  int match_count=0;
  for(int i=0; i<this->storage.size(); i++){
    match_count=0;
    for(int j=0; j<storage[i].size(); j++){
      if(element[j].equals(storage[i][j])) match_count++; 
    }
    if(match_count==this->ngram) return false;
  }

  this->storage.push_back(element);
  return true;
}

int abj::Set::size(){
  return this->storage.size();
}

void abj::Set::print(){
  this->print(* new abj::String(this->DEBUG_FILEAME));
}

void abj::Set::print(abj::String& filename){
  FILE* fptr = fopen(filename.get_raw_data(), "w");
  if(fptr==NULL){
    printf("Error opening %s file! Exiting...\n",this->DEBUG_FILEAME);
    exit(1);
  }
  
  for(int i=0; i<this->storage.size(); i++){
    fprintf(fptr,"Set %d: ",i+1);
    for(int j=0; j<this->storage[i].size(); j++){
      fprintf(fptr,"\"%s\",",this->storage[i][j].get_raw_data());
    }
    fprintf(fptr,"\n");
  }
  fclose(fptr);
}
