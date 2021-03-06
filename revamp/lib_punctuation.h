#include<iostream>

#ifndef _LIB_PUNCTUATION_H
#define _LIB_PUNCTUATION_H
#include "lib_string.h"
// #include "lib_vector.h"
#include "Vector.h"


namespace abj {
  class Punctuation{
  private:
    const char punctuation_filename[MAX_WORD_SIZE*5] = "punctuation.txt";
    abj::Vector<char>punctuation_list;
    const char separator=' ';
    
    abj::String corpus;

    int get_file_length(FILE* fptr);
    void get_punctuation_list();
  public:
    Punctuation(abj::String corpus);
    Punctuation();
    ~Punctuation();

    void setCorpus(abj::String corpus);
    void handle_punctuation();
    static void test_function();

    void print();
    abj::String getUpdatedCorpus();
    // Service
    bool isPunctuation(char c);
  };
}
#endif
