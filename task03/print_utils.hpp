#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>
#include <vector>
#include "node.hpp"

#define VEC_2D vector<vector<int>>
#define VEC_P vector<int>*

using namespace std;

template<class T> 
  void break_point(T input);
void break_point();
void print_scc(VEC_2D strong_components);
void print_adj_list(vector<int>* adj_list, int n_crossings);
void print_ints(int* ints);

int break_point_n = 0;
char break_point_arr[1000];

template<class T> 
void break_point(T input) {
  cout << "==BP== value: " << input << endl; // print the input
  cin >> break_point_arr[break_point_n]; // pauses the programm here 
  break_point_n = min(break_point_n+1, 1000-1);
}

void break_point() {
  cout << "==BP==" << endl;
  cin >> break_point_arr[break_point_n]; // pauses the programm here 
}

void print_adj_list(vector<int>* adj_list, int n_of_items) 
{
  cout << endl;
  for(int i = 0; i < n_of_items; i++) 
  {
    int n_succ = (int)adj_list[i].size();

    cout << "Node " << i << ": ["; 
      for(int j = 0; j < n_succ-1; j++) 
      {
        cout << adj_list[i][j] << ", ";
      }
    if (n_succ != 0) 
      cout << adj_list[i][n_succ-1] << "]" << endl;
    else
      cout << "]" << endl;
  }
  cout << endl;
}

#endif


