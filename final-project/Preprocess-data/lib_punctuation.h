#include<iostream>
#include<vector>

#ifndef _LIB_PUNCTUATION_H
#define _LIB_PUNCTUATION_H
#include "../Data-Structures/lib_string.h"


namespace abj {
  class Punctuation{
  private:
    const char punctuation_filename[MAX_WORD_SIZE*5] = "./Resources/punctuation.txt";
    std::vector<char>punctuation_list;
    const char separator=' ';

    const char* debug_filename = "./Debug-Log-Files/lib_punctuation.txt";
    FILE* fptr;
    
    abj::String corpus;
    
    int get_file_length(FILE* fptr);
    void get_punctuation_list();
  public:
    Punctuation(abj::String corpus);
    Punctuation();
    ~Punctuation();

    void setCorpus(abj::String corpus);
    void handle_punctuation();
    void handle_punctuation_with_decision_tree();

    void print();
    abj::String& getUpdatedCorpus();
    // Service
    bool isPunctuation(char c);
    static void test_function();
  };
}
#endif
