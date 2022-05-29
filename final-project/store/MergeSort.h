#include<vector>

#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

#include "Candidate.cpp"

namespace abj{
class MergeSort{
 private:
  void merge(int array[], int start_index, int mid_index, int end_index);
  
 public:
  std::vector<abj::Candidate> storage;

  MergeSort(std::vector<abj::Candidate>& arr);
  void sort();
};

}
#endif
