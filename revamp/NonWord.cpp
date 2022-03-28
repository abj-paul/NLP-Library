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

int NonWord::domerau_levensthein_edit_distance(abj::String& A, abj::String&& B){
  int m[MAX_WORD_SIZE][MAX_WORD_SIZE];
  for(int i=0; i<A.size(); i++) m[i][0]=i;
  for(int j=0; j<B.size(); j++) m[0][j]=j;

  int cost=0;
  // A,B indexing starts from 1 and m's indexing starts from 0 according to the algorithm. But our A,B starts from 0. So to compensate that, we start from 1 in the loop but subtract 1 (i-1 or j-1) when accessing A or B.
  for(int i=1; i<=A.size(); i++){
    for(int j=1; j<=B.size(); j++){
      if(A[i-1]==B[j-1]) cost=0;
      else cost=1;

      m[i][j] = std::min(m[i-1][j]+1,                //deletion
			std::min(m[i][j-1]+1,       //insertion
				 m[i-1][j-1]+cost));//substitution
      if(i>1 && j>1 && A[i-1]==B[j-1-1] && A[i-1-1]==B[j-1]){
	m[i][j] = std::min(m[i][j], m[i-2][j-2]+1); //transposition
      }
    }
  }

  return m[A.size()][B.size()];
}

abj::Vector<abj::String> NonWord::generate_candidate_set(abj::String word){
  abj::Vector<abj::String> candidate_set;
  
  for(int i=0; i<this->vocabulary.size(); i++){
    if(this->domerau_levensthein_edit_distance(word, this->vocabulary[i]) <=2) candidate_set.push(this->vocabulary[i]);
  }
  return candidate_set;
}

void NonWord::test_function(){
  abj::NonWord nonWord;
  abj::String word("able");
  printf("%s is nonword?%d\n",word.get_raw_data(),nonWord.isNonWord(word));

  abj::Vector<abj::String> candidate_set = nonWord.generate_candidate_set(word);
  for(int i=0; i <candidate_set.size(); i++) candidate_set[i].print();
}


int main(){
  abj::NonWord::test_function();
  return 0;
}
