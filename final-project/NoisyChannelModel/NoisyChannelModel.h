
#ifndef _NOISY_CHANNEL_MODEL_H
#define _NOISY_CHANNEL_MODEL_H

#include "ConfusionMatrix.h"
#include "MED.h"
#include "KMP.h"
#include "../Data-Structures/lib_string.h"
#include<string>
#include<fstream>
#include<cmath>

namespace abj {
class NoisyChannelModel : public ConfusionMatrix {
 private:
  abj::String filename;
  abj::String correction;
  abj::String typo;
  abj::String fileText;
  double total_probablity;

  void backtrace_noisy_path(int i, int j, int direction[][MAX_WORD_SIZE]);
  void loadSpellingFile();

  int substringCount(char a);
  int substringCount(char a, char b);

  double normalize(double log_value);
  
 public:
  NoisyChannelModel(abj::String& mainWord, abj::String& newWord);
  ~NoisyChannelModel();
  double getProbablity();
  double getNormalizedProbablity();
  static void test_function();
};
}

#endif
