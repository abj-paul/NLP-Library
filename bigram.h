#include<iostream>
#include<vector>

#ifndef _BIGRAM_H_
#include "sentence-segmentation.cpp"
#include "porters-algorithm.cpp"
//#define CORPUS "korpus/stanfordSentimentTreebank/datasetSentences.txt"
#define CORPUS "LN-chapter.txt"
//#define CORPUS "small-corpus.txt"
#define COMPILED_CORPUS "compiled-corpus.txt"

namespace abj{
class Bigram{
public:
  void test_function();
  Bigram(const char* corpus);
  ~Bigram();

  char* compiled_corpus_strings;
  void take_input_and_find_probablity();
  void display_process_in_detail(char* str);
  void unigram(char* str);
private:
  char start_symbol[MAX_WORD_SIZE] = "<s>";
  char end_symbol[MAX_WORD_SIZE] = "</s>";
  
  const char* compiled_corpus = COMPILED_CORPUS;
  FILE* corpus_fptr;
  int corpus_size=0;
  bool compile_and_normalize_corpus();
  double probablity(char* sentence);
  double log(double value);
  std::vector<char*>  get_word_from_sentence(char* sentence);
  std::vector<char*> get_word_from_sentence(const char* sentence);
  char* make_word(int start_index, int end_index, char* sentece);
  char* make_word(int start_index, int end_index, const char* sentence);


  bool load_all_corpus_strings();
  int get_word_count(char* word1, char* word2);
  int get_word_count(char* worwordd);

  double probablity(const char* sentence);
  void naive_punctuation_handling(char* str);
  char* normalize_string(char* str);
  void print_raw_corpus();
  void print_compiled_corpus();
};
}

#endif
