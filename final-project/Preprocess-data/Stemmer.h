#ifndef _STEMMER_H
#define _STEMMER_H
#include "../Data-Structures/lib_string.h"
#include<vector>

namespace abj{
  
  class Stemmer{
  private:
    abj::String word;
    std::vector<int> vowel_consonant_array; // VOWEL CONSONANT COUNT ARRAY
    const int VOWEL=1;
    const int CONSONANT=2;
    const int PUNCTUATION=3;
    int m_value;
    
    void build_vowel_consonant_array();
    int calculate_m_value();
    bool isConsonant(int index);
    bool isPunctuation(char c);
    bool regex(const char* condition); // For readability, we choose regex
    bool regex(const char* condition, int index);

    char smallize(char c);
    char capitalize(char c);
    bool isCapital(char c);


    bool ends_with(const char* suffix);
    void replace_suffix(const char* prev_suffix, const char* new_suffix);
  public:
    Stemmer(abj::String& word);
    Stemmer();
    void initialize(abj::String word);
    
    abj::String get_stem();
    static void test_function();
  };
}
#endif
