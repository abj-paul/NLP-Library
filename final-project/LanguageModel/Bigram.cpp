#include "Bigram.h"

abj::Bigram::Bigram(const abj::String& fileName){
  this->corpusFileName.initialize(fileName);
  this->fptr = fopen(this->DEBUG_FILE, "w");
}

abj::Bigram::~Bigram(){
  for(int i=0; i<this->stem_list.size(); i++) stem_list[i].~String();
  fclose(this->fptr);
}


void abj::Bigram::preprocess_corpus(){
  abj::String corpusData = this->getFileData();
  this->stem_list = this->getStemList(corpusData); // This function preprocessed the given text before generating the stem list.
}

// This function preprocessed the given text before generating the stem list.
std::vector<abj::String> abj::Bigram::getStemList(const abj::String& text){
  // First, Segment sentence
  abj::SentenceSegmenter ss(text);
  ss.use_decision_tree();
  std::vector<abj::String> sentences = ss.getSentenceList();

  // Then handle punctuaio
  for(int i=0; i<sentences.size(); i++){
    abj::Punctuation punctuation(sentences[i]);
    punctuation.handle_punctuation();
    sentences[i] = punctuation.getUpdatedCorpus();
  }
  // Then tokenize
 std::vector<abj::String> tokens;
 for(int i=0; i<sentences.size(); i++){
   abj::Tokenizer tokenizer(sentences[i]);
   tokenizer.tokenize();
   std::vector<abj::String> current_sentence_tokens = tokenizer.getTokens();
   for(int j=0; j<current_sentence_tokens.size(); j++)
     tokens.push_back(current_sentence_tokens[j]);
 }
 // Now Stem them
 std::vector<abj::String> stems;
 for(int i=0; i<tokens.size(); i++){
   abj::Stemmer stemmer(tokens[i]);
   stems.push_back(stemmer.get_stem());
 }
 return stems;
}

std::vector<abj::String>& abj::Bigram::getStemList(){
  return this->stem_list;
}
abj::String abj::Bigram::getFileData(){
  char* corpusChar = this->corpusFileName.get_raw_data();
  FILE *fptr = fopen(corpusChar, "r");
  if(fptr==NULL){
    printf("Error opening file %s. Exiting....\n",corpusChar);
    exit(1);
  }
  free(corpusChar);
  fseek(fptr, 0, SEEK_END);
  unsigned int file_size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);  /* same as rewind(f); */

  char *buffer = (char*)malloc(file_size + 1);
  fread(buffer, file_size, 1, fptr);
  fclose(fptr);

  buffer[file_size] = 0;
  abj::String fileData(buffer);
  free(buffer);
  return fileData;
}

int abj::Bigram::count(abj::String& stemmedWord){
  stemmedWord.capitalize();
  int count=0;
  for(int i=0; i<this->stem_list.size(); i++){
    stem_list[i].capitalize();
    if(stem_list[i].equals(stemmedWord)) count++;
  }
  return count;
}

int abj::Bigram::count(abj::String& stemmedFirstword, abj::String& stemmedSecondword){
stemmedFirstword.capitalize();
stemmedSecondword.capitalize();
int count=0;
for(int i=0; i<this->stem_list.size()-1; i++){
  this->stem_list[i].capitalize();
  if(stem_list[i].equals(stemmedFirstword) && stem_list[i+1].equals(stemmedSecondword)) count++;
 }
return count;
}

double abj::Bigram::probablity(const abj::String& text){
  std::vector<abj::String> textStems = this->getStemList(text);

  double textProbablity = 0;
  for(int i=0; i<textStems.size()-1; i++){
    double currentProbablity = this->laplace_smoothing_probablity(textStems[i+1], '|', textStems[i]);
    textProbablity +=  currentProbablity;

    //print
    char* textStemChar = textStems[i].get_raw_data();
    char* nextTextStemChar = textStems[i+1].get_raw_data();
    fprintf(fptr,"P(%s|%s)=%lf\n", nextTextStemChar, textStemChar, currentProbablity);
    free(textStemChar);
    free(nextTextStemChar);
  }

  return textProbablity;
}

double abj::Bigram::no_smoothing_probablity(abj::String& stem2, char separator, abj::String& stem1){
  int x = count(stem1,stem2);
  int y = count(stem1);
  // printf("count(%s,%s)=%d\n",stem1.get_raw_data(),stem2.get_raw_data(), x);
  // printf("count(%s)=%d\n",stem1.get_raw_data(),y);
  return std::log(((double)x / (double)y));
}

double abj::Bigram::laplace_smoothing_probablity(abj::String& stem2, char separator, abj::String& stem1){
  int x = count(stem1,stem2)+1;
  int y = count(stem1)+this->stem_list.size();
  // printf("count(%s,%s)=%d\n",stem1.get_raw_data(),stem2.get_raw_data(), x);
  // printf("count(%s)=%d\n",stem1.get_raw_data(),y);
  return std::log(((double)x / (double)y));
}


void abj::Bigram::test_function(){
  abj::String corpus("./Resources/100_lines.txt");
  abj::Bigram bigram(corpus);
  bigram.preprocess_corpus();
  std::cout<<"P="<<bigram.probablity(*new abj::String("The lord of the rings"))<<std::endl;
  std::cout<<"P="<<bigram.probablity(*new abj::String("rings lord of the the"))<<std::endl;
}
