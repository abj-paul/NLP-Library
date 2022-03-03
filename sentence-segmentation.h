#include<iostream>
#include<vector>

#ifndef _SETENCE_SEGMENTATION_H
#include "auxiliary.h"
#include "String-Library.h"

namespace abj{
  class SentenceSegmentation {
  public:
    std::vector<char*>sentence_list;
    SentenceSegmentation(char* string);
    void test_function();
    void use_decision_tree();
    ~SentenceSegmentation();

    //Extra Services
    char* punctuation_list = NULL;
    bool isPunctuation(char c);
  private:
    char* str;
    bool decision_tree(int i);
    const char* punctuation_list_containing_file = "punctuation.txt";
    int number_of_punctuation;
    char* getPunctuationList(const char* filename);
    bool lots_of_space_after_it(int i);
    bool isAbbreviation(char* str, int i);
    void print_sentence(int start_index, int i);
    char* make_sentence(int start_index, int i);
  };
}

#endif
