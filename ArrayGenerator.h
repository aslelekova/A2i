#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class ArrayGenerator {
 private:
  std::mt19937 rng;

 public:
  ArrayGenerator() {
    rng.seed(std::random_device()());
  }

  std::vector<int> generateRandomArray(int size, int minVal = 0, int maxVal = 6000) {
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    std::vector<int> arr(size);
    for (int& val : arr) {
      val = dist(rng);
    }
    return arr;
  }

  std::vector<int> generateReverseSortedArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
      arr[i] = size - i;
    }
    return arr;
  }

  std::vector<int> generateNearlySortedArray(int size, int swaps = 10) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
      arr[i] = i;
    }
    for (int i = 0; i < swaps; ++i) {
      int idx1 = rng() % size;
      int idx2 = rng() % size;
      std::swap(arr[idx1], arr[idx2]);
    }
    return arr;
  }
};
