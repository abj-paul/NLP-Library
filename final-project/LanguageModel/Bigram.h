#include<tgmath.h>
#include<vector>

#ifndef _BIGRAM_H_
#define _BIGRAM_H_

#include "../Data-Structures/lib_string.h"
#include "../Preprocess-data/SentenceSegmenter.h"
#include "../Preprocess-data/lib_punctuation.h"
#include "../Preprocess-data/Tokenizer.h"
#include "../Preprocess-data/Stemmer.h"

namespace abj{
  class Bigram{
  private:
    double BIGRAM_SIZE;
    std::vector<abj::String> stem_list;
    abj::String corpusFileName;
    FILE* fptr;
    const char* DEBUG_FILE = "./Debug-Log-Files/bigram.txt";


    int count(abj::String& stemmedWord);
    int count(abj::String& stemmedFirstword, abj::String& stemmedSecondword);

    void precompute();
    // Auxiliary functions
    [[nodiscard]] abj::String getFileData();
    std::vector<abj::String> getStemList(const abj::String& text);


  public:
    double no_smoothing_probablity(abj::String& stem2, char separator, abj::String& stem1);
    double laplace_smoothing_probablity(abj::String& stem2, char separator, abj::String& stem1);
    double kneeser_ney_probablity(abj::String& stem2, char separator, abj::String& stem1);
    double kneeser_ney_probablity_for_unseen_words(abj::String& stem2, char separator, abj::String& stem1);
  
    void preprocess_corpus();
    double probablity(const abj::String& text);
    std::vector<abj::String>& getStemList();

    Bigram(const abj::String& filename);
    ~Bigram();

    static void test_function();
  };
}

#endif
