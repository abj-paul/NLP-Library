
#ifndef _SETENCE_SEGMENTATION_H
#include "lib_punctuation.h"

namespace abj{
  class SentenceSegmenter {
  public:
    abj::Vector<abj::String>sentence_list;

    SentenceSegmenter(abj::String corpus);
    SentenceSegmenter();
    ~SentenceSegmenter();

    void setCorpus(abj::String corpus);

    void use_decision_tree();
    void print();
    static void test_function();
  private:
    abj::String corpus; // str
    abj::Punctuation punctuation;
    
    bool decision_tree(int i);
    bool lots_of_space_after_it(int i);
    bool isAbbreviation(abj::String str, int i);
    void print_sentence(int start_index, int i);
    abj::String make_sentence(int start_index, int i);
  };
}

#endif
