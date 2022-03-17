
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
  char* extract_content_from_file(const char* filename);
 public:
  Bigram(); // Uses default Corpus
  Bigram(const char* filename);
  //~Bigram();
  
  bool preprocess_corpus();
  static void test_function();
};
}

#endif
