#include <iostream>
#include <chrono>

class SortTester {
 public:
  static long long measureTime(std::vector<int>& arr, void (*sortFunction)(std::vector<int>&, int, int), int left, int right) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(arr, left, right);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }

  static long long measureHybridTime(std::vector<int>& arr, void (*hybridFunction)(std::vector<int>&, int, int, int), int left, int right, int threshold) {
    auto start = std::chrono::high_resolution_clock::now();
    hybridFunction(arr, left, right, threshold);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  }
};
