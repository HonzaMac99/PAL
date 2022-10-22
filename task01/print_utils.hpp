#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>
#include <vector>

using namespace std;

void print_ints(int* ints);
void print_edges(int** data, int*distr_edges, int roads);
void print_town_info(int* town_districts, int* town_distances, int n_towns);
void print_frontier(int* frontier, int n_towns, int dist, int expansions);


void print_ints(int* ints) {
  std::cout << ints[0] <<" "<< ints[1] <<" "<< ints[2] << std::endl;
}


void print_edges(int** data, int*distr_edges, int roads) {
  cout << endl;
  for(int i = 0; i < roads; i++) {
    if (distr_edges[i])
      print_ints(data[i]);
  }
}

void print_town_info(int* town_districts, int* town_distances, int n_towns) {
  cout << endl << "Town no.:  x ";
  for(int i = 1; i <= n_towns; i++)
    cout << i << " ";

  cout << endl << "Districts: ";
  for(int i = 0; i <= n_towns; i++)
    cout << town_districts[i] << " ";

  cout << endl << "Distances: ";
  for(int i = 0; i <= n_towns; i++)
    cout << town_distances[i] << " ";
  cout << endl;
}


void print_frontier(int* frontier, int n_towns, int dist, int expansions) {
  cout << "  Frontier_" << dist << ": ";
  for(int i = 0; i <= n_towns; i++ )
    cout << frontier[i] << " ";
  cout << "| " << expansions << endl;
}
#endif

