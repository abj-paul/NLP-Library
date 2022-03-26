#include "Perplexity.h"
using namespace abj;

Perplexity::Perplexity(){
  this->corpus_filename.initialize(DEFAULT_CORPUS);
  this->train_part=0.8;
  this->train_part=0.2;

  this->train_corpus.initialize("train_corpus.txt");
  this->test_corpus.initialize("test_corpus.txt");
}

void Perplexity::set_corpus_file(const char* filename){
  this->corpus_filename.initialize((char*)filename);
}

void Perplexity::set_train_test_split_ratio(double train, double test){
  this->train_part = train/100;
  this->test_part = test/100;
}

char* Perplexity::read_file(const char* filename){ //auxiliary function
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


  // Segment the corpus into sentences. Then take 80% of the sentences. 
void Perplexity::split_corpus(){
  SentenceSegmenter ss;
  ss.setCorpus(read_file(this->corpus_filename.get_raw_data()));
  ss.use_decision_tree();

  double train_sentence_count=std::ceil(ss.sentence_list.size()*train_part);
  double test_sentence_count=ss.sentence_list.size()-train_sentence_count;

  if(test_sentence_count==0){
    printf("Erro! Too small corpus, can not create test train set!\n");
    exit(1);
  }
  // Building train set
  FILE* train_fptr = fopen(train_corpus.get_raw_data(), "a+");
  for(int i=0; i<train_sentence_count; i++){
    fprintf(train_fptr, "%s", ss.sentence_list[i].get_raw_data()); // Verify the output!!!!!!!!!
  }
  fclose(train_fptr);

  // Building test set
  FILE* test_fptr = fopen(test_corpus.get_raw_data(), "a+");
  for(long long int i=(long long int)train_sentence_count; i<ss.sentence_list.size(); i++){
    fprintf(test_fptr, "%s ", ss.sentence_list[i].get_raw_data()); // Verify the output!!!!!!!!!
  }
  fclose(test_fptr);
}

double Perplexity::perplexity(){
  this->split_corpus();
  this->build_bigram_model();
  this->test_bigram_model();

  return -1;
}
void Perplexity::build_bigram_model(){}
void Perplexity::test_bigram_model(){}


void Perplexity::test_function(){
  abj::Perplexity pp;
  pp.perplexity();
}
