#include<string>
#include<vector>

#ifndef _KMP_H_
#define _KMP_H_

class KMP {
 private:
  std::vector<int> lps;

  void computeLPS();
  void KMP_algorithm();
  void initialize();
 protected:
  std::string text;
  std::string pattern;

 public:
  std::vector<int>occurences;
  KMP(std::string text, std::string pattern);
  static void test_function();
  void printMatchingIndices();
};

#endif
