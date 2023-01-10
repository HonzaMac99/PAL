#include <iostream>
#include <vector>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

int compute_chain_len(int n_rows, int n_cols) {
  if(n_cols == 1)
    return n_rows;

  int chain_len = 0;
  std::vector<int> n_paths(n_cols, 1);
  std::vector<int> new_n_paths(n_cols);

  std::cout << std::endl;
  for(int i = 0; i < n_rows-1; i++) {
    for(int j = 0; j < n_cols; j++) {
      if(j == 0) 
        new_n_paths[j] = n_paths[j] + n_paths[j+1];
      else if(j == n_cols-1)
        new_n_paths[j] = n_paths[j-1] + n_paths[j];
      else
        new_n_paths[j] = n_paths[j-1] + n_paths[j] + n_paths[j+1];
    }
    n_paths = new_n_paths;

    for(int j = 0; j < n_cols; j++) {
      std::cout << new_n_paths[j] << " ";
    }
    std::cout << std::endl;
  }
  
  for(int &element : n_paths)
    chain_len += element;
  chain_len *= n_rows;
  return chain_len;
}
