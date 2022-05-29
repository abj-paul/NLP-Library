#include "Evaluation.h"

abj::Evaluation::Evaluation(){
  this->perplexity = 0;
}
abj::Evaluation::~Evaluation(){
  this->perplexity = 0;
}


abj::String& abj::Evaluation::extract_content_from_file(const abj::String& filename){ //auxiliary function
  FILE* fptr = fopen(filename.get_raw_data(),"r");
  if(fptr==NULL){
    printf("Error! %s-File not found!\n",filename.get_raw_data());
    exit(1);
  }

  fseek(fptr,0L,SEEK_END);
  int size = ftell(fptr);
  fseek(fptr, 0L, SEEK_SET);
  
  char* content = (char*)calloc(size+1, sizeof(char));
  fread(content, size, 1, fptr);
  content[size]='\0';

  return *new abj::String(content);
}

std::vector<abj::String> abj::Evaluation::getSentenceList(abj::String& content){
  abj::SentenceSegmenter ss(content);
  ss.use_decision_tree();
  return ss.getSentenceList();
}


void abj::Evaluation::splitIntoTrainAndTestDataset(abj::String& filename, double testRatio, double trainRatio) // in percentage
{
  abj::String text = this->extract_content_from_file(filename);
  std::vector<abj::String> sentences = this->getSentenceList(text);
  int trainSentenceCount = std::ceil((double)sentences.size()*trainRatio/100);
  int testSentencecount = sentences.size() - trainSentenceCount;

  // Creating train dataset
  FILE* fptr = fopen(this->TRAIN_FILE_NAME, "w");
  if(fptr==NULL){
    printf("%s File not found! Exiting...\n",this->TRAIN_FILE_NAME);
    exit(1);
  }
  for(int i=0; i<trainSentenceCount; i++) fprintf(fptr,"%s", sentences[i].get_raw_data());
  fclose(fptr);

  //Creating test dataset
  fptr = fopen(this->TEST_FILE_NAME, "w");
  if(fptr==NULL){
    printf("%s File not found! Exiting...\n",this->TEST_FILE_NAME);
    exit(1);
  }
  for(int i=trainSentenceCount; i<sentences.size(); i++) fprintf(fptr,"%s", sentences[i].get_raw_data());
  fclose(fptr);

  // Clearing heap
  for(int i=0; i<sentences.size(); i++) sentences[i].~String();
}


double abj::Evaluation::measurePerplexity(){
  abj::NGram bigram(2,*new abj::String(this->TRAIN_FILE_NAME));
  // bigram.preprocess_corpus();

  abj::String& testData = this->extract_content_from_file(this->TEST_FILE_NAME);
  // double logProbablity = bigram.probablity(testData);
  double logProbablity = bigram.probablity_sentence(testData);
  this->perplexity = (-1)*(logProbablity / (double)bigram.getNGramSize());
  return this->perplexity;
}

void abj::Evaluation::test_function(){
  abj::Evaluation evaluation;
  evaluation.splitIntoTrainAndTestDataset(*new abj::String("./Resources/100_lines.txt"), 20, 80);
  // evaluation.splitIntoTrainAndTestDataset(*new abj::String("sed-corpus.txt"), 20, 80);
  std::cout<<"Perplexity"<<evaluation.measurePerplexity()<<std::endl;
}
