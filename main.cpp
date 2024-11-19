#include <iostream>
#include <vector>
#include <fstream>
#include "ArrayGenerator.h"
#include "SortTester.h"



void merge(std::vector<int>& arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);
  for (int i = 0; i < n1; i++) L[i] = arr[left + i];
  for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) arr[k++] = L[i++];
    else arr[k++] = R[j++];
  }

  while (i < n1) arr[k++] = L[i++];
  while (j < n2) arr[k++] = R[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
  if (left >= right) return;
  int mid = left + (right - left) / 2;
  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);
  merge(arr, left, mid, right);
}


void insertionSort(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void hybridMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
  if (right - left + 1 <= threshold) {
    insertionSort(arr, left, right);
    return;
  }
  int mid = left + (right - left) / 2;
  hybridMergeSort(arr, left, mid, threshold);
  hybridMergeSort(arr, mid + 1, right, threshold);
  merge(arr, left, mid, right);
}


void standardMergeSort(std::vector<int>& arr, int left, int right) {
  mergeSort(arr, left, right);
}

void hybridMergeInsertionSort(std::vector<int>& arr, int left, int right, int threshold) {
  hybridMergeSort(arr, left, right, threshold); // Гибридный Merge+Insertion Sort
}

int main() {
  ArrayGenerator generator;
  SortTester tester;

  const int minSize = 500;
  const int maxSize = 10000;
  const int stepSize = 100;
  const int threshold = 30;

  std::ofstream outputFile("sorting_results.csv");
  outputFile << "Size,Random_Merge,Random_Hybrid,Reverse_Merge,Reverse_Hybrid,NearlySorted_Merge,NearlySorted_Hybrid\n";

  for (int size = minSize; size <= maxSize; size += stepSize) {
    std::cout << "Testing size: " << size << std::endl;

    std::vector<int> randomArray = generator.generateRandomArray(size);
    std::vector<int> reverseArray = generator.generateReverseSortedArray(size);
    std::vector<int> nearlySortedArray = generator.generateNearlySortedArray(size);

    std::vector<int> randomArrayCopy = randomArray;
    std::vector<int> reverseArrayCopy = reverseArray;
    std::vector<int> nearlySortedArrayCopy = nearlySortedArray;

    long long randomMergeTime = tester.measureTime(randomArray, standardMergeSort, 0, size - 1);
    long long reverseMergeTime = tester.measureTime(reverseArray, standardMergeSort, 0, size - 1);
    long long nearlySortedMergeTime = tester.measureTime(nearlySortedArray, standardMergeSort, 0, size - 1);

    long long randomHybridTime = tester.measureHybridTime(randomArrayCopy, hybridMergeInsertionSort, 0, size - 1, threshold);
    long long reverseHybridTime = tester.measureHybridTime(reverseArrayCopy, hybridMergeInsertionSort, 0, size - 1, threshold);
    long long nearlySortedHybridTime = tester.measureHybridTime(nearlySortedArrayCopy, hybridMergeInsertionSort, 0, size - 1, threshold);

    outputFile << size << ","
               << randomMergeTime << "," << randomHybridTime << ","
               << reverseMergeTime << "," << reverseHybridTime << ","
               << nearlySortedMergeTime << "," << nearlySortedHybridTime << "\n";
  }

  outputFile.close();
  std::cout << "Results saved to sorting_results.csv" << std::endl;

  return 0;
}
