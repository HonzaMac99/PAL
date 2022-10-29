#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>
#include <vector>

using namespace std;

void print_adj_list(vector<int>* adj_list, int n_crossings);
void print_ints(int* ints);


void print_adj_list(vector<int>* adj_list, int n_crossings) 
{
  for(int i = 0; i < n_crossings; i++) 
  {
    for(int j = 0; j < (int)adj_list[i].size(); j++) 
    {
      cout << adj_list[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void print_ints(int* ints) {
  cout << ints[0] <<" "<< ints[1] << endl;
}

#endif

