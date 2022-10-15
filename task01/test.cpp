#include <iostream>
#include "data_utils.hpp"

void test_arrays() {
  int len = 4;
  int array1[] = {1, 0, 0, 1};
  int array2[] = {0, 1, 0, 1};

  int* final_array = or_arrays(array1, array2, len);
  for(int i = 0; i < len; i++) {
    std::cout << final_array[i] << " ";
  }
  std::cout << std::endl;
}


int main() {
  test_arrays();
  return 0;
}
