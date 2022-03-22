#include "Bigram.h"

abj::Bigram::Bigram(){
  this->corpus.initialize(this->extract_content_from_file(DEFAULT_CORPUS));
}
abj::Bigram::Bigram(const char* filename){
  this->corpus.initialize(this->extract_content_from_file(filename));
}

char* abj::Bigram::extract_content_from_file(const char* filename){ //auxiliary function
  FILE* fptr = fopen(DEFAULT_CORPUS,"r");
  if(fptr==NULL){
    printf("Error! %s-File not found!\n",filename);
    exit(1);
  }

  fseek(fptr,0L,SEEK_END);
  int size = ftell(fptr);
  fseek(fptr, 0L, SEEK_SET);
  
  char* content = (char*)calloc(size+1, sizeof(char));
  fread(content, size, 1, fptr);
  content[size]='\0';

  return content;
}

bool abj::Bigram::preprocess_corpus(){
  /*abj::Punctuation punctuation;
  punctuation.setCorpus(this->corpus);
  punctuation.handle_punctuation();
  this->corpus = punctuation.getUpdatedCorpus();
  this->corpus.print();*/

  abj::SentenceSegmenter ss;
  ss.setCorpus(this->corpus);
  ss.use_decision_tree();
  ss.print();

  for(int i=0; i<ss.sentence_list.size(); i++){
    Punctuation p;
    p.setCorpus(ss.sentence_list.get(i));
    p.handle_punctuation();
    ss.sentence_list.set(i, p.getUpdatedCorpus());
  }
  
  ss.print();

  abj::Vector<abj::Vector<abj::String>> tokenized_corpus;
  for(int i=0; i<ss.sentence_list.size(); i++){
      abj::Tokenizer t ;
      t.setString(ss.sentence_list.get(i));
      t.tokenize();
      //t.print();
      abj::Vector<abj::String>tokens = t.getTokens();
      tokenized_corpus.push(tokens);
  }

  // Printing tokens
  for(int i=0; i<tokenized_corpus.size(); i++){
    printf("Sentence %d:\n",i+1);
         for(int j=0; j<tokenized_corpus[i].size(); j++){
	   tokenized_corpus[i].get(j).print();
	   //abj::String current_token = tokenized_corpus[i].get(j);
	   //stemmer.initialize(current_token);
	   //tokenized_corpus[i].set(j,stemmer.get_stem());
	   //tokenized_corpus[i].get(j).print();
    }
  }
  
  return true;
}

void abj::Bigram::test_function(){
  printf("Testing bigram---------------------------\n");
  abj::Bigram bigram;
  bigram.preprocess_corpus();
}
