#include<iostream>

#ifndef _KNEESER_NEY_H_
#define _KNEESER_NEY_H_

#include<vector>
#include "../Data-Structures/lib_string.h"
#include "../LanguageModel/PrecomputeNGram.h"
#include "../LanguageModel/NGram.h"

namespace abj{
  class KneeserNey{
  private:
    int highestNGramValue;
    abj::String text;
    std::vector<abj::String> textStemList;
    std::vector<abj::String> corpusStemList;
    double d_value=0.75;
    int _NGRAM_SIZE_=30;

  public:
    KneeserNey(int nGram, const abj::String& text, const std::vector<abj::String>& corpusStemList);
    double kneeserNey(int nGram, int stemIndex);
    double kneeserNey_with_delta(int nGram, int stemIndex);

    int getPrefixCount(int ngram, const std::vector<abj::String>& ngram_packet);
    int getSuffixCount(int ngram, const std::vector<abj::String>& ngram_packet);

    static void test_function();
  };
}

#endif
