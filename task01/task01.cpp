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
  set_town_info(data, town_districts, town_distances, n_towns, n_dtowns, n_roads);

  print_town_info(town_districts, town_distances, n_towns); 

  // sort array by the cost of the roads
  data = sort_array(data, n_roads);

  return 0;
}
