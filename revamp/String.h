#include<iostream>

#ifndef _STRING_LIBRARY_H_

namespace abj{
#define MAX_WORD_IN_A_SENTENCE 20
#define MAX_WORD_SIZE 40
#define USE_OLD_MEMORY 1
#define ALLOCATE_NEW_MEMORY 1

class String{
	private:
		char* storage;
		int curr_size;
		char capitalize(char c);
	public:
		String();
		String(abj::String& data);
		String(char* data);
		String(const char* data);

		int size();
		char get(int index);

		void print();
		void capitalize();

		char* get_raw_data();
		String copy();

		// Concatenation
		void concatenate_at_point(abj::String str, char separator);
		void concatenate_at_end(abj::String str, int index, char separator);

		bool equals(abj::String data);
		bool equals(const char* data);

		static void test_function();
};


//char** tokenizer_revamp(char* str);
//void print_word_list(char** x);
}
#endif
