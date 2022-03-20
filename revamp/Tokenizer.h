
#ifndef _TOKENIZER_H
#define _TOKENIZER_H

#include "SentenceSegmenter.h"
//#include "lib_string.h"
//#include "lib_vector.h"
//#include "lib_punctuation.h"

// Return vector of tokens (for each sentence)
namespace abj{
class Tokenizer {
 private:
  abj::Vector<abj::String> tokens;
  abj::String sentence;

  const char separator = ' ';
  abj::String start_token;
  abj::String end_token;

  abj::String make_token(int start_index, int end_index);
  
 public:

  Tokenizer();
  Tokenizer(abj::String sentence);

  ~Tokenizer();

  void setString(abj::String sentence);
  void tokenize();
  abj::Vector<abj::String> getTokens();

  void print();

  static void test_function();
};
}

#endif
