#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
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
int* get_prosp_cross(VEC_2D strong_components, Node* vertices);


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


int* get_prosp_cross(VEC_2D strong_components, Node* vertices) 
{
  int* results = new int[3];
  int p_crossings = 0, max_var = 0, min_cost = 0;


  results[0] = p_crossings;
  results[1] = max_var;
  results[2] = min_cost;

  return results;
}
#endif

