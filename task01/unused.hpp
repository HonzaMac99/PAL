#include <iostream>
#include "data_utils.hpp"
#include "print_utils.hpp"

// these two functions are designed as DFS, but it is useless here

void sort_array(int** in_array, int array_len);
int search_tree(int** data, int* closed, int* town_districts, 
                int search_id, int cur_district, int towns, int roads);
int get_msp_cost(int** data, int* town_districts, int towns, int districts, int roads);


// selection sort (slow)
// TODO: quick/merge/heap sort??
// sort array by the cost of the 3rd element 
void sort_array(int** in_array, int array_len) {
  for(int i = 0; i < array_len; i++) {
    int arr_rest_min = in_array[i][2]; 
    int min_idx = i;
    for(int j = i+1; j < array_len; j++) {
      if (in_array[j][2] < arr_rest_min) {
        arr_rest_min = in_array[j][2];
        min_idx = j;
      }
    }
    if (min_idx != i)
      swap_arrays(in_array[i], in_array[min_idx]);
  }

#if PRINT_INFO
  for(int i = 0; i < array_len; i++) 
    print_ints(in_array[i]);
  std::cout << std::endl;
#endif
}


int search_tree(int** data, int* closed, int* town_districts, 
                int search_id, int cur_district, int towns, int roads) {
  int min_cost = 0;
  int add_min_cost = 0;
  for(int j = 0; j < roads; j++) {
    int town1_id = data[j][0];
    int town2_id = data[j][1];
    int road_cost = data[j][2];
    if(search_id == town1_id or search_id == town2_id) {
      int child_id = (search_id == town1_id) ? town2_id : town1_id;
      if(not closed[child_id] and town_districts[child_id] == cur_district) {
        closed[search_id] = 1;
        std::cout << "(" << child_id << ")";
        add_min_cost = search_tree(data, closed, town_districts, 
                            child_id, cur_district, towns, roads);
        std::cout << " + " << add_min_cost << " + " << road_cost << std::endl; 
        min_cost += add_min_cost; 
        min_cost += road_cost; 
      }
    }
  }
  return min_cost;
}


// construct a minimal spanning tree for each district
int get_msp_cost(int** data, int* town_districts, int towns, int districts, int roads) {
  int min_cost = 0;
  int* closed = new int[towns+1];
  for(int i = 1; i <= districts; i++) {
    int distr_town = i;
    min_cost += search_tree(data, closed, town_districts, distr_town, i, towns, roads);
  }
  return min_cost;
}
