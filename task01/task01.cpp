#include <iostream>
#include "task01.hpp"
#include "data_utils.hpp"

#define MAX_T 250000
#define MAX_D 2000
#define MAX_R 450000

#define EDGE_COST_MIN 1
#define EDGE_COST_MAX 250 

// perform BFS on the cities, define districts 
// and their distances to their district towns
int* set_districts(int **data, int towns, int districts, int roads) {
  int* town_districts = new int[towns];
  for(int i = 1; i <= districts; i++) {
      
  }
  


  return town_districts;
}

int main(int argc, char* argv[])
{
  // Read from the text file
  std::string file_name = "/home/honzamac/PAL/task01/datapub/pub01.in";
  if (argc > 1) 
    file_name = argv[1];

  int n_towns, n_dtowns, n_roads; 
  int **data = get_data(file_name, &n_towns, &n_dtowns, &n_roads);
  int *town_districts = new int[n_towns];

  // sort array by the cost of the roads
  data = sort_array(data, n_roads);


  return 0;
}
