
#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include "SentenceSegmenter.h"
#include "../Data-Structures/lib_string.h"
#include<vector>
#include "lib_punctuation.h"

// Return vector of tokens (for each sentence)
namespace abj{
class Tokenizer {
 private:
  std::vector<abj::String> tokens;
  abj::String sentence;

  const char separator = ' ';
  abj::String start_token;
  abj::String end_token;
  const char* DEBUG_FILENAME = "./Debug-Log-Files/tokenizer.txt";

  abj::String make_token(int start_index, int end_index);
  
 public:
  std::vector<abj::String>& getTokens();

  Tokenizer();
  Tokenizer(abj::String sentence);

  ~Tokenizer();

  void setString(abj::String sentence);
  void tokenize();

  void print();

  static void test_function();
};
}

#endif
