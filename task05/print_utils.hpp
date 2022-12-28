#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VEC;
typedef vector<int>* VEC_P;
typedef vector<vector<int>> VEC_2D;

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

void print_scc(VEC_2D strong_components) 
{
  for(int i = 0; i < (int)strong_components.size(); i++) 
  {
    int max_elements = 0;
    int n_elements = (int)strong_components[i].size();
    if (n_elements > max_elements) max_elements = n_elements;

    cout << "Scc " << i << ": ["; 
    for(int j = 0; j < n_elements-1; j++) 
    {
      cout << strong_components[i][j] << ", ";
    }
    if (n_elements != 0) 
      cout << strong_components[i][n_elements-1] << "]" << endl;
    else
      cout << "]" << endl;
  }
  cout << endl;
}

void print_adj_list(vector<int>* adj_list, int n_crossings) 
{
  for(int i = 0; i < n_crossings; i++) 
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

void print_ints(int* ints) {
  cout << ints[0] <<" "<< ints[1] << endl;
}

#endif


