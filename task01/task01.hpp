#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include "data_utils.hpp"
#include "print_utils.hpp"
#include "node.hpp"


int search_tree(int** data, int* closed, int* town_districts, 
                int search_id, int cur_district, int towns, int roads);
int get_msp_cost(int** data, int* town_districts, int towns, int districts, int roads);
int* set_town_info(int **data, int* town_districts, int* town_distances,
                   int towns, int districts, int roads);


int search_tree(int** data, int* closed, int* town_districts, 
                int search_id, int cur_district, int towns, int roads) {
  int min_cost = 0;
  for(int j = 0; j < roads; j++) {
    int town1_id = data[j][0];
    int town2_id = data[j][1];
    int road_cost = data[j][2];
    if(search_id == town1_id or search_id == town2_id) {
      int child_id = (search_id == town1_id) ? town2_id : town1_id;
      if(not closed[child_id] and town_districts[child_id] == cur_district) {
        closed[search_id] = 1;
        min_cost += search_tree(data, closed, town_districts, child_id, cur_district, towns, roads);
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
    std::cout << "District " << i << ":" << std::endl;
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
        std::cout << town1_id << " " << town2_id << " " << data[j][2] << " (" << j << ") ";
        // is one of the towns in frontier?
        // is the edge connected to the tree?
        if(last_frontier[town1_id] xor last_frontier[town2_id]) {
          int new_town_id = (last_frontier[town1_id]) ? town2_id : town1_id;
          if(not closed[new_town_id] and new_town_id > districts and
            (town_distances[new_town_id] == 0 or 
              frontier_dist < town_distances[new_town_id])) {

            town_distances[new_town_id] = frontier_dist;
            town_districts[new_town_id] = i;
            std::cout << "--> Town " << new_town_id << " is now in " << i << " ";
            new_frontier[new_town_id] = 1;
            // std::cout << "Adding " << new_town_id << std::endl;
            towns_to_expand++;
          }
          if(town_districts[town1_id] != town_districts[town2_id]) {
            distr_edges[j] = 1;
            std::cout << "--> Add " << j 
              << " because " << town_districts[town1_id] << 
                      " != " << town_districts[town2_id];
          } else {
            distr_edges[j] = 0;
            std::cout << "--> Del " << j 
              << " because " << town_districts[town1_id] << 
                      " == " << town_districts[town2_id];
          }
        }
        std::cout << std::endl;
      }
      // print_frontier(new_frontier, towns, frontier_dist, towns_to_expand);

      closed = or_arrays(closed, last_frontier, towns+1);
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
#endif
