#include<iostream>
#include<vector>

#ifndef abj
#include "sentence-segmentation.cpp"
#include "porters-algorithm.cpp"
#define CORPUS "korpus/stanfordSentimentTreebank/datasetSentences.txt"

namespace abj{
class Bigram{
public:
  void test_function();
  Bigram(const char* corpus);
  ~Bigram();
private:
  const char* compiled_corpus = "compiled_corpus.txt";
  FILE* corpus_fptr;
  char* all_strings_in_corpus;
  bool compile_and_normalize_corpus();
  double probablity(char* first_word, char* second_word);
  double log(double value);
  std::vector<char*>  get_word_from_sentence(char* sentence);
  char* make_word(int start_index, int end_index, char* sentece);
};
}

#endif
