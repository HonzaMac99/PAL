#include <iostream>
#include <algorithm>
#include "task01.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT 0

bool mySort(int* a, int*b) {
  return a[2] < b[2];
}


int main(int argc, char* argv[])
{
  // Read the input from file or stdin
  std::string file_name;
  int stdin_input = 1;
  if (argc > 1) {
    file_name = argv[1];
    if (file_name == "-f")
      file_name = "/home/honzamac/PAL/task01/datapub/pub01.in";
    stdin_input = 0;
  }
    
  int n_towns, n_dtowns, n_roads; 
  int **data;
  if (stdin_input) {
    data = get_stdin_data(&n_towns, &n_dtowns, &n_roads);
  }
  else {
    data = get_file_data(file_name, &n_towns, &n_dtowns, &n_roads);
  }

  // sort the roads by their cost in ascending order
  std::sort(data, data+n_roads, mySort); 
#if PRINT
  std::cout << "Quicksort done" << std::endl;
#endif

  // find a corresponding district for each town
  int* town_districts = zero_array(new int[n_towns+1], n_towns+1);
  process_towns(data, town_districts, n_towns, n_dtowns, n_roads);
#if PRINT
  std::cout << "Towns processed" << std::endl;
#endif

  // print_edges(data, distr_edges, n_roads);

  // print_town_info(town_districts, town_distances, n_towns); 

  int min_cost = 0;
  min_cost += get_mst_cost(data, town_districts, n_towns, n_roads);
#if PRINT
  std::cout << "Mst cost done " << min_cost << std::endl;
#endif

  min_cost += get_glob_mst_cost(data, town_districts, n_dtowns, n_roads);
#if PRINT
  std::cout << "Global mst cost done " << min_cost << std::endl;
#endif

  std::cout << min_cost << std::endl;

  // clear the memory
  for (int i = 0; i < n_roads; i++)
    delete [] data[i];
  delete [] data;
  delete [] town_districts;
  
  return 0;
}
