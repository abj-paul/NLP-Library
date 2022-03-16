//#include "lib_string.h"
//#include "lib_vector.h"
#include "auxiliary.h"


#ifndef _STEMMER_H
namespace abj{

#define VOWEL 1
#define CONSONANT 2
#define PUNCTUATION 3

  class Stemmer{
  private:
    abj::String word;
    abj::Vector<int> vowel_consonant_count; // VOWEL CONSONANT COUNT ARRAY
    
    void build_vowel_consonant_count_array();
    int m_value();
    bool isConsonant(int i);
    bool isPunctuation(char c);
    bool regex(const char* condition); // For readability, we choose regex
    bool regex(const char* condition, int index);

    char smallize(char c);
    char capitalize(char c);
    bool isCapital(char c);


    bool ends_with(const char* suffix, abj::String& word);
    void replace_suffix(const char* prev_suffix, const char* new_suffix);
  public:
    Stemmer(abj::String& word);
    Stemmer();
    void initialize(abj::String& word);
    
    abj::String get_stem();
    static void test_function();
  };
}
#endif
