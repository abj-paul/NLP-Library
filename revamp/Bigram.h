#include<vector>
#include<tgmath.h> //for LOG

#ifndef _BIGRAM_H_
#define _BIGRAM_H_

#include "Tokenizer.h"
#include "Stemmer.h"

//#define CORPUS "korpus/stanfordSentimentTreebank/datasetSentences.txt"
//#define DEFAULT_CORPUS "../LN-chapter.txt"
#define DEFAULT_CORPUS "../small-corpus.txt"
//#define DEFAULT_CORPUS "sed-corpus.txt"


namespace abj{
class Bigram{
 private:
  abj::String corpus;
  abj::Vector<abj::Vector<abj::String>> stemmed_corpus;
  int VOCABULARY_SIZE_FOR_BIGRAM=1;
  char* extract_content_from_file(const char* filename);
  void print_stems();

  double find_probablity(abj::String phrase);
  int count_of_stem(abj::String word);
  int count_of_two_stem(abj::String s1, abj::String s2);
  double probablity_laplace_smoothing(abj::String word2, char PIPE, abj::String word1);
  
 public:
  Bigram(); // Uses default Corpus
  Bigram(const char* filename);
  void setCorpus(const char* filename);
  //~Bigram();
  
  bool preprocess_corpus();
  Vector<Vector<String>> get_stems_list(abj::String& text, abj::String tag);
  static void test_function();
  double text_probablity_using_laplace_smoothing(abj::String sentence);
};
}

#endif
