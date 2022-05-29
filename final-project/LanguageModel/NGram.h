

#ifndef _N_GRAM_H_
#define _N_GRAM_H_

#include "../Data-Structures/OrderedSet.h"
#include<vector>
#include "../Data-Structures/lib_string.h"
#include "../LanguageModel/PrecomputeNGram.h"

namespace abj{
class NGram {
private:
  int ngram;
  abj::Set<std::vector<abj::String>> ngram_packet_set;
  abj::Set<std::vector<abj::String>> nMinusOnegram_packet_set;
  abj::String corpusFileName;

  double probablity(double totalCount, char separator, double previousCount);

  FILE* debug_fptr;
  const char* debugFileName = "./Debug-Log-Files/ngram.txt";

  // Formats
  double no_smoothing_probablity(double totalCount, char separator, double previousCount);
  double laplace_smoothing_probablity(double totalCount, char separator, double previousCount);

public:
  NGram(int ngram, const abj::String& corpusFileName);
  ~NGram();
  double probablity_sentence(const abj::String& text);
  int getNGramSize();

  static void test_function();
  // static void terminal_user_interface();

  static double normalize(double log_probablity, int textSize);
};
}


#endif
