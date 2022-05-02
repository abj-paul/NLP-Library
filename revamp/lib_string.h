#include<iostream>
#include<string>

#ifndef _STRING_LIBRARY_H_
#define _STRING_LIBRARY_H_

#include "lib_vector.h"

#define MAX_WORD_IN_A_SENTENCE 20
#define MAX_WORD_SIZE 40
#define USE_OLD_MEMORY 1
#define ALLOCATE_NEW_MEMORY 2

namespace abj{

class String{
private:
  char* storage;
  int curr_size;
  char capitalize(char c);
  int compare_string(char *str1, char *str2);
public:
  String();
  String(std::string data);
  String(abj::String& data);
  String(char* data, int FLAG);
  String(const char* data);
  ~String();
  
  int size();
  char get(int index);
  bool set(int index, char c);
  void initialize(abj::String& str);
  void initialize(char* str);
  void initialize(const char* str);
  void removeData();
  void insert_char_at_point(int index, char c);

  void print();
  void capitalize();

  char* get_raw_data();
  abj::String copy();

  // Concatenation
  void concatenate_at_point(abj::String& str, int index, char separator);
  void concatenate_at_point(abj::String& str, int index);
  void concatenate_at_end(abj::String& str, char separator);
  void concatenate_at_end(abj::String& str);
  
  bool equals(abj::String& data);
  bool equals(const char* data);
  void resize(int size);

  char lastChar();
  char operator[](int index);
  abj::String operator+(abj::String str);
  bool operator==(abj::String data);
  abj::String& operator=(abj::String data);
  bool operator>(abj::String data);
  bool operator<(abj::String data);

  static void test_function();
};


//char** tokenizer_revamp(char* str);
//void print_word_list(char** x);
}
#endif
