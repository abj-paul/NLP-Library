
#ifndef _SPELLING_CORRECTION_H_
#define _SPELLING_CORRECTION_H_

#include "../NoisyChannelModel/NoisyChannelModel.h"
#include "../NoisyChannelModel/MED.h"
#include "../LanguageModel/Bigram.h"
#include "../LanguageModel/PrecomputeNGram.h"
#include<vector>
#include "../Data-Structures/lib_string.h"
/* #include "PriorityQueue.h" */
#include "Candidate.cpp"

namespace abj {
class SpellingCorrection {
 private:
  abj::Bigram* bigram;
  abj::String givenWord;
  abj::String previousWord;
  std::vector<abj::Candidate> candidateList;
  const char* CANDIDATE_LIST_FILE = "candidates.txt";
  abj::String filename;
  
  void prepareModel();
  void clearCandidateList();
  void generateCandidateList();
 public:
  SpellingCorrection(const abj::String& filename);
  ~SpellingCorrection();

  void setStem(const abj::String& newStem, const abj::String& previousStem);
  void printCandidateList();

  static void test_function();
};
}


#endif

