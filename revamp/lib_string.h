#include<iostream>
#include<string>

#ifndef _STRING_LIBRARY_H_
#define _STRING_LIBRARY_H_

#include "Vector.h"

#define MAX_WORD_IN_A_SENTENCE 20
#define MAX_WORD_SIZE 40
#define USE_OLD_MEMORY 1
#define ALLOCATE_NEW_MEMORY 2

namespace abj{

class String{
private:
  char* storage;
  int curr_size;
  char capitalize(char c) const;
  int compare_string(char *str1, char *str2) const;
public:
  String();
  String(std::string data);
  String(const abj::String& data);
  String(char* data, int FLAG);
  String(const char* data);
  ~String();
  
  int size() const;
  char get(int index) const;
  bool set(int index, char c);
  void initialize(const abj::String& str);
  void initialize(char* str);
  void initialize(const char* str);
  void removeData();
  void insert_char_at_point(int index, char c);

  void print() const;
  void capitalize();

  char* get_raw_data() const;
  abj::String copy();

  // Concatenation
  void concatenate_at_point(abj::String& str, int index, char separator);
  void concatenate_at_point(abj::String& str, int index);
  void concatenate_at_end(abj::String& str, char separator);
  void concatenate_at_end(abj::String& str);
  
  bool equals(abj::String& data) const;
  bool equals(const char* data) const;
  void resize(int size);

  char lastChar() const;
  char operator[](int index) const;
  abj::String operator+(const abj::String& str);
  bool operator==(const abj::String& data) const;
  abj::String& operator=(const abj::String& data);
  bool operator>(const abj::String& data) const;
  bool operator<(const abj::String& data) const;
  bool operator<<(const abj::String& data) const;
  void swap(abj::String& data);

  void setStorage(char* storage);
  char* getStorage() const;
  void setSize(int newSize);

  static abj::String& getFileContent(const abj::String& filename);

  friend std::ostream& operator<<( std::ostream &output, const abj::String &data ){
    output <<"String size: " << data.curr_size << ", " << data.storage << "\n";
    return output;
  }

  static void test_function();
};


}
#endif
