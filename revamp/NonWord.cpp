#include "NonWord.h"
using namespace abj;

NonWord::NonWord(){
  this->load_vocabulary();
  this->print_vocabulary();
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
    abj::Stemmer stemmer(new_string);
    this->vocabulary.push(stemmer.get_stem());
    // this->vocabulary.push(new_string);
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

Candidate NonWord::domerau_levensthein_edit_distance(abj::String& A, abj::String&& B){
  A.capitalize();
  B.capitalize();
  
  // Converting A to B
  int m[MAX_WORD_SIZE][MAX_WORD_SIZE];
  int direction[MAX_WORD_SIZE][MAX_WORD_SIZE];
  abj::Vector<int> backtrack_path;
  
  for(int i=0; i<=A.size(); i++) {
    m[i][0]=i;
    direction[i][0]=DELETION_DOWN_ARROW;
  }
  for(int j=0; j<=B.size(); j++){
    direction[0][j]=INSERTION_RIGHT_ARROW;
    m[0][j]=j;
  }
  direction[0][0]=NO_OPERATION;
  m[0][0]=0;

  int cost=0;
  // A,B indexing starts from 1 and m's indexing starts from 0 according to the algorithm. But our A,B starts from 0. So to compensate that, we start from 1 in the loop but subtract 1 (i-1 or j-1) when accessing A or B.
  for(int i=1; i<=A.size(); i++){
    for(int j=1; j<=B.size(); j++){
      if(A[i]==B[j]) cost=0;
      else cost=1;

      m[i][j] = std::min(m[i-1][j]+1,                //deletion
			std::min(m[i][j-1]+1,       //insertion
				 m[i-1][j-1]+cost));//substitution
      // Direction
      if(m[i][j]==m[i-1][j]+1) direction[i][j]=DELETION_DOWN_ARROW;
      else if(m[i][j]==m[i][j-1]+1) direction[i][j]=INSERTION_RIGHT_ARROW;
      else if(m[i-1][j-1]==m[i][j]) direction[i][j]=SAME_CHARACTER_DIAGONAL_ARROW;
      else if(m[i-1][j-1]+1==m[i][j]) direction[i][j]=SUBSTITUTION_DIAGONAL_ARROW;
      
      if(i>1 && j>1 && A[i-1]==B[j-1-1] && A[i-1-1]==B[j-1]){
	m[i][j] = std::min(m[i][j], m[i-2][j-2]+1); //transposition
	if(m[i][j]==m[i-2][j-2]+1) direction[i][j] = TRANSPOSITION_ARROW;
      }
    }
  }

  //print_direction(direction, A, B);
  this->backtracking(A.size(), B.size(), direction, &backtrack_path);
  backtrack_path.reverse();

  abj::Candidate candidate(B, m[A.size()][B.size()], backtrack_path);
  return candidate;
}

void NonWord::backtracking(int i, int j, int d[][MAX_WORD_SIZE], abj::Vector<int>* backtrack_path){
  if(i<0 || j<0) return;
  backtrack_path->push(d[i][j]);

  if(d[i][j]==INSERTION_RIGHT_ARROW){
    // weight_matrix+=weight[][];
    this->backtracking(i, j-1, d, backtrack_path);
  }
  else if(d[i][j]==DELETION_DOWN_ARROW) this->backtracking(i-1, j, d, backtrack_path);
  else if(d[i][j]==SAME_CHARACTER_DIAGONAL_ARROW) this->backtracking(i-1, j-1, d, backtrack_path);
  else if(d[i][j]==SUBSTITUTION_DIAGONAL_ARROW) this->backtracking(i-1, j-1, d, backtrack_path);
  else if(d[i][j]==TRANSPOSITION_ARROW) this->backtracking(i-2, j-2, d, backtrack_path);

  return;
}

void NonWord::print_direction(int d[][MAX_WORD_SIZE], abj::String A, abj::String B){
  for(int i=0; i<=A.size(); i++){
    for(int j=0; j<=B.size(); j++){
      print_med_direction(d[i][j]);
    }
    printf("\n");
  }
}
void NonWord::print_med_direction(int direction_Value){
      if(direction_Value==INSERTION_RIGHT_ARROW) printf("IN ");
      else if(direction_Value==DELETION_DOWN_ARROW) printf("DW ");
      else if(direction_Value==SAME_CHARACTER_DIAGONAL_ARROW) printf("SM ");
      else if(direction_Value==SUBSTITUTION_DIAGONAL_ARROW) printf("ST ");
      else if(direction_Value==TRANSPOSITION_ARROW) printf("TP ");
      else if(direction_Value==NO_OPERATION) printf("NA ");
}


abj::Vector<abj::Candidate> NonWord::generate_candidate_set(abj::String word){
  abj::Vector<abj::Candidate> candidate_set;
  word.capitalize();
  
  for(int i=0; i<this->vocabulary.size(); i++){
    this->vocabulary[i].capitalize();
    abj::Candidate candidate = this->domerau_levensthein_edit_distance(word, this->vocabulary[i]);
    if(candidate.get_med() <=2) candidate_set.push(candidate);

    //DEBUG
    candidate.print();
  }
  return candidate_set;
}


void NonWord::test_function(){
  abj::String word("abrevat");
  abj::NonWord nonWord;
  abj::Stemmer stemmer(word);

  printf("%s is nonword?%d\n",word.get_raw_data(),nonWord.isNonWord(word));

  abj::String stem = stemmer.get_stem();
  printf("The stemmed word is=%s\n",stem.get_raw_data());
  printf("Size=%d\n",stem.size());
  
  abj::Vector<abj::Candidate>v = nonWord.generate_candidate_set(stem);

  printf("Size=%d\n",v.size());
  for(int i=0; i<v.size(); i++) v[i].print();
}


/*int main(){
  abj::NonWord::test_function();
  return 0;
  }*/
