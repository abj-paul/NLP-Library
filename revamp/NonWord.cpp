#include "NonWord.h"
using namespace abj;

NonWord::NonWord(){
  this->load_vocabulary();
}

void NonWord::load_vocabulary(){
  FILE* fptr = fopen(VOCABULARY_FILE_NAME, "r");
  if(fptr==NULL){
    printf("%s file not found!\n", VOCABULARY_FILE_NAME);
    exit(-1);
  }
  char word[MAX_WORD_SIZE];
  while(!feof(fptr)){
    fscanf(fptr, "%s\n", word);
    abj::String new_string(word);
    this->vocabulary.push(new_string);
  }
  fclose(fptr);
}

void NonWord::print_vocabulary(){
  FILE* fptr = fopen(DEBUG_VOCABULARY_FILE_NAME, "w");
  if(fptr==NULL){
    printf("%s file not found!\n", DEBUG_VOCABULARY_FILE_NAME);
    exit(-1);
  }

  for(int i=0; i<this->vocabulary.size(); i++){
    fprintf(fptr,"%d) %s\n",i+1, this->vocabulary[i].get_raw_data());
  }
  fclose(fptr);
}

bool NonWord::isNonWord(abj::String& word){
  if(this->binarySearch(0, this->vocabulary.size()-1, word)==-1) return true;
  return false;
}
bool NonWord::isNonWord(abj::String&& word){
  if(this->binarySearch(0, this->vocabulary.size()-1, word)==-1) return false;
  return true;
}


int NonWord::binarySearch(int left_index, int right_index, abj::String& word){
  if(right_index >= left_index){
        int mid_index = left_index + (right_index - left_index) / 2;
 
        if (this->vocabulary[mid_index] == word)
            return mid_index;
        if (this->vocabulary[mid_index] > word)
            return binarySearch(left_index, mid_index - 1, word);
        return binarySearch(mid_index + 1, right_index, word);
    }
    return -1;
}

void NonWord::test_function(){
  abj::NonWord nonWord;
  abj::String word("aaShiRvAad");
  printf("%s is nonword?%d\n",word.get_raw_data(),nonWord.isNonWord(word));
}

int main(){
  abj::NonWord::test_function();
  return 0;
}
