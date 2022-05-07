#include "SentenceSegmenter.h"
#define MIN_SENTENCE_SIZE 10

abj::SentenceSegmenter::SentenceSegmenter(abj::String corpus){
  this->corpus.initialize(corpus);
}

void abj::SentenceSegmenter::setCorpus(abj::String corpus){
  this->corpus.initialize(corpus);
}

abj::SentenceSegmenter::SentenceSegmenter(){
  //this->corpus=NULL;
}

abj::SentenceSegmenter::~SentenceSegmenter(){
  //this->corpus.~String();
  //this->punctuation.~Punctuation();
}

bool abj::SentenceSegmenter::decision_tree(int index){
  // Detedct punctuation in the string
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
  if(this->corpus.get(index)==-1) return true; //EOF

  index++;
  int space_count=0;
  while(this->corpus.get(index)!='\0'){
    if(this->corpus.get(index)==' ') space_count++;
    if(space_count>=2) return true;
    index++;
  }
  if(space_count>=2) return true;
  return false;
}

bool abj::SentenceSegmenter::isAbbreviation(abj::String str, int index){
  return false;
}

void abj::SentenceSegmenter::print(){
  printf("The segmented sentences are:--\n");
  for(int i=0; i<sentence_list.size(); i++)
    this->sentence_list[i].print();
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
  return str;
}

void abj::SentenceSegmenter::use_decision_tree(){
  int sentence_count=0;
  int start_index=0,i=0;
  for(i=0; i<this->corpus.size(); i++){
    if(this->decision_tree(i)){
      abj::String sentence = this->make_sentence(start_index, i);
      if(sentence.size()<MIN_SENTENCE_SIZE) continue;
      printf("%d) %s\n",sentence_count+1,sentence.get_raw_data());
      this->sentence_list.push(sentence);
      start_index=i+2; // Because there is a space between (dot) and first word of next sentence

	sentence_count++;
    }
    //else printf("%c",this->this->corpus.get(index));
  }
  abj::String last_sentence = this->make_sentence(start_index, i);
  if(last_sentence.size()!=0)this->sentence_list.push(last_sentence);
     
}

void abj::SentenceSegmenter::test_function(){
  printf("Testing SentenceSegmenter--------------------\n");
  //abj::String str("Joy, dipy and abhi went there. They travelled through the forest! The ghosts were lurking behind them, they will rip them apart the moment they see the opportunity! Abhi exclaimed, \"What a time to be alive!\". Hais, there is an error here, smh");
  // abj::String str("Joy, dipy and abhi went there. They travelled through the forest! The ghosts were lurking behind them, they will rip them apart the moment they see the opportunity! Abhi exclaimed, What a time to be alive! Hais, there is an error here, smh.");
  abj::String str = abj::String::getFileContent(*new abj::String("sed-corpus.txt"));
  
  SentenceSegmenter ss;
  ss.setCorpus(str);
  ss.use_decision_tree();
  ss.print();
}
