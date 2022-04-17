
#include<iostream>
#include<algorithm>

#ifndef _NON_WORD_H_
#define _NON_WORD_H_

#include "lib_string.h"
#include "lib_vector.h"
#include "Stemmer.h"
#include "Candidate.h"
#include "ConfusionMatrix.h"

namespace abj{
#define VOCABULARY_FILE_NAME "vocabulary.txt"
#define DEBUG_VOCABULARY_FILE_NAME "debug-vocabulary.txt"

#define DELETION_DOWN_ARROW 1
#define INSERTION_RIGHT_ARROW 2
#define SAME_CHARACTER_DIAGONAL_ARROW 3
#define SUBSTITUTION_DIAGONAL_ARROW 4
#define TRANSPOSITION_ARROW 5
#define NO_OPERATION 6
  
  class NonWord : public ConfusionMatrix
  {
  private:
    abj::Vector<abj::String>vocabulary;

    void load_vocabulary();
    int binarySearch(int left_index, int right_index, abj::String& word);
    void print_vocabulary(); // For debug

    bool isNonWord(abj::String& word);
    bool isNonWord(abj::String&& word);

    abj::Candidate domerau_levensthein_edit_distance(abj::String& A, abj::String&& B);
    void print_direction(int d[][MAX_WORD_SIZE], abj::String A, abj::String B);
    void print_med_direction(int direction_Value);


    void backtracking(int i, int j, int d[][MAX_WORD_SIZE], abj::Vector<int>*backtrack_path);
    
  public:
    NonWord();
    //void get_correct_word();
    abj::Vector<abj::Candidate> generate_candidate_set(abj::String word);
    static void test_function();
  };
}


#endif
