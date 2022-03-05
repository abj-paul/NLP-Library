#ifndef _PORTERS_ALGORITHM_H

#include "String-Library.cpp"
#include "auxiliary.cpp"
#define VOWEL 1
#define CONSONANT 2
#define PUNCTUATION 3

// Function Prototypes
int* vowel_consonant_count_array(const char* str);
int m_value(const char* str);
bool isConsonant(int i, const char* str);
bool isPunctuation(char c);
bool regex(const char* condition, const char* str);

bool ends_with(const char* suffix, const char* word);
void replace_suffix(char* word, const char* prev_suffix, const char* new_suffix);
char* get_stem(char* word);
void test_functions();


#endif
