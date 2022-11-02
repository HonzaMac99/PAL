#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
#include "data_utils.hpp"
#include "print_utils.hpp"
#include "node.hpp"

#define VEC_2D vector<vector<int>>
#define VEC_P vector<int>*
#define V vertices[node_id]
#define W vertices[succ_id]

#define PRINT_INFO 0


void process_crosses(int** data, Node* vertices, int n_streets); 
void find_scc(Node* vertices, VEC_P out_streets, t_stack* my_stack, int node_id, 
                int* index, int* n_scc, VEC_2D scc_vec);
VEC_2D get_all_scc(Node* vertices, VEC_P out_streets, int n_crossings);
int get_min_trail(vector<int>scc_ids, VEC_P out_streets, 
                    int cross1_id, int cross2_id, int n_crosses);
void get_best_cross(vector<int> scc_ids, VEC_P out_streets, int n_crossings, 
                    int* p_crossings, int* min_cost);
void get_prosp_cross(VEC_2D strong_components, VEC_P out_streets, int n_crossings,
                      int* p_crossings, int* max_var, int* min_cost);

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


void find_scc(Node* vertices, VEC_P out_streets, t_stack* my_stack, int node_id, 
                int* index, int* n_scc, VEC_2D scc_vec) {
  V.index = V.lowlink =(*index)++;
  
  my_stack->push_node(V.id);
  V.instack = true;
  
  for(int j = 0; j < (int)out_streets[V.id].size(); j++) { 

    int succ_id = out_streets[V.id][j]; 

    if (W.index == 0) { // not yet visited
      find_scc(vertices, out_streets, my_stack, W.id, index, n_scc, scc_vec);
      V.lowlink = min(V.lowlink, W.lowlink);
    }
    else if (W.instack) { 
      V.lowlink = min(V.lowlink, W.index);
    } 
  } 

  
  std::cout << V.id << std::endl;
  std::cout << V.index << std::endl;
  std::cout << V.lowlink << std::endl;
  break_point();

  if (V.lowlink == V.index) { // v: head of SCC
    (*n_scc)++; // track how many SCCs found
    vector<int> new_scc;
    int stack_top_id = my_stack->pop_node();
    std::cout << stack_top_id << " " << V.id << std::endl;
    break_point();
    
    while(stack_top_id != V.id) {
      stack_top_id = my_stack->pop_node();
      std::cout << stack_top_id << " " << V.id << std::endl;
      break_point();
      vertices[stack_top_id].instack = false;

      new_scc.push_back(stack_top_id);
    }
    scc_vec.push_back(new_scc);
  }
}


// tarjan's algorithm for getting the strong components of the graph
VEC_2D get_all_scc(Node* vertices, VEC_P out_streets, int n_crossings) 
{
  vector<vector<int>> scc_vector;
  t_stack my_stack;

  int index = 1; // unique node number > 0
  int n_scc = 0; // number of SCCs in G

  for(int i = 0; i < n_crossings; i++) {
    if (vertices[i].index == 0) { // yet unvisited
      find_scc(vertices, out_streets, &my_stack, i, &index, &n_scc, scc_vector);   
    }
  }
  return scc_vector;
}

int get_min_trail(vector<int>scc_ids, VEC_P out_streets, 
                    int cross1_id, int cross2_id, int n_crosses) {
  int scc_size = scc_ids.size();
  int trail_len = 0;
  int last_front_id = cross1_id;
  std::queue<int> queue_crosses;
  int* queue_ids = zero_array(new int[scc_size], scc_size);
  queue_crosses.push(cross1_id);

  while(not queue_crosses.empty()) {
    int exp_cross_id = queue_crosses.front();
    queue_crosses.pop();

    if (exp_cross_id == last_front_id) {
      last_front_id = queue_crosses.back();
      trail_len++;
    }

    for(int i = 0; i < (int)out_streets[exp_cross_id].size(); i++) {
      int new_cross_id = out_streets[exp_cross_id][i];

      // check if the cross wasn't already in queue
      if (not queue_ids[new_cross_id]) {
        queue_crosses.push(new_cross_id);
        queue_ids[new_cross_id] = 1;
        // std::cout << "push " << new_cross_id << " to queue_crosses" << std::endl;
      }
    }
  }
  
}

void get_best_cross(vector<int> scc_ids, VEC_P out_streets, int n_crossings, 
                    int* p_crossings, int* min_cost) {
  for(int i = 0; i < (int)scc_ids.size(); i++) {
    int cross_cost = 0;
    for(int j = 0; j < (int)out_streets[i].size(); j++) {
      cross_cost += 2*get_min_trail(scc_ids, out_streets, n_crossings, i, j); 
      cross_cost += get_min_trail(scc_ids, out_streets, n_crossings, j, i);
    }
    if(cross_cost < *min_cost) {
      *min_cost = cross_cost;
      *p_crossings = 1;
    }
    else if (cross_cost == *min_cost) {
      (*p_crossings)++; 
    }
  }
}


void get_prosp_cross(VEC_2D strong_components, VEC_P out_streets, int n_crossings,
                      int* p_crossings, int* max_var, int* min_cost) {
  
  vector<int> best_indexes;
  
  for(int i = 0; i < (int)strong_components.size(); i++) {
    int scc_size = (int)strong_components[i].size();
    if(scc_size > *max_var) {
      *max_var = scc_size;
      best_indexes.clear();
    } else if (scc_size == *max_var) {
      best_indexes.push_back(i);
    }
  }

  for(int i = 0; i < (int)best_indexes.size(); i++) {
    get_best_cross(strong_components[i], out_streets, n_crossings, 
                                                p_crossings, min_cost);  
  }
}
#endif

