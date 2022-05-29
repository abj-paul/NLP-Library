#include<iostream>
#include<vector>

#ifndef _COUNTER_SET_H_
#define _COUNTER_SET_H_

#include "lib_string.h"
#define NGRAM_PACKET_COUNT std::pair<std::vector<abj::String>, int>

namespace abj{
  class CounterSet{
  private:
    int ngram;
    std::vector<NGRAM_PACKET_COUNT> storage;
    const char* DEBUG_FILEAME="debug_counter_set.txt";
  public:
    CounterSet();
    ~CounterSet();

    void defineNGram(int ngram);
    bool insert(std::vector<abj::String>& element);
    int getCount(std::vector<abj::String>& element);
    [[nodiscard]] int size();
    void print();
    void print(abj::String& filename);
  };
}


#endif
