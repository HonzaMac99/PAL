#include <iostream>
#include <algorithm>
#include "task05.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT 1

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;


int main()
{
  // Do './task05 < ../datapub/pub01.in' for reading files using stdin
  // Therefore no need for implementing reading from file in the program 
  int n_states, n_chars;
  std::cin >> n_states >> n_chars; 

  nfa_state* nf_automaton = get_stdin_data(n_states, n_chars);

  std::string input_line; 
  std::getline(std::cin, input_line);
  std::cout << input_line << std::endl;

  std::cout << n_states << " " << n_chars << std::endl;

  return 0;
}
