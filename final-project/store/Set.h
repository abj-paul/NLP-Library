#include<iostream>
#include<vector>

#ifndef _SET_H_
#define _SET_H_

#include "lib_string.h"
#define NGRAM_PACKET std::vector<abj::String>

namespace abj{
  class Set{
  private:
    int ngram;
    std::vector<NGRAM_PACKET> storage;
    const char* DEBUG_FILEAME="debug_set.txt";
  public:
    Set();
    ~Set();

    void defineNGram(int ngram);
    bool insert(std::vector<abj::String>& element);
    [[nodiscard]] int size();
    void print();
    void print(abj::String& filename);
  };
}


#endif
