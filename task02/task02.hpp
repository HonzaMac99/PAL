#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

void process_crosses(int** data, vector<int>* out_streets, 
                                  vector<int>* in_streets, int n_streets);


// contruct an adjacency list from the streets
void process_crosses(int** data, vector<int>* out_streets, 
                                  vector<int>* in_streets, int n_streets) {

  for(int i = 0; i < n_streets; i++) {
    int cross1_id = data[i][0];
    int cross2_id = data[i][1];

    out_streets[cross1_id].push_back(cross2_id); 
    in_streets[cross2_id].push_back(cross1_id); 
  }
}

#endif

