#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include "data_utils.hpp"
#include "print_utils.hpp"

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;

VEC generate_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols);
void gen_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols,
            VEC* base_chain, VEC new_chain, int row_id, int col_id);


VEC operator + (const VEC a, const VEC b) {
    VEC c = a;
    c.insert(c.end(), b.begin(), b.end());
    return c;
}



void gen_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols,
            VEC* base_chain, VEC new_chain, int row_id, int col_id) 
{
  new_chain.push_back(prod_matrix[row_id][col_id]);

  if (row_id == n_rows-1) {
    *base_chain = *base_chain + new_chain;
    return;
  }

  if (col_id == 0) { 
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id+1);
  }
  else if (col_id == n_cols-1) {
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id-1);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id);
  }
  else {
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id-1);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id);
    gen_base_chain(prod_matrix, n_rows, n_cols, base_chain, new_chain, row_id+1, col_id+1);
  }
}


VEC generate_base_chain(VEC_2D prod_matrix, int n_rows, int n_cols) {

  VEC base_chain, new_chain;
  for(int col_id = 0; col_id < n_cols; col_id++) {
    gen_base_chain(prod_matrix, n_rows, n_cols, &base_chain, new_chain, 0, col_id); 
  }
  return base_chain;
}

#define PRINT_INFO 0


#endif

