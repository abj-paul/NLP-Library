
#ifndef _NOISY_CHANNEL_MODEL_H
#define _NOISY_CHANNEL_MODEL_H

#include "ConfusionMatrix.h"
#include "MED.h"
#include "KMP.h"
#include "../lib_string.h"
#include<string>
#include<fstream>
#include<cmath>

namespace abj {
class NoisyChannelModel : public ConfusionMatrix {
 private:
  abj::String filename;
  abj::String mainWord;
  abj::String newWord;
  abj::String fileText;
  double total_probablity;

  void backtrace_noisy_path(int i, int j, int direction[][MAX_WORD_SIZE]);
  void loadSpellingFile();

  int substringCount(char a);
  int substringCount(char a, char b);
  
 public:
  NoisyChannelModel(abj::String& mainWord, abj::String& newWord);
  double getProbablity();
};
}

#endif
