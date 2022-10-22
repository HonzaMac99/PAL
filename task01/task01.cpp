#include <iostream>
#include "task01.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"

int main(int argc, char* argv[])
{
  // Read the input from file of stdin
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

  quickSort(data, 0, n_roads-1); // sort data by cost of the roads
  // std::cout << "Quicksort done" << std::endl;
  int* town_districts = zero_array(new int[n_towns+1], n_towns+1);
  int* town_distances = zero_array(new int[n_towns+1], n_towns+1);

  
  // set towns dirtrs and d and get list of idx of roads connecting the distrs
  int *distr_edges = process_towns(data, town_districts, town_distances, 
                                    n_towns, n_dtowns, n_roads);
  // std::cout << "Towns processed" << std::endl;

  // print_edges(data, distr_edges, n_roads);

  // print_town_info(town_districts, town_distances, n_towns); 

  int min_cost = 0;
  min_cost += get_mst_cost(data, town_districts, n_towns, n_dtowns, n_roads);
  // std::cout << "Mst cost done" << std::endl;
  min_cost += get_glob_mst_cost(data, town_districts, n_towns, n_dtowns, n_roads);
  // std::cout << "Global mst cost done" << std::endl;
  std::cout << min_cost << std::endl;

  // clear the memory
  for (int i = 0; i < n_roads; i++)
    delete [] data[i];
  delete [] data;
  delete [] distr_edges;
  delete [] town_districts;
  delete [] town_distances;
  
  return 0;
}
