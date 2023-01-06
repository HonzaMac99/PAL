#include <iostream>
#include "task06.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT 0

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;


int main()
{
  // Do './task06 < ../datapub/pub01.in' for reading files using stdin
  // No need for implementing reading from file in the program 
  
  int n_rows, n_cols, f_chain_len, n_clips, clip_factor, rplc_factor;
  std::cin >> n_rows >> n_cols >> f_chain_len >> n_clips >> clip_factor >> rplc_factor;

  //nfa_state* lex_nfa = get_stdin_data(n_states);
  VEC_2D prod_matrix = get_prod_matrix(n_rows, n_cols);

  std::string f_chain;
  std::cin >> f_chain; 

  VEC_2D clip_schemes = get_clip_schemes(n_clips);

  std::string substring; 
  std::getline(std::cin, substring);
  nfa_state* substr_nfa = get_substr_nfa(substring, alphabet_len);

  int substr_len = substring.length();
  std::string nfa_word = get_nfa_word(lex_nfa, substr_nfa, alphabet_len, substr_len);

  std::cout << nfa_word << std::endl;

  return 0;
}
