#include<iostream>
#include<vector>
#include<tgmath.h>

#ifndef _PRECOMPUTE_NGRAM_H_
#define _PRECOMPUTE_NGRAM_H_
#include "../Data-Structures/OrderedSet.h"
#include "../Data-Structures/lib_string.h"
#include "../Preprocess-data/SentenceSegmenter.h"
#include "../Preprocess-data/lib_punctuation.h"
#include "../Preprocess-data/Tokenizer.h"
#include "../Preprocess-data/Stemmer.h"



namespace abj{
  class PrecomputeNGram{
  private:
    int nGram;
    abj::String corpusFileName;
    const char* debugFileName = "./Debug-Log-Files/precompute_NGram.txt";
    abj::Set<std::vector<abj::String>> ngram_packet_set;

  public:
    PrecomputeNGram(int nGram, const abj::String& corpus_fileName);
    ~PrecomputeNGram();

    [[nodiscard]] static abj::String getFileData(const abj::String& filename);
    [[nodiscard]] static std::vector<abj::String> getStemList(const abj::String& text);
    void build_ngram();
    // void save_ngram(const abj::String& filename);
    // Auxiliary
    void print_ngram();

    [[nodiscard]] abj::Set<std::vector<abj::String>>& get_ngram_packet_set();
    static void test_function();
  };
}

#endif
