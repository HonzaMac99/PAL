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
  
  std::cout << "b_chain_len: " << base_chain.size() 
            << " d_chain_len: " << desr_chain.size() << std::endl;
  std::vector<tree_node> clip_tree = get_clip_tree(clip_schemes);
#if PRINT
  print_clip_tree(clip_tree);
#endif

  int start_pos, end_pos, cost;

  find_best_chain(base_chain, desr_chain, clip_tree, 
                clip_factor, replace_factor,
                &start_pos, &end_pos, &cost);

  int b_ch_len = end_pos - start_pos + 1; 
  
  std::cout << start_pos << " " << b_ch_len << " " << cost << std::endl;

  return 0;
}
