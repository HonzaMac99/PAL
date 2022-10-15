#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
//#include <unistd.h>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define MAX_T 250000
#define MAX_D 2000
#define MAX_R 450000

#define EDGE_COST_MIN 1
#define EDGE_COST_MAX 250 

#define PRINT_INFO 0 

// perform BFS on the cities, define districts 
// and their distances to their district towns
void set_town_info(int **data, int* town_districts, int* town_distances,
                   int towns, int districts, int roads) {

  int frontier_dist, towns_to_expand;
  int* closed = new int[towns+1];
  int* last_frontier = new int[towns+1];
  int* new_frontier = new int[towns+1];

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
        // is one of the towns in frontier?
        if(last_frontier[town1_id] xor last_frontier[town2_id]) {
          int new_town_id = (last_frontier[town1_id]) ? town2_id : town1_id;
          if(not closed[new_town_id] and new_town_id > districts and
            (town_distances[new_town_id] == 0 or frontier_dist < town_distances[new_town_id])) {

            town_distances[new_town_id] = frontier_dist;
            town_districts[new_town_id] = i;
            new_frontier[new_town_id] = 1;
            // std::cout << "Adding " << new_town_id << std::endl;
            towns_to_expand++;
          }
        }
      }
      print_frontier(new_frontier, towns, frontier_dist, towns_to_expand);

      closed = or_arrays(closed, last_frontier, towns+1);
      last_frontier = copy_array(new_frontier, towns+1);
      new_frontier = zero_array(new_frontier, towns+1);
      frontier_dist++;
      // usleep(200000);
    }
  }
  delete [] closed;
  delete [] last_frontier;
  delete [] new_frontier;
}
#endif
