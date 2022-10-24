#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

int* bosses;
int* ranks;
void UF_init(int n);
void UF_union(int rootA, int rootB);
int UF_find(int a); 
void UF_free();

int get_glob_mst_cost(int** data, int* town_districts, int distr_towns, int roads);
int get_mst_cost(int** data, int* town_districts, int towns, int roads);
void process_towns(int **data, int* town_districts, int towns, int districts, int roads);


void UF_init(int n) {
  bosses = new int [n];
  ranks = new int [n];

  for(int i = 0; i < n; i++ ) {
    bosses[i] = i; // everybody's their own boss
    ranks[i] = 0; // initial rank is 0
  }
}

void UF_union( int rootA, int rootB ) {
  if( ranks[rootB] > ranks[rootA] )
    bosses[rootA] = rootB;
  else {
    bosses[rootB] = rootA;
    if( ranks[rootB] == ranks[rootA] ) // change rank?
      ranks[rootA]++;
  }
}

int UF_find(int a) {
  int parent = bosses[a];
  if ( parent != a )
    bosses[a] = UF_find(parent); // path compression
  return bosses[a];
}

void UF_free() {
  delete [] bosses;
  delete [] ranks;
}


// Kruskal's algorithm for global mst (faster)
// get a value of a minimal spanning tree cost on a global scale 
int get_glob_mst_cost(int** data, int* town_districts, int distr_towns, int roads) {

  UF_init(distr_towns+1);
  int min_cost = 0;

  for(int j = 0; j < roads; j++) {
    int town1_distr = town_districts[data[j][0]];
    int town2_distr = town_districts[data[j][1]];
    int road_cost = data[j][2];

    if(town1_distr != town2_distr) {
      int distr1_root = UF_find(town1_distr);
      int distr2_root = UF_find(town2_distr);

      if (distr1_root != distr2_root) {
        UF_union(distr1_root, distr2_root);
        min_cost += road_cost;
      }
    }
  }
  UF_free();

  return min_cost;
}


// Kruskal's algorithm for mst (faster)
// get the sum of a minimal spanning tree cost for each district
int get_mst_cost(int** data, int* town_districts, int towns, int roads) {

  UF_init(towns+1);
  int min_cost = 0;

  for(int j = 0; j < roads; j++) {

    int town1_id = data[j][0];
    int town2_id = data[j][1];
    int road_cost = data[j][2];

    if (town_districts[town1_id] == town_districts[town2_id] 
          and UF_find(town1_id) != UF_find(town2_id)) {
        UF_union(UF_find(town1_id), UF_find(town2_id));
        min_cost += road_cost;
    }
  }
  UF_free();

  return min_cost;
}


// perform BFS on the cities, define their districts 
void process_towns(int **data, int* town_districts, int towns, int districts, int roads) {

  std::queue<int> queue_towns;
  int* queue_ids = zero_array(new int[towns+1], towns+1);
  vector<int>* adjacency_list = new vector<int>[towns+1]; 

  for(int i = 0; i < roads; i++) {
    int town1_id = data[i][0];
    int town2_id = data[i][1];

    adjacency_list[town1_id].push_back(town2_id); 
    adjacency_list[town2_id].push_back(town1_id); 
  }

  for(int i = 1; i <= districts; i++) {
    queue_towns.push(i);
    // std::cout << "push " << i << " to queue_towns" << std::endl;
    town_districts[i] = i;
    queue_ids[i] = 1;
  }
  
  while(not queue_towns.empty()) {
    int exp_town_id = queue_towns.front();
    queue_towns.pop();
    // std::cout << std::endl << "pop " << exp_town_id << " from queue_towns" << std::endl;
    for(int i = 0; i < (int)adjacency_list[exp_town_id].size(); i++) {
      int new_town_id = adjacency_list[exp_town_id][i];

      // check if the town wasn't already in queue
      if (not queue_ids[new_town_id]) {
        town_districts[new_town_id] = town_districts[exp_town_id];
        queue_towns.push(new_town_id);
        queue_ids[new_town_id] = 1;
        // std::cout << "push " << new_town_id << " to queue_towns" << std::endl;
      }
    }
  }
  delete [] queue_ids;
  delete [] adjacency_list;
}
#endif

