#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>

void print_town_info(int* town_districts, int* town_distances, int n_towns);
void print_frontier(int* frontier, int n_towns, int dist, int expansions);


void print_town_info(int* town_districts, int* town_distances, int n_towns) {
  std::cout << std::endl << "Town no.:  x ";
  for(int i = 1; i <= n_towns; i++)
    std::cout << i << " ";

  std::cout << std::endl << "Districts: ";
  for(int i = 0; i <= n_towns; i++)
    std::cout << town_districts[i] << " ";

  std::cout << std::endl << "Distances: ";
  for(int i = 0; i <= n_towns; i++)
    std::cout << town_distances[i] << " ";
  std::cout << std::endl;
}


void print_frontier(int* frontier, int n_towns, int dist, int expansions) {
  std::cout << "  Frontier_" << dist << " :";
  for(int i = 0; i <= n_towns; i++ )
    std::cout << frontier[i] << " ";
  std::cout << "| " << expansions << std::endl;
}
#endif

