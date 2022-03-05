#include<iostream>

#ifndef _STRING_LIBRARY_H_

#define MAX_WORD_IN_A_SENTENCE 20
#define MAX_WORD_SIZE 40


int string_len(char* x);
int string_len(const char* x);
void string_concatenate(char first[], char second[], char sentence[]);
bool is_same_string(const char* str,char word[]);
bool is_same_string(const char* str,const char* word);
bool is_same_string(char* str,const char* word);
bool is_same_string(char* str, char* word);
char** tokenizer_revamp(const char* str);
char** tokenizer_revamp(char* str);
void print_word_list(char** x);
void print_string(char* str);
void print_string(const char* str);
void string_copy(char* source_array, const char* the_word);

bool string_concatenate(char* corpus, char* word, const char separator);
bool string_insert_behind(char* str,int* index, char c);
char capitalize(char c);
char* capitalize(char* str);
void string_copy(char* source_array, char* the_word);

#endif
