#ifndef _CONFUSION_MATRIX_H_
#define _CONFUSION_MATRIX_H_

#include "../lib_string.h"
#include "../lib_vector.h"

namespace abj{
#define ALPHABET_SIZE 26
#define ID_INSERTION "INSERTION"
#define ID_DELETION "DELETION"
#define ID_SUBSTITUTION "SUBSTITUTION"
#define ID_TRANSPOSITION "TRANSPOSITION"

  class ConfusionMatrix{
  protected:
    abj::Vector<abj::Vector<int>> insertion_confusion_matrix; // 2D array
    abj::Vector<abj::Vector<int>> deletion_confusion_matrix;
    abj::Vector<abj::Vector<int>> substitution_confusion_matrix;
    abj::Vector<abj::Vector<int>> transposition_confusion_matrix;
    
    void load_confusion_matrices();
    void print_confusion_matrix(abj::Vector<abj::Vector<int>> confusion_matrix, abj::String* filename); // Testing purpose


    //Internal Functions to divide the big task into smaller tasks
    void extract_content_from_file_into_matrix(abj::String* filename, abj::String* matrix_name);

    public:
    ConfusionMatrix();
    double character_probablity(char new_char, char separator, char old_char);
    // double probablity(abj::String main_word, char separator, abj::String candidate);
    // abj::String get_correct_word(abj::String& main_word);
    static void test_function();
  };
}

#endif
