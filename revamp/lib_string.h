#include<iostream>

#ifndef _STRING_LIBRARY_H_
#define MAX_WORD_IN_A_SENTENCE 20
#define MAX_WORD_SIZE 40
#define USE_OLD_MEMORY 1
#define ALLOCATE_NEW_MEMORY 1

namespace abj{

class String{
	private:
		char* storage;
		int curr_size;
                int curr_capacity;
		char capitalize(char c);
	public:
		String();
		String(abj::String& data);
		String(char* data, int FLAG);
		String(const char* data);

		int size();
  int capacity();
		int get(int index);
  void initialize(abj::String& str);
  void initialize(char* str);
  void removeData();
  void insert_char_at_point(int index, char c);

		void print();
		void capitalize();

		char* get_raw_data();
		abj::String copy();

		// Concatenation
		void concatenate_at_point(abj::String& str, int index, char separator);
		void concatenate_at_end(abj::String& str, char separator);

		bool equals(abj::String& data);
		bool equals(const char* data);
		void resize(int size);

		static void test_function();
};


//char** tokenizer_revamp(char* str);
//void print_word_list(char** x);
}
#endif
