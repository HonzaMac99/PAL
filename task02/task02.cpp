#include <iostream>
#include <algorithm>
#include "task02.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"
#include "node.hpp"

#define PRINT 1


int main(int argc, char* argv[])
{
  // Read the input from file or stdin
  std::string file_name;
  int stdin_input = 1;
  if (argc > 1) {
    file_name = argv[1];
    if (file_name == "-f")
      file_name = "/home/honzamac/PAL/task02/datapub/pub01.in";
    stdin_input = 0;
  }
    
  int n_crossings, n_streets;
  int **data;
  if (stdin_input) {
    data = get_stdin_data(&n_crossings, &n_streets);
  }
  else {
    data = get_file_data(file_name, &n_crossings, &n_streets);
  }
  
  // adjacency lists for children and parents of the nodes
  vector<int>* out_streets = new vector<int>[n_crossings]; 
  vector<int>* in_streets = new vector<int>[n_crossings]; 
  
  // list of graph node structs 
  //Node* graph_verts = (Node*)malloc(sizeof(Node)*n_crossings);
  Node* graph_verts = new Node[n_crossings];
  for(int i = 0; i < n_crossings; i++) {
    graph_verts[i].id = i;
  } 

  process_crosses(data, out_streets, in_streets, n_streets);
#if PRINT
  std::cout << "Graph created" << std::endl;
#endif
  print_adj_list(out_streets, n_crossings);
  // print_adj_list(in_streets, n_crossings);
  
  vector<vector<int>> scc_vector = get_all_scc(graph_verts, out_streets, n_crossings);
#if PRINT
  std::cout << "Strong components established" << std::endl;
#endif

  //print_scc(scc_vector);

  int* results = get_prosp_cross(scc_vector, out_streets);
#if PRINT
  std::cout << "Prospective crossings found" << std::endl;
#endif

  std::cout << results[0] << " " << results[1] << " " << results[2] << std::endl;

  // clear the memory
  for (int i = 0; i < n_streets; i++)
    delete [] data[i];
  delete [] data;
  delete [] graph_verts;
  delete [] results;
  
  return 0;
}
