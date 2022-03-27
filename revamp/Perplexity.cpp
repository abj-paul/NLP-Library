#include "Perplexity.h"
using namespace abj;

Perplexity::Perplexity(){
  this->corpus_filename.initialize(DEFAULT_CORPUS);
  this->train_part=0.8;
  this->test_part=0.2;

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
    printf("Error! Too small corpus, can not create test train set!\n");
    exit(1);
  }
  // Building train set
  FILE* train_fptr = fopen(train_corpus.get_raw_data(), "a+");
  for(int i=0; i<train_sentence_count; i++){
    //fprintf(train_fptr, "%s", ss.sentence_list[i].get_raw_data()); // Verify the output!!!!!!!!!
    fputs(ss.sentence_list[i].get_raw_data(), train_fptr);
  }
  fclose(train_fptr);

  // Building test set
  FILE* test_fptr = fopen(test_corpus.get_raw_data(), "a+");
  for(long long int i=(long long int)train_sentence_count; i<ss.sentence_list.size(); i++){
    //fprintf(test_fptr, "%s ", ss.sentence_list[i].get_raw_data()); // Verify the output!!!!!!!!!
    fputs(ss.sentence_list[i].get_raw_data(), test_fptr);
  }
  fclose(test_fptr);
}

void Perplexity::build_bigram_model(){
  this->bigram.setCorpus(this->train_corpus.get_raw_data());
  this->bigram.preprocess_corpus();
}

// Returns AVERAGE perplexity value
double Perplexity::test_bigram_model(){
  abj::String corpus(read_file(this->test_corpus.get_raw_data()));
  SentenceSegmenter ss(corpus);
  ss.use_decision_tree();
  
  double total_perplexity=0;
  for(int i=0; i<ss.sentence_list.size(); i++){
    double perplexity = 0; // In log format
    double sentence_probablity = this->bigram.text_probablity_using_laplace_smoothing(ss.sentence_list[i]);

   double number_of_words = 10;
    
    perplexity = pow(pow(10,((-1)*(sentence_probablity))), 1/number_of_words);
    printf("N=%lf, 1/N(probablity)=%lf\n",number_of_words, perplexity);
    total_perplexity += perplexity;
  }
  return (total_perplexity/ss.sentence_list.size());
}


double Perplexity::perplexity(){
  this->split_corpus();
  this->build_bigram_model();
  return this->test_bigram_model();
}
void Perplexity::test_function(){
  abj::Perplexity pp;
  printf("Perplexity is=%lf",pp.perplexity());
}
