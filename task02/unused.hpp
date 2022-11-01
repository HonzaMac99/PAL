#include <iostream>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define VEC_2D vector<vector<int>>
#define VEC_P vector<int>*

void process_crosses(int** data, VEC_P out_streets, VEC_P in_streets, int n_streets);



// // adjacency lists for children and parents of the nodes
// vector<int>* out_streets = new vector<int>[n_crossings]; 
// vector<int>* in_streets = new vector<int>[n_crossings]; 
 
// print_adj_list(out_streets, n_crossings);
// print_adj_list(in_streets, n_crossings);


// contruct an adjacency list from the streets
void process_crosses(int** data, VEC_P out_streets, VEC_P in_streets, int n_streets) 
{

  for(int i = 0; i < n_streets; i++) 
  {
    int cross1_id = data[i][0];
    int cross2_id = data[i][1];

    out_streets[cross1_id].push_back(cross2_id); 
    in_streets[cross2_id].push_back(cross1_id); 
  }
}

