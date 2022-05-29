#include "CounterSet.h"

abj::CounterSet::CounterSet(){
  this->ngram = 0;
}
abj::CounterSet::~CounterSet(){
  for(int i=0; i<storage.size(); i++)
    for(int j=0; j<storage[i].first.size(); j++) storage[i].first[j].~String();
}

void abj::CounterSet::defineNGram(int ngram){
  this->ngram = ngram;
}

bool abj::CounterSet::insert(std::vector<abj::String>& element){
  //Finding match
  int match_count=0;
  for(int i=0; i<this->storage.size(); i++){
    match_count=0;
    for(int j=0; j<storage[i].first.size(); j++){
      if(element[j].equals(storage[i].first[j])) match_count++; 
    }
    if(match_count==this->ngram){
      storage[i].second++;
      return false;
    }
  }

  this->storage.push_back(make_pair(element,0));
  return true;
}

int abj::CounterSet::getCount(std::vector<abj::String>& element){
  int match_count=0;
  for(int i=0; i<this->storage.size(); i++){
    match_count=0;
    for(int j=0; j<storage[i].first.size(); j++){
      if(element[j].equals(storage[i].first[j])) match_count++; 
    }
    if(match_count==this->ngram){
      return this->storage[i].second;
    }
  }

  return 0; // Match not found
}


int abj::CounterSet::size(){
  return this->storage.size();
}

void abj::CounterSet::print(){
  this->print(* new abj::String(this->DEBUG_FILEAME));
}

void abj::CounterSet::print(abj::String& filename){
  FILE* fptr = fopen(filename.get_raw_data(), "w");
  if(fptr==NULL){
    printf("Error opening %s file! Exiting...\n",this->DEBUG_FILEAME);
    exit(1);
  }
  
  for(int i=0; i<this->storage.size(); i++){
    fprintf(fptr,"CounterSet %d: ",i+1);
    for(int j=0; j<this->storage[i].first.size(); j++){
      fprintf(fptr,"\"%s\",",this->storage[i].first[j].get_raw_data());
    }
    fprintf(fptr,"\tCount=%d\n",this->storage[i].second);
  }
  fclose(fptr);
}

