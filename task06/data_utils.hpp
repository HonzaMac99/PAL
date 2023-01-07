#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include "print_utils.hpp"

#define DATA_INFO 1 

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;

VEC_2D get_prod_matrix(int n_rows, int n_cols);
VEC_2D get_clip_schemes(int n_clips);


VEC_2D get_prod_matrix(int n_rows, int n_cols) {
  VEC_2D prod_matrix;
  char new_link;
  int new_link_len;
  for(int i = 0; i < n_rows; i++) {
    VEC prod_row; 
    for(int j = 0; j < n_cols; j++) {
      std::cin >> new_link;
      new_link_len = new_link - 'a' + 1;
      prod_row.push_back(new_link_len);
    }
    prod_matrix.push_back(prod_row);
  }
#if DATA_INFO
  for(int i = 0; i < n_rows; i++) {
    for(int j = 0; j < n_cols; j++) {
      std::cout << prod_matrix[i][j] << " ";
    } 
    std::cout << std::endl;
  }
  std::cout << std::endl;
#endif
  return prod_matrix; 
}

VEC get_desr_chain(int desr_chain_len) {
  VEC desr_chain;
  char new_link;
  int new_link_len;
  for(int i = 0; i < desr_chain_len; i++) {
    std::cin >> new_link;
    new_link_len = new_link - 'a' + 1;
    desr_chain.push_back(new_link_len);
  }
#if DATA_INFO
  for(int i = 0; i < desr_chain_len; i++) {
    std::cout << desr_chain[i] << " ";
  }
  std::cout << std::endl << std::endl;
#endif
  return desr_chain;
}

VEC_2D get_clip_schemes(int n_clips) {
  VEC_2D clip_schemes;
  char new_link;
  int new_link_len;
  std::string clip_scheme_str;
  for(int i = 0; i < n_clips; i++) {
    VEC clip_scheme; 
    std::cin >> clip_scheme_str; 
    for(int j = 0; j < clip_scheme_str.size(); j++) {
      new_link = clip_scheme_str[j];
      new_link_len = new_link - 'a' + 1; 
      clip_scheme.push_back(new_link_len);
      std::cout << new_link_len << " ";
    }
    clip_schemes.push_back(clip_scheme);
    std::cout << std::endl;
  }
  return clip_schemes;
}
#endif

