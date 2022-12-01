#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
#include "data_utils.hpp"
#include "print_utils.hpp"
#include "node.hpp"

#define VEC vector<int>
#define VEC_2D vector<vector<int>>

#define V vertices[node_id]
#define W vertices[succ_id]
#define X vertices[stack_top_id]

#define PRINT_INFO 0
#define PRINT_INFO_2 0


void process_crosses(int** data, VEC* out_streets, int n_streets); 
void find_scc(Node* vertices, VEC* out_streets, t_stack* my_stack, int node_id, 
                int* index, int* n_scc, VEC_2D* scc_vec);
VEC_2D get_all_scc(Node* vertices, VEC* out_streets, int n_crossings);
void refine_scc(Node* vertices, VEC* out_streets, VEC* new_out_streets, t_stack* my_stack, 
                  int node_id, int* index, int* n_scc, VEC_2D* scc_vec, VEC old_scc_ids);
VEC_2D refine_all_scc(Node* vertices, VEC* out_streets, VEC* new_out_streets, VEC_2D* old_scc_ids);
int* get_min_trails(VEC* out_streets, int n_crosses, int max_var, VEC scc_ids, int c_id);
void get_best_cross(vector<int> scc_ids, VEC* out_streets, int n_crossings, 
                    int* p_crossings, int max_var, int* min_cost);
void get_prosp_cross(VEC_2D strong_components, VEC* out_streets, int n_crossings,
                      int* p_crossings, int* max_var, int* min_cost);


// contruct an adjacency list from the streets
void process_crosses(int** data, VEC* out_streets, int n_streets) 
{
  for(int i = 0; i < n_streets; i++) {
    int cross1_id = data[i][0];
    int cross2_id = data[i][1];

    out_streets[cross1_id].push_back(cross2_id);
  }
}

//------------------------------------------------------------------------------------

void find_scc(Node* vertices, VEC* out_streets, t_stack* my_stack, int node_id, 
                int* index, int* n_scc, VEC_2D* scc_vec) 
{
  // V ... expanding crossing with its properties -> V = vertices[node_id]
  // W ... its successors with their properties -> W = vertices[succ_id]
  // X ... crossing poped from the stack -> X = vertices[stack_top_id]
 
  V.index = V.lowlink = (*index)++;
  
  my_stack->push_node(V.id);
  V.instack = true;
  
  for(int j = 0; j < (int)out_streets[V.id].size(); j++) { 

    int succ_id = out_streets[V.id][j];  // index for W

    if (W.index == 0) // W not yet visited
    {
#if PRINT_INFO 
      print_v(V, "---->");
      break_point();
#endif
      find_scc(vertices, out_streets, my_stack, W.id, index, n_scc, scc_vec);
      // std::cout << W.id << " closed? " << W.closed << std::endl;
      // break_point();

      if (W.closed) // W became closed after return from recursion -> V is weak:w
      {         
        V.weak = true;
        // std::cout << "WEAK_B: " << V.id << std::endl;
        // break_point();
      } 
      else {
        V.lowlink = min(V.lowlink, W.lowlink);
      } 
    }
    else if (W.instack) {
      V.lowlink = min(V.lowlink, W.index);
    } 
    else if (W.closed) // W is already closed and is part of another scc -> V is weak
    {
      V.weak = true;
      // std::cout << "WEAK_A: " << V.id << std::endl;
      // break_point();
    }
  } 

#if PRINT_INFO 
  print_v(V, "<----");
  break_point();
#endif

  // if V is head of scc, pop all elements of the scc from the stack 
  if (V.lowlink == V.index) {     
    (*n_scc)++; // track how many SCCs found
    vector<int> new_scc;
    int stack_top_id = my_stack->pop_node(); // index for X
    X.instack = false;
    X.closed = true;
    if (not X.weak) {
      new_scc.push_back(stack_top_id);
      // std::cout << stack_top_id << " " << V.id << std::endl;
    }
    while(stack_top_id != V.id) {
      stack_top_id = my_stack->pop_node(); // index for X
      X.instack = false;
      X.closed = true;
      if (not X.weak) {
        new_scc.push_back(stack_top_id);
        // std::cout << stack_top_id << " " << V.id << std::endl;
      }
    }
    scc_vec->push_back(new_scc);
    // break_point();

  } 
}


// tarjan's algorithm for getting the strong components of the graph
VEC_2D get_all_scc(Node* vertices, VEC* out_streets, int n_crossings) 
{
  vector<vector<int>> scc_vector;
  t_stack my_stack;

  int index = 1; // unique node number > 0
  int n_scc = 0; // number of SCCs in G

  for(int i = 0; i < n_crossings; i++) {
    if (vertices[i].index == 0) { // yet unvisited
      find_scc(vertices, out_streets, &my_stack, i, &index, &n_scc, &scc_vector);   
    }
  }
  return scc_vector;
}


void refine_scc(Node* vertices, VEC* out_streets, VEC* new_out_streets, t_stack* my_stack, 
                  int node_id, int* index, int* n_scc, VEC_2D* scc_vec, VEC old_scc_ids)
{
  // V ... expanding crossing with its properties -> V = vertices[node_id]
  // W ... its successors with their properties -> W = vertices[succ_id]
  // X ... crossing poped from the stack -> X = vertices[stack_top_id]
 
  V.index = V.lowlink = (*index)++;
  
  my_stack->push_node(V.id);
  V.instack = true;
  
  for(int j = 0; j < (int)out_streets[V.id].size(); j++) { 

    int succ_id = out_streets[V.id][j];  // index for W
    bool in_scc = false;

    // TODO: potentially slow
    // check if the crossing is in the scc that is refined 
    for(int k = 0; k < (int)old_scc_ids.size(); k++) {
      if(succ_id == old_scc_ids[k]) {
        in_scc = true;
        new_out_streets[V.id].push_back(succ_id);
        break;
      }
    }
    if (not in_scc) 
      continue;

    if (W.index == 0) // W not yet visited
    {
#if PRINT_INFO_2 
      print_v(V, "---->");
      break_point();
#endif
      refine_scc(vertices, out_streets, new_out_streets, my_stack, W.id, index, n_scc, scc_vec, old_scc_ids);
      // std::cout << W.id << " closed? " << W.closed << std::endl;
      // break_point();
      V.lowlink = min(V.lowlink, W.lowlink);
    }
    else if (W.instack) {
      V.lowlink = min(V.lowlink, W.index);
    } 
  } 

#if PRINT_INFO_2 
  print_v(V, "<----");
  break_point();
#endif

  // if V is head of scc, pop all elements of the scc from the stack 
  if (V.lowlink == V.index) {     
    (*n_scc)++; // track how many SCCs found
    vector<int> new_scc;
    int stack_top_id = my_stack->pop_node(); // index for X
    X.instack = false;
    X.closed = true;
    new_scc.push_back(stack_top_id);
    // std::cout << stack_top_id << " " << V.id << std::endl;
    
    while(stack_top_id != V.id) {
      stack_top_id = my_stack->pop_node(); // index for X
      X.instack = false;
      X.closed = true;
      new_scc.push_back(stack_top_id);
      // std::cout << stack_top_id << " " << V.id << std::endl;
    }
    scc_vec->push_back(new_scc);
    // break_point();

  } 
}


// tarjan's algorithm for getting the strong components of the sccs without weak crossings 
VEC_2D refine_all_scc(Node* vertices, VEC* out_streets, VEC* new_out_streets, VEC_2D old_scc_vec)
{
  vector<vector<int>> new_scc_vec;
  t_stack my_stack;

  int index = 1; // unique node number > 0
  int n_scc = 0; // number of SCCs in G

  // set the scc crosses to theirs initial values
  for(int i = 0; i < (int)old_scc_vec.size(); i++) {
    for(int j = 0; j < (int)old_scc_vec[i].size(); j++) {
      vertices[old_scc_vec[i][j]].index = 0;
      vertices[old_scc_vec[i][j]].lowlink = 0;
      vertices[old_scc_vec[i][j]].instack = false;
      vertices[old_scc_vec[i][j]].closed = false;
    }
  }

  // refine the old 'scc' without weak crossings with second-run tarjan 
  for(int i = 0; i < (int)old_scc_vec.size(); i++) {
    for(int j = 0; j < (int)old_scc_vec[i].size(); j++) {
      int c_id = old_scc_vec[i][j];
      // std::cout << "c_id: " << c_id << std::endl;
      if (vertices[c_id].index == 0) { // yet unvisited
        refine_scc(vertices, out_streets, new_out_streets, &my_stack, c_id, 
                    &index, &n_scc, &new_scc_vec, old_scc_vec[i]);   
      }
    }
  }

  return new_scc_vec;
}

//------------------------------------------------------------------------------------


// searches the shortest trail from one crossing to another crossing in the grahp
int* get_min_trails(VEC* new_out_streets, int n_crosses, int max_var, VEC scc_ids, int c_id) 
{
  int* trail_dists = zero_array(new int[n_crosses], n_crosses); 
  int n_dists = 1;

  std::queue<int> queue_crosses;
  int* in_queue = zero_array(new int[n_crosses], n_crosses);

  int trail_len = 0;
  int expecting_new_dist_id = 0;
  int first_new_dist_id = c_id;
  queue_crosses.push(c_id);
  in_queue[c_id] = 1;

  while(not queue_crosses.empty()) {
    int exp_cross_id = queue_crosses.front();
    queue_crosses.pop();
    // std::cout << "pop " << exp_cross_id << " from queue_crosses" << std::endl;
    if (exp_cross_id == first_new_dist_id) {
      expecting_new_dist_id = 1;
    }

    for(int i = 0; i < (int)new_out_streets[exp_cross_id].size(); i++) {
      int new_cross_id = new_out_streets[exp_cross_id][i];

      // check if the new cross isn't already in queue
      if (not in_queue[new_cross_id]) {
        queue_crosses.push(new_cross_id);
        in_queue[new_cross_id] = 1;

        if (expecting_new_dist_id) {
          first_new_dist_id = new_cross_id; 
          trail_len++;
          expecting_new_dist_id = 0;
          // std::cout << "New distance: " << trail_len
          //           << ", first_new_dist_id: " << first_new_dist_id << std::endl;
        }
        // std::cout << "push " << new_cross_id << " to queue_crosses" << std::endl;
      }
      if (trail_dists[new_cross_id] == 0 and new_cross_id != c_id) {
        trail_dists[new_cross_id] = trail_len;
        n_dists++;  
        // std::cout << c_id << "-->" << scc_ids[j] << ": " << trail_len 
        //           << " (" << n_dists << ")" << std::endl;
      } 
    }
    if (n_dists == max_var) {
      break;
    }
  }
  return trail_dists; 
}

void get_best_cross(vector<int> scc_ids, VEC* new_out_streets, int n_crossings, 
                    int* p_crossings, int max_var, int* min_cost) 
{

  int** trail_dists = new int*[n_crossings];
  for(int i = 0; i < max_var; i++) {
    int c_id = scc_ids[i];
    int* new_trail_dists = get_min_trails(new_out_streets, n_crossings, max_var, scc_ids, c_id);
    trail_dists[c_id] = new_trail_dists;
    // std::cout << "Got min trails for " << c_id <<  std::endl;
  }

  for(int i = 0; i < max_var; i++) {
    int cross_cost = 0;
    int c1_id = scc_ids[i];
    for(int j = 0; j < max_var; j++) {
      if (i == j) 
        continue;
      int c2_id = scc_ids[j];
      cross_cost += 2*trail_dists[c1_id][c2_id];
      cross_cost += trail_dists[c2_id][c1_id];
    }

    if(cross_cost < *min_cost or *min_cost == -1) {
      *min_cost = cross_cost;
      *p_crossings = 1;
    }
    else if (cross_cost == *min_cost) {
      (*p_crossings)++; 
    }
  }
}


void get_prosp_cross(VEC_2D strong_components, VEC* out_streets, int n_crossings,
                      int* p_crossings, int* max_var, int* min_cost)
{
  vector<int> max_scc_indexes;
  
  // find every scc that has the max_variability
  for(int i = 0; i < (int)strong_components.size(); i++) {
    int scc_size = (int)strong_components[i].size();
    if(scc_size > *max_var) {
      *max_var = scc_size;
      max_scc_indexes.clear();
      max_scc_indexes.push_back(i);
    } 
    else if (scc_size == *max_var) {
      max_scc_indexes.push_back(i);
    }
  }

  // look for prospective crossings in every scc with max_variability 
  for(int i = 0; i < (int)max_scc_indexes.size(); i++) {
    int scc_index = max_scc_indexes[i];
    // std::cout << "Scc " << index << ": " <<  std::endl;
    get_best_cross(strong_components[scc_index], out_streets, n_crossings, 
                                              p_crossings, *max_var, min_cost);  
  }
  
  (*max_var)--;
}
#endif

