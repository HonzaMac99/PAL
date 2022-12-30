#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

//if the new string is better, update the nfa_state and return true if updated
nfa_state* get_substr_nfa(std::string substring);
std::string get_nfa_word(nfa_state* lex_nfa, nfa_state* substr_nfa, int alphabet_len, int substr_len);


nfa_state* get_substr_nfa(std::string substring, int alphabet_len) 
{
  int str_len = substring.length();
  nfa_state* substr_nfa = new nfa_state[str_len+1];

  // Set transitions for cases when the correct char will be read
  for(int i = 0; i < str_len; i++) {
    char next_char = substring[i];    
    substr_nfa[i].transitions[next_char].push_back(i+1); 
  }

  // In the final state, there are only transitions to this state
  int final_state_id = str_len;
  for(int j = 0; j < alphabet_len; j++) {
    substr_nfa[final_state_id].transitions['a' + j ].push_back(final_state_id); 
  }

  // Set transition to state 1 for every state 
  // that does not continue with this char
  for(int i = 1; i < str_len; i++) {
    if (substring[i] != substring[0]) {
      substr_nfa[i].transitions[substring[0]].push_back(1); 
    }
    else {
      int j = 1;
      while(i+j < str_len && substring[i+j] == substring[j]) {
        j++;
      }
      substr_nfa[i+j].transitions[substring[j]].push_back(j+1); 
    }
  }

  // Fill the rest with return to the initial state 0
  for(int i = 0; i < str_len; i++) {
    for(int j = 0; j < alphabet_len; j++) {
      if (substr_nfa[i].transitions['a' + j].empty()) {
        substr_nfa[i].transitions['a' + j].push_back(0);
      } 
    }
  }
  return substr_nfa;
}


std::string get_nfa_word(nfa_state* lex_nfa, nfa_state* substr_nfa, int alphabet_len, int substr_len) 
{
  std::string nfa_word;
  int exp_state;
  std::queue<int> states_q;
  states_q.push(0);

  while(not states_q.empty()) {
    exp_state = states_q.front();
    states_q.pop();
    for(int i = 0; i < alphabet_len; i++) 
    {
      char new_char = 'a' + i;
      for(const int &new_state : lex_nfa[exp_state].transitions[new_char]) 
      {
        int old_str_state = lex_nfa[exp_state].best_str_state;
        int new_str_state = substr_nfa[old_str_state].transitions[new_char][0];

        if (lex_nfa[new_state].best_str == "" or new_str_state > old_str_state) 
        {
          lex_nfa[new_state].best_str = lex_nfa[exp_state].best_str; 
          lex_nfa[new_state].best_str += new_char;
          lex_nfa[new_state].best_str_state = new_str_state;

          std::cout << "Adding " << lex_nfa[new_state].best_str 
                    << " to " << new_state 
                    << " with score " << lex_nfa[new_state].best_str_state 
                    << std::endl;

          states_q.push(new_state);

          if(lex_nfa[new_state].finite and new_str_state == substr_len) 
            return lex_nfa[new_state].best_str;
        }
      }
    }
  }
  std::cerr << "No string found!" << std::endl;
  return "";
}


#endif

