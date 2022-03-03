#include<iostream>
#include<vector>

#ifndef _BIGRAM_H_
#include "sentence-segmentation.cpp"
#include "porters-algorithm.cpp"
//#define CORPUS "korpus/stanfordSentimentTreebank/datasetSentences.txt"
//#define CORPUS "LN-chapter.txt"
#define CORPUS "small-corpus.txt"

namespace abj{
class Bigram{
public:
  void test_function();
  Bigram(const char* corpus);
  ~Bigram();

  char* compiled_corpus_strings;
private:
  const char* compiled_corpus = "compiled_corpus.txt";
  FILE* corpus_fptr;
  int corpus_size=0;
  bool compile_and_normalize_corpus();
  double probablity(char* first_word, char* second_word);
  double log(double value);
  std::vector<char*>  get_word_from_sentence(char* sentence);
  char* make_word(int start_index, int end_index, char* sentece);


  bool load_all_corpus_strings();
};
}

#endif
