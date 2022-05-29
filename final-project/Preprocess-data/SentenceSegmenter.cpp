#include "SentenceSegmenter.h"

abj::SentenceSegmenter::SentenceSegmenter(abj::String corpus){
  // printf("Calling SentenceSegmenter Constructor\n");
  this->corpus.initialize(corpus);
  this->buildAbbreviationList();
}
abj::SentenceSegmenter::SentenceSegmenter(){
  // printf("Calling SentenceSegmenter Constructor\n");
  this->corpus=NULL;
  this->buildAbbreviationList();
}

abj::SentenceSegmenter::~SentenceSegmenter(){
  // for(unsigned long i=0; i<abbreviations.size(); i++) this->abbreviations[i].~String();
}
void abj::SentenceSegmenter::setCorpus(abj::String corpus){
  this->corpus.initialize(corpus);
}


bool abj::SentenceSegmenter::decision_tree(int index){
  // Handcrafted rules
  if((index!=0 && this->corpus[index-1]<=9 && this->corpus[index-1]>=0) || (index!=corpus.size()-1 && this->corpus[index+1]<=9 && this->corpus[index+1]>=0)) return false;

    //Decision tree from NLP playlist by da jurafsky
  if(this->punctuation.isPunctuation(this->corpus.get(index))){
      if(this->lots_of_space_after_it(index)){
	return true;
      }else{
	if(this->corpus.get(index)=='?' || this->corpus.get(index)=='!' || this->corpus.get(index)==':') return true;
	else if(this->corpus.get(index)=='.'){
	  if(!isAbbreviation(this->corpus,index)) return true;
	  else return false;
	}
	else return false;
      }
    }
  return false;
}

bool abj::SentenceSegmenter::lots_of_space_after_it(int index){
  if(index == this->corpus.size()-1) return true; //EOF

  index++;
  int space_count=0;
  while(this->corpus.get(index)!='\0'){
    if(this->corpus.get(index)==' ') space_count++;
    else break;
    if(space_count>=2) return true;
    index++;
  }
  if(space_count>=2) return true;
  return false;
}

bool abj::SentenceSegmenter::isAbbreviation(abj::String str, int index){
  int start_index=index;
  int end_index = index;

  int i=index;
  while(str[i]!=' ' && i>=0) {
    start_index--;
    i--;
  }
  start_index++; // because loop stopped at space

  i=index;
  while(str[i]!=' ' && i<str.size()) {
    end_index++;
    i++;
  }
  end_index--; // becasue loop stopped at space

  abj::String abbreviation = this->make_word(start_index, end_index);
  // printf("DEBUG: ");abbreviation.print();
  if(this->abbreviations.find(abbreviation)==true){
    char* abbreviationChar = abbreviation.get_raw_data();
    printf("Abbreviation detected! %s\n",abbreviationChar);
    free(abbreviationChar);
    return true;
  }
  if(abbreviation.size()==1 && abbreviation[0]!='A' && abbreviation[0]!='a') return true; //handcrafted rule For S. K. Das or similar abbreviation in name.
  return false;
}
// abbSKYabb
// 012345678
// make_word(3,5)
// allocation = 5-3+1 +1
abj::String abj::SentenceSegmenter::make_word(int start_index, int end_index){
  char* newWord = (char*)calloc(end_index-start_index+1+1, sizeof(char));  // +1 for NULL, +1 to balance the subtraction of indices
  int j=0;
  for(int i=start_index; i<=end_index; i++,j++)
    newWord[j]=this->corpus.get(i);
  newWord[j]='\0';

  abj::String newWord_abj(newWord,ALLOCATE_NEW_MEMORY);
  free(newWord);
  newWord=NULL;
  return newWord_abj;
}

void abj::SentenceSegmenter::buildAbbreviationList(){
  // LOADING messenger acronym list
  FILE* fptr = fopen(this->ABBREVIATION_FILE_NAME, "r");
  if(fptr==NULL){
    printf("Error opening %s file!Exiting...",this->ABBREVIATION_FILE_NAME);
    exit(1);
  }
  char newAbbrebiation[MAX_WORD_SIZE];
  while(!feof(fptr)){
    fscanf(fptr, "%s \n", newAbbrebiation);
    abj::String temp(newAbbrebiation);
    this->abbreviations.insert(temp);
  }
  fclose(fptr);

  //LOADING CSR acronym list
   fptr = fopen(this->ABBREVIATION_FILE_NAME, "r");
  if(fptr==NULL){
    printf("Error opening %s file!Exiting...",this->ABBREVIATION_FILE_NAME);
    exit(1);
  }
  while(!feof(fptr)){
    fscanf(fptr, "%s \n", newAbbrebiation);
    abj::String temp(newAbbrebiation);
    this->abbreviations.insert(temp);
  }
  fclose(fptr);

}

void abj::SentenceSegmenter::printAbbreviationsForDebug(){
  FILE* fptr = fopen(this->DEBUG_FILENAME, "w");
  if(fptr==NULL){
    printf("Error opening %s file!Exiting...",this->ABBREVIATION_FILE_NAME);
    exit(1);
  }
  fprintf(fptr,"Printing all abbreviations.\n");
  // for(int i=0; i<this->abbreviations.size(); i++) fprintf(fptr, "%d) %s\n", i+1, abbreviations[i].get_raw_data());
  this->abbreviations.print();
  fclose(fptr);
}

void abj::SentenceSegmenter::print(){
  FILE* fptr = fopen(this->DEBUG_FILENAME, "w");
  if(fptr==NULL){
    printf("Error opening %s file!Exiting...",this->ABBREVIATION_FILE_NAME);
    exit(1);
  }

  fprintf(fptr,"The segmented sentences are:--\n");
  for(int i=0; i<sentence_list.size(); i++){
    char* sentenceChar = this->sentence_list[i].get_raw_data();
    fprintf(fptr,"%d) %s\n",i+1,sentenceChar);
    free(sentenceChar);
  }
  fprintf(fptr, "Done printing all sentences!\n");
  fclose(fptr);
}
abj::String abj::SentenceSegmenter::make_sentence(int start_index, int end_index){
  char* store_in_heap = (char*)calloc(end_index-start_index+1+1, sizeof(char));

  int j=0;
  for(int i=start_index; i<=end_index; i++) {
    store_in_heap[j]=(char)this->corpus.get(i);
    j++;
  }
  store_in_heap[j]='\0';

  //  printf("j=%d\nInside: %s\n",j,store_in_heap);
  abj::String str(store_in_heap);
  //printf("The sentence is: %s\n",store_in_heap);
  free(store_in_heap);
  return str;
}

void abj::SentenceSegmenter::use_decision_tree(){
  int start_index=0,i=0;
  for(i=0; i<this->corpus.size(); i++){
    if(this->decision_tree(i)){
      abj::String sentence = this->make_sentence(start_index, i);
      if(sentence.size()<MIN_SENTENCE_SIZE) continue;
      this->sentence_list.push_back(sentence);
      start_index=i+2; // Because there is a space between (dot) and first word of next sentence
    }
  }
  abj::String last_sentence = this->make_sentence(start_index, i);
  if(last_sentence.size()!=0)this->sentence_list.push_back(last_sentence);
     
}

std::vector<abj::String>& abj::SentenceSegmenter::getSentenceList(){
  return this->sentence_list;
}

void abj::SentenceSegmenter::test_function(){
  printf("Testing SentenceSegmenter--------------------\n");
  //abj::String str("Joy, dipy and abhi went there. They travelled through the forest! The ghosts were lurking behind them, they will rip them apart the moment they see the opportunity! Abhi exclaimed, \"What a time to be alive!\". Hais, there is an error here, smh");
  // abj::String str("Joy, dipy and abhi went there. They travelled through the forest! The ghosts were lurking behind them, they will rip them apart the moment they see the opportunity! Abhi exclaimed, What a time to be alive! Hais, there is an error here, smh.");
  abj::String str = abj::String::getFileContent(*new abj::String("./Resources/sed-corpus.txt"));
  
  SentenceSegmenter ss(str);
  // ss.printAbbreviationsForDebug();
  ss.use_decision_tree();
  ss.print(); // it prints in log file
}
