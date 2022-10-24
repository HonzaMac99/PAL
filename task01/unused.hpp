#include <iostream>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

int get_glob_mst_cost(int** data, int* town_districts, 
                  int towns, int districts, int roads);
int get_mst_cost(int** data, int* town_districts, 
                  int towns, int districts, int roads);
int* process_towns(int **data, int* town_districts, int* town_distances,
                   int towns, int districts, int roads);
void swap_arrays(int* array1, int* array2);
void sort_array(int** in_array, int array_len);


// Jarnik's algorithm for global mst (slow)
// get a value of a minimal spanning tree cost on a global scale 
int get_glob_mst_cost(int** data, int* town_districts, int towns, 
                    int districts, int roads) {

  int* connected_distrs = zero_array(new int[districts+1], districts+1);
  connected_distrs[1] = 1;
  int towns_to_expand = 1;
  int min_cost = 0;
  while(towns_to_expand > 0) {
    towns_to_expand = 0;
    for(int j = 0; j < roads; j++) {
      int town1_id = data[j][0];
      int town1_distr = town_districts[town1_id];
      int town2_id = data[j][1];
      int town2_distr = town_districts[town2_id];
      int road_cost = data[j][2];
      
      if(connected_distrs[town1_distr] xor connected_distrs[town2_distr]) 
      {
        int new_district = (connected_distrs[town1_distr]) 
                              ? town2_distr : town1_distr;
        connected_distrs[new_district] = 1;
        min_cost += road_cost;
      #if PRINT_INFO 
        print_ints(data[j]);
        std::cout << "connecting " << town1_distr <<
                           " and " << town2_distr;
        std::cout << " --> new: " << new_district << std::endl;
      #endif
        towns_to_expand++;
        break;
      }
    }
  }
  delete [] connected_distrs; 

  return min_cost;
}


// Jarnik's algorithm for mst (slow)
// get the sum of a minimal spanning tree cost for each district
int get_mst_cost(int** data, int* town_districts, int towns, 
                    int districts, int roads) {
  int min_cost = 0;
  int towns_to_expand;
  int* frontier = new int[towns+1];

  for(int i = 1; i <= districts; i++) {
    // std::cout << "District " << i << ":" << std::endl;
    frontier = zero_array(frontier, towns+1);
    frontier[i] = 1;
    towns_to_expand = 1;

    // e.k. run until there in no town added in the new_frontiers
    while (towns_to_expand > 0) {
      towns_to_expand = 0;
      for(int j = 0; j < roads; j++) {

        int town1_id = data[j][0];
        int town2_id = data[j][1];
        int road_cost = data[j][2];

        if(frontier[town1_id] xor frontier[town2_id]) 
        {
          int new_town_id = (frontier[town1_id]) ? town2_id : town1_id;
          if(town_districts[new_town_id] == i) 
          {
            frontier[new_town_id] = 1;
            min_cost += road_cost;
            towns_to_expand++;
            break;
          }
        }
      }
    }
  }
  delete [] frontier;

  return min_cost;
}


// perform BFS on the cities, define districts 
// and their distances to their district towns
// return indexes of edges between the districts
int* process_towns(int **data, int* town_districts, int* town_distances,
                   int towns, int districts, int roads) {

  int frontier_dist, towns_to_expand;
  int* closed = new int[towns+1];
  int* last_frontier = new int[towns+1];
  int* new_frontier = new int[towns+1];
  int* distr_edges = new int[roads];

  for(int i = 1; i <= districts; i++) {
    // std::cout << "District " << i << ":" << std::endl;
    town_districts[i] = i;

    closed = zero_array(closed, towns+1);
    last_frontier = zero_array(last_frontier, towns+1);
    new_frontier = zero_array(new_frontier, towns+1);

    frontier_dist = 1; 
    last_frontier[i] = 1;
    towns_to_expand = 1;

    // e.k. run until there in no town added in the new_frontiers
    while (towns_to_expand > 0) {
      towns_to_expand = 0;
      for(int j = 0; j < roads; j++) {
        int town1_id = data[j][0];
        int town2_id = data[j][1];
      #if PRINT_INFO
        std::cout << town1_id << " "
                  << town2_id << " " 
                  << data[j][2] << " (" << j << ") ";
      #endif
        // is one of the towns in frontier?
        // is the edge connected to the tree?
        if(last_frontier[town1_id] xor last_frontier[town2_id]) {
          int new_town_id = (last_frontier[town1_id]) ? town2_id : town1_id;
          if(not closed[new_town_id] and new_town_id > districts and
            (town_distances[new_town_id] == 0 or 
              frontier_dist < town_distances[new_town_id])) {

            town_distances[new_town_id] = frontier_dist;
            town_districts[new_town_id] = i;
            // std::cout << "--> Town " << new_town_id << " is now in " << i << " ";
            new_frontier[new_town_id] = 1;
            // std::cout << "Adding " << new_town_id << std::endl;
            towns_to_expand++;
          }
          if(town_districts[town1_id] != town_districts[town2_id]) {
            distr_edges[j] = 1;
            // std::cout << "--> Add " << j 
            //   << " because " << town_districts[town1_id] << 
            //           " != " << town_districts[town2_id];
          } else {
            distr_edges[j] = 0;
            // std::cout << "--> Del " << j 
            //   << " because " << town_districts[town1_id] << 
            //           " == " << town_districts[town2_id];
          }
        }
        // std::cout << std::endl;
      }
      // print_frontier(new_frontier, towns, frontier_dist, towns_to_expand);

      or_arrays(closed, last_frontier, towns+1);
      delete [] last_frontier;
      last_frontier = copy_array(new_frontier, towns+1);
      new_frontier = zero_array(new_frontier, towns+1);
      frontier_dist++;
    }
  }
  delete [] closed;
  delete [] last_frontier;
  delete [] new_frontier;

  return distr_edges;
}


// quick sort from data_utils:

void swap_arrays(int* array1, int* array2) {
  int tmp;
  for(int i = 0; i < 3; i++) {
    tmp = array1[i];
    array1[i] = array2[i];
    array2[i] = tmp;
  }
}

// part in the quick sort algorithm
int partition(int** arr, int start, int end)
{
 
    int pivot = arr[start][2];
 
    int count_var = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i][2] <= pivot)
            count_var++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count_var;
    swap_arrays(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i][2] <= pivot) {
            i++;
        }
 
        while (arr[j][2] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap_arrays(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 

// quick sort (fast)
void quickSort(int** arr, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);

    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);

#if DATA_INFO
    for(int i = 0; i < end; i++) 
        print_ints(arr[i]);
    std::cout << std::endl;
#endif
}
