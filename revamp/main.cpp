#include "lib_string.h"
// #include "Vector.h"
#include<iostream>
// #include "lib_punctuation.h"
// #include "SentenceSegmenter.h"
// #include "Tokenizer.h"
// #include "Stemmer.h"
//#include "Bigram.h"
//#include "Perplexity.h"
// #include "NoisyChannelModel.h"

void vector_test_function();
void loadFileToVector();
int main(){
  // abj::String::test_function();
  // abj::Vector<abj::String>::test_function();
  // vector_test_function();
  loadFileToVector();
  // abj::Punctuation::test_function();
	// abj::SentenceSegmenter::test_function();
	// abj::Tokenizer::test_function();
	// abj::Stemmer::test_function();

        // abj::Bigram::test_function();
	//abj::Perplexity::test_function();
  //abj::NonWord::test_function();
  // abj::NoisyChannelModel::test_function();
return 0;
}


void vector_test_function(){
printf("Testing Vector----------------------\n");
 abj::Vector<abj::String> x;
 abj::Vector<abj::String> y;
 
 abj::String firstName("Abhi");
 abj::String lastName("Paul");
 x.push(firstName);
 x.push(*new abj::String("Jit"));
 x.push(lastName);
 x.print();
 
 // y.push(x);
 for(int i=0; i<x.size(); i++) x[i].~String();
 y.push(*new abj::String("Empire!"));
 y.print();
 for(int i=0; i<x.size(); i++) y[i].~String();
}

void loadFileToVector(){
  abj::Vector<abj::String>arr;

  FILE* fptr = std::fopen("sed-corpus.txt","r");
  if(fptr==NULL) exit(1);

  char str[MAX_WORD_SIZE];
  // int size=0;
  while(!feof(fptr)){
    fscanf(fptr, "%s", str);
    abj::String myStr(str);
    arr.push(myStr);
    // arr[size] = myStr;
    // size++;
  }
  arr.reverse();
  arr.get(arr.size()-1).print();
  arr.set(arr.size()-1, *new abj::String("Abhijit Paul"));
  arr.get(arr.size()-1).print();


  abj::Vector<abj::String> new_arr(arr);
  for(int i=0; i<arr.size(); i++) arr[i].~String();

  new_arr.reverse();
  new_arr.get(0).print();
  new_arr.get(arr.size()-1).print();
  for(int i=0; i<new_arr.size(); i++) new_arr[i].~String();
  
}
