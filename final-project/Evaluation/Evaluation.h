#include<iostream>
#include<vector>
#include<cmath>


#ifndef _EVALUATION_H_
#define _EVALUATION_H_

#include "../Data-Structures/lib_string.h"
#include "../Preprocess-data/SentenceSegmenter.h"
#include "../LanguageModel/NGram.h"

namespace abj{
class Evaluation{
 private:
  double perplexity;
  const char* TEST_FILE_NAME="./Resources/test-split.txt";
  const char* TRAIN_FILE_NAME="./Resources/train-split.txt";

  std::vector<abj::String> getSentenceList(abj::String& text);
  abj::String& extract_content_from_file(const abj::String& filename);
  
 public:
  Evaluation();
  ~Evaluation();
  void splitIntoTrainAndTestDataset(abj::String& filename, double testRatio, double trainRatio); // in percentage
  double measurePerplexity();

  static void test_function();
};
}


#endif
