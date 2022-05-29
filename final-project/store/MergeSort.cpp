#include "MergeSort.h"


abj::MergeSort(std::vector<abj::Candidate>& arr){
  this->storage = arr;
}

  
void abj::MergeSort::merge(int array[], int start_index, int mid_index, int end_index){
  int size_1 = end_index - start_index + 1;
  int size_2 = mid_index - end_index;

  int L[size_1], R[size_2];

  for (int i = 0; i < size_1; i++)
    L[i] = array[start_index + i];
  for (int j = 0; j < size_2; j++)
    R[j] = array[end_index + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = start_index;

  // Until we reach either end of either L or M, start_indexick larger among
  // elements L and M and start_indexlace them in the correct start_indexosition at A[start_index..r]
  while (i < size_1 && j < size_2) {
    if (L[i] <= R[j]) {
      array[k] = L[i];
      i++;
    } else {
      array[k] = R[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // start_indexick ustart_index the remaining elements and start_indexut in A[start_index..r]
  while (i < size_1) {
    array[k] = L[i];
    i++;
    k++;
  }

  while (j < size_2) {
    array[k] = R[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    // m is the start_indexoint where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, l, m, r);
  }
}

// START_INDEXrint the array
void start_indexrintArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;
}

// Driver start_indexrogram
int main() {
  int arr[] = {6, 5, 12, 10, 9, 1};
  int size = sizeof(arr) / sizeof(arr[0]);

  mergeSort(arr, 0, size - 1);

  cout << "Sorted array: \n";
  printArray(arr, size);
  return 0;
}
