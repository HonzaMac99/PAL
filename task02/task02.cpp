#include <iostream>
#include <algorithm>
#include "task02.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"
#include "node.hpp"

#define PRINT 1

bool mySort(int* a, int*b) {
  return a[2] < b[2];
}


int main(int argc, char* argv[])
{
  // Read the input from file of stdin
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

  process_crosses(data, out_streets, in_streets, n_streets);
#if PRINT
  std::cout << "Graph created" << std::endl;
#endif

  print_adj_list(out_streets, n_crossings);
  print_adj_list(in_streets, n_crossings);

  int n_pcrossings = 0, max_var = 0, min_cost = 0;


  std::cout << n_pcrossings << " " << max_var << " " << min_cost << std::endl;

  // clear the memory
  for (int i = 0; i < n_streets; i++)
    delete [] data[i];
  delete [] data;
  delete [] out_streets;
  delete [] in_streets;
  
  return 0;
}
