#ifndef _CONFUSION_MATRIX_H_
#define _CONFUSION_MATRIX_H_

#include "../lib_string.h"
// #include "../lib_vector.h"
#include<vector>

namespace abj{
#define MATRIX_SIZE 26
#define ID_INSERTION "INSERTION"
#define ID_DELETION "DELETION"
#define ID_SUBSTITUTION "SUBSTITUTION"
#define ID_TRANSPOSITION "TRANSPOSITION"

  class ConfusionMatrix{
  protected:
    std::vector<std::vector<int>> insertion_confusion_matrix; // 2D array
    std::vector<std::vector<int>> deletion_confusion_matrix;
    std::vector<std::vector<int>> substitution_confusion_matrix;
    std::vector<std::vector<int>> transposition_confusion_matrix;
    
    void load_confusion_matrices();
    void print_confusion_matrix(std::vector<std::vector<int>> confusion_matrix, abj::String* filename); // Testing purpose

    //Internal Functions to divide the big task into smaller tasks
    void extract_content_from_file_into_matrix(abj::String* filename, abj::String* matrix_name);

    public:
    ConfusionMatrix();
    static void test_function();
  };
}

#endif
