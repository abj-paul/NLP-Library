
#include<iostream>

#ifndef _NON_WORD_H_
#define _NON_WORD_H_

#include "lib_string.h"
#include "lib_vector.h"

namespace abj{
#define VOCABULARY_FILE_NAME "vocabulary.txt"
#define DEBUG_VOCABULARY_FILE_NAME "debug-vocabulary.txt"
  class NonWord{
  public:
  private:
    abj::Vector<abj::String>vocabulary;

    void load_vocabulary();
    void print_vocabulary(); // For debug
    int binarySearch(int left_index, int right_index, abj::String& word);
    abj::Vector<abj::String> generate_candidate_set(abj::String word);
    int domerau_levensthein_edit_distance(abj::String& A, abj::String&& B);

    
  public:
    NonWord();
    bool isNonWord(abj::String& word);
    bool isNonWord(abj::String&& word);

    void get_correct_word();
    static void test_function();
  };
}


#endif
