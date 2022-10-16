#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>
#include <vector>
#include "node.hpp"

using namespace std;

void print_town_info(int* town_districts, int* town_distances, int n_towns);
void print_frontier(int* frontier, int n_towns, int dist, int expansions);
void print_node(Node* node);


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

void print_node(Node* node) {
  cout << "Node id is: " << node->id << endl;
  if (node->parent != NULL) {
    cout << "Parent id is: " << node->parent->id << endl;
  }
  else {
    cout << "The node is a root" << endl;
  }

  if (!node->childs.empty()) {
    for (int i = 0; i < (int)node->childs.size(); i++) {
      cout << "Child " << i << " id is: " << node->childs[i]->id << endl;
    }
  } 
  else {
    cout << "The node has no children!" << endl;
  }
  cout << "-------------------------" << endl << endl;
}
#endif

