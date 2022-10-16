#include <iostream>
#include "task01.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"

int main(int argc, char* argv[])
{
  // Read from the text file
  std::string file_name = "/home/honzamac/PAL/task01/datapub/pub01.in";
  if (argc > 1) 
    file_name = argv[1];

  int n_towns, n_dtowns, n_roads; 
  int **data = get_data(file_name, &n_towns, &n_dtowns, &n_roads);
  int* town_districts = zero_array(new int[n_towns+1], n_towns+1);
  int* town_distances = zero_array(new int[n_towns+1], n_towns+1);

  std::cout << std::endl;
  // sort array by the cost of the roads
  sort_array(data, n_roads);
  
  int *distr_edges = process_towns(data, town_districts, town_distances, n_towns, n_dtowns, n_roads);

  for(int i = 0; i < n_roads; i++) {
    if (distr_edges[i])
      std::cout << data[i][0] << " "
                << data[i][1] << " "
                << data[i][2] << std::endl;
  }

  print_town_info(town_districts, town_distances, n_towns); 

  int min_cost = get_msp_cost(data, town_districts, n_towns, n_dtowns, n_roads);
  
  return 0;
}
