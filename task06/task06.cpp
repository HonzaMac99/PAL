#include <iostream>
#include "task06.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT 0

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;


int main()
{
  // Do './task06 < ../datapub/pub01.in' for reading files using stdin
  // No need for implementing reading from file in this program 
  
  int n_rows, n_cols, desr_chain_len, n_clips, clip_factor, replace_factor;

  std::cin >> n_rows >> n_cols >> desr_chain_len >> n_clips 
           >> clip_factor >> replace_factor;
  VEC_2D prod_matrix = get_prod_matrix(n_rows, n_cols);
  VEC desr_chain = get_desr_chain(desr_chain_len);
  VEC_2D clip_schemes = get_clip_schemes(n_clips);

  VEC base_chain = generate_base_chain(prod_matrix, n_rows, n_cols);
  int chain_len = base_chain.size(); 

  //for(int i = 0; i < base_chain.size(); i++) {
  //  std::cout << base_chain[i] << " ";
  //}
  //std::cout << std::endl << std::endl;;


  return 0;
}
