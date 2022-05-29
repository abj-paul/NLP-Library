
#ifndef _SETENCE_SEGMENTATION_H
#define _SETENCE_SEGMENTATION_H

#include "lib_punctuation.h"
#include "../Data-Structures/BinarySearchTree.h"
#define MIN_SENTENCE_SIZE 10
namespace abj{
  class SentenceSegmenter {
  public:

    SentenceSegmenter(abj::String corpus);
    SentenceSegmenter();
    ~SentenceSegmenter();

    void setCorpus(abj::String corpus);

    abj::String make_word(int start_index, int end_index);
    void use_decision_tree();
    void print();
    static void test_function();
    void printAbbreviationsForDebug();
    std::vector<abj::String>& getSentenceList();
  private:
    abj::String corpus; // str
    abj::Punctuation punctuation;
    const char* ABBREVIATION_FILE_NAME = "./Resources/formatted-daily-chat-shortcuts.txt";
    const char* DEBUG_FILENAME = "./Debug-Log-Files/sentence_segmenter.txt";
    const char* ABBREVIATION_CSR_FILE_NAME = "./Resources/formatted-CSR-acronym-list.txt";
    BinarySearchTree abbreviations;
    std::vector<abj::String>sentence_list;
    
    bool decision_tree(int i);
    bool lots_of_space_after_it(int i);
    bool isAbbreviation(abj::String str, int i);
    void print_sentence(int start_index, int i);
    abj::String make_sentence(int start_index, int i);
    void buildAbbreviationList();
  };
}

#endif
