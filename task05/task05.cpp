#include <iostream>
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
  int n_states, alphabet_len;
  std::cin >> n_states >> alphabet_len; 

  nfa_state* lex_nfa = get_stdin_data(n_states);

  std::string substring; 
  std::getline(std::cin, substring);
  nfa_state* substr_nfa = get_substr_nfa(substring, alphabet_len);

  int substr_len = substring.length();
  std::string nfa_word = get_nfa_word(lex_nfa, substr_nfa, alphabet_len, substr_len);

  std::cout << nfa_word << std::endl;

  return 0;
}
