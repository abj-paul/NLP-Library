#include<iostream>
#include<vector>
#include "./Data-Structures/lib_string.h"
#include "./Data-Structures/BinarySearchTree.h"
#include "./Preprocess-data/lib_punctuation.h"
#include "./Preprocess-data/SentenceSegmenter.h"
#include "./Preprocess-data/Tokenizer.h"
#include "./Preprocess-data/Stemmer.h"
#include "./LanguageModel/Bigram.h"
#include "./Data-Structures/OrderedSet.h"
#include "./LanguageModel/PrecomputeNGram.h"
#include "./LanguageModel/NGram.h"

#include "./NoisyChannelModel/ConfusionMatrix.h"
#include "./NoisyChannelModel/MED.h"
#include "./NoisyChannelModel/KMP.h"
#include "./NoisyChannelModel/DefineNoisyChannel.h"
#include "./NoisyChannelModel/NoisyChannelModel.h"

#include "./Evaluation/Evaluation.h"
#include "./KneeserNey/KneeserNey.h"

#include "./Spelling-Correction/SpellingCorrection.h"


int main(){
  // abj::String::test_function();
  // abj::Punctuation::test_function();
  // abj::BinarySearchTree::test_function();
  // abj::SentenceSegmenter::test_function();
  // abj::Tokenizer::test_function();
  // abj::Stemmer::test_function();
  // abj::Bigram::test_function();
  // set_test_function();
  // abj::PrecomputeNGram::test_function();
  // abj::NGram::test_function();
  abj::NoisyChannelModel::test_function();
  abj::Evaluation::test_function();
  // abj::KneeserNey::test_function();

  // abj::SpellingCorrection::test_function();
  return 0;
}

