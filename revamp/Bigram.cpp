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

  for(int i=0; i<ss.sentence_list.size(); i++){
      abj::Tokenizer t ;
      t.setString(ss.sentence_list.get(i));
      t.tokenize();
      //t.print();
      abj::Vector<abj::String>tokens = t.getTokens();
      tokenized_corpus.push(tokens);
  }

  //printf("Printing tokens:--------\n");
  //print_tokens();

  //Stemming the tokens
  int stem_count=0;
  for(int i=0; i<tokenized_corpus.size(); i++){
    abj::Vector<abj::String> sentence_stems;
    for(int j=0; j<tokenized_corpus[i].size(); j++){
      Stemmer stemmer;
      abj::String current_token = tokenized_corpus[i].get(j);
      stemmer.initialize(current_token);
      abj::String current_stem = stemmer.get_stem();
      sentence_stems.push(current_stem);
      stem_count++;
    }
    stemmed_corpus.push(sentence_stems);
  }
  // Printing stems
  //printf("After stemming----\n");
  //print_stems();
  
  
  this->VOCABULARY_SIZE_FOR_BIGRAM = stem_count-1;
  return true;
}

int abj::Bigram::count_of_stem(abj::String stem){
  int count=0;
  for(int i=0; i<stemmed_corpus.size(); i++){
    for(int j=0; j<stemmed_corpus[i].size(); j++){
      abj::String corpus_stem(stemmed_corpus[i].get(j));
      if(stem.equals(corpus_stem)) count++;
    }
  }
  return count;
}

int abj::Bigram::count_of_two_stem(abj::String stem1, abj::String stem2){
  int count=0;
  for(int i=0; i<stemmed_corpus.size(); i++){
    for(int j=1; j<stemmed_corpus[i].size(); j++){
      if(stemmed_corpus[i][j-1].equals(stem1) && stemmed_corpus[i][j].equals(stem2)) count++;
    }
  }
  return count;
}

double abj::Bigram::probablity_laplace_smoothing(abj::String word2, char PIPE, abj::String word1 ){
  int x = count_of_two_stem(word1,word2)+1;
  int y = count_of_stem(word1)+VOCABULARY_SIZE_FOR_BIGRAM;
  return std::log(((double)x / (double)y));
}

void abj::Bigram::print_tokens(){
  for(int i=0; i<tokenized_corpus.size(); i++){
    for(int j=0; j<tokenized_corpus[i].size(); j++){
      this->tokenized_corpus[i].get(j).print();
    }
  }
}
void abj::Bigram::print_stems(){
  for(int i=0; i<stemmed_corpus.size(); i++){
    for(int j=0; j<stemmed_corpus[i].size(); j++){
      this->stemmed_corpus[i].get(j).print();
    }
  }
}

void abj::Bigram::test_function(){
  printf("Testing bigram---------------------------\n");
  abj::Bigram bigram;
  bigram.preprocess_corpus();

  /*  abj::String phrase("Victorious Soldiers !");
  abj::Tokenizer tokenizer(phrase);
  tokenizer.tokenize();
  abj::Vector<abj::String>tokens = tokenizer.getTokens();
  abj::Stemmer w1, w2;
  w1.initialize(tokens[0]);
  w2.initialize(tokens[1]);
  
  double p = bigram.probablity_laplace_smoothing(w2.get_stem(), '|', w1.get_stem());
  phrase.print();
  printf("probablity=%lf\n",p);
  */

  abj::String phrase("Stupid Soldiers !");
  abj::Tokenizer tokenizer(phrase);
  tokenizer.tokenize();
  abj::Vector<abj::String>tokens = tokenizer.getTokens();
  abj::Stemmer w1, w2;
  w1.initialize(tokens[0]);
  w2.initialize(tokens[1]);
  
  double p = bigram.probablity_laplace_smoothing(w2.get_stem(), '|', w1.get_stem());
  phrase.print();
  printf("probablity=%lf\n",p);

}

