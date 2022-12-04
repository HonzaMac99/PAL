#ifndef PRINT_LIB
#define PRINT_LIB

#include <iostream>
#include <vector>

#define llong long long

using namespace std;

template<class T> 
  void break_point(T input);
void break_point();
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

#endif


