#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "print_utils.hpp"

#define DATA_INFO 1

struct nfa_st
{
  bool finite = false;
  VEC_2D transitions;
}; 

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;
typedef struct nfa_st nfa_state;

vector<nfa_state> get_stdin_data();

// stores data from a stdin into a 2D array
// also stores values about the data 
vector<nfa_state> get_stdin_data() 
{
  std::vector<nfa_state> nf_automaton;

  char test1, test2, test3;
  cin >> test1 >> test2 >> test3;
  cout << test1 << " " << test2 << " " << test3 << endl;

  // int state_id, char_id;
  // bool finite; 
  // char state_type;
  // VEC_2D transition_matrix;

  // for(int i = 0; i < n_states; i++) 
  // {
  //   VEC state_trans;
  //   std::cin >> state_id >> state_type;
  //   finite = (state_type == 'F') ? true : false;

  //   std::cin >> char_id; //a
  //   for(int j = 0; j < n_chars; j++) 
  //   {

  //   
  //   }
  // }
  
  return nf_automaton;
}
#endif

