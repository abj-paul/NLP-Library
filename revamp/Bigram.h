#include<vector>
#include<tgmath.h> //for LOG

#ifndef _BIGRAM_H_
#define _BIGRAM_H_

#include "Tokenizer.h"
#include "Stemmer.h"

//#define CORPUS "korpus/stanfordSentimentTreebank/datasetSentences.txt"
//#define DEFAULT_CORPUS "../LN-chapter.txt"
#define DEFAULT_CORPUS "../small-corpus.txt"


namespace abj{
class Bigram{
 private:
  abj::String corpus;
  abj::Vector<abj::Vector<abj::String>> tokenized_corpus;
  abj::Vector<abj::Vector<abj::String>> stemmed_corpus;
  int VOCABULARY_SIZE_FOR_BIGRAM=1;
  char* extract_content_from_file(const char* filename);
  void print_tokens();
  void print_stems();

  double find_probablity(abj::String phrase);
  int count_of_stem(abj::String word);
  int count_of_two_stem(abj::String s1, abj::String s2);
  
 public:
  Bigram(); // Uses default Corpus
  Bigram(const char* filename);
  //~Bigram();

  double probablity_laplace_smoothing(abj::String word2, char PIPE, abj::String word1);
  
  bool preprocess_corpus();
  void laplace_smoothing();
  static void test_function();
};
}

#endif
