#include<iostream>
#include<vector>
#include<algorithm>

#ifndef _CONTINUATION_H_
#define _CONTINUATION_H_

#include "lib_string.h"
#include "Set.h"

#define _UNIGRAM_ 1
#define _BIGRAM_ 2
#define _TRIGRAM_ 3

namespace abj{
  class Continuation{
  private:
    static std::vector<abj::String> reverseVector(std::vector<abj::String>& data);
  public:
    static int getCount(const abj::String& targetStem, int NGram, std::vector<abj::String>& stemList); // strings that ends with Target
    static int wordsThatFollow(const abj::String& targetStem,int NGram, const std::vector<abj::String>& stemList); // Strings that starts with Target

    static int getNGramSize(std::vector<abj::String>& stemList, int nGram);
    static void test_function();
  };
}


#endif
