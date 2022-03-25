
#ifndef _PERPLEXITY_H_
#define _PERPLEXITY_H_

#include "Bigram.h"
namespace abj{
class Perplexity {
 private:
  abj::Vector<abj::Vector<abj::String>> stemmed_corpus;
  abj::String corpus_filename;
  void build_bigram_model();
  void test_bigram_model();

 public:
  Perplexity();
  void set_corpus_file(const char* filename);
  void set_train_test_split_ratio(double train, double test);
  double perplixity();
};
}

#endif
