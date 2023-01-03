#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <unistd.h>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

//if the new string is better, update the nfa_state and return true if updated
nfa_state* get_substr_nfa(std::string substring);
bool update_word(nfa_state lex_nfa_state, std::string new_word, int new_word_state);
std::string get_nfa_word(nfa_state* lex_nfa, nfa_state* substr_nfa, int alphabet_len, int substr_len);


// note: could use lighter struct than nfa_state, 
// but for < 10 states it does not make an impact on memory performance
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


bool update_word(nfa_state* lex_nfa_state, std::string new_word, int new_word_state) 
{
  bool inserted = false;

  std::string lex_word = lex_nfa_state->words[new_word_state];
  // note: you can use '<' and '>' on strings in c++11, but not in c++20
  if (lex_word == "" or new_word.size() < lex_word.size() or 
      (new_word.size() == lex_word.size() and new_word < lex_word))
  {
    lex_nfa_state->words[new_word_state] = new_word; 
    inserted = true;
  }
  return inserted;
}


std::string get_nfa_word(nfa_state* lex_nfa, nfa_state* substr_nfa, int alphabet_len, int substr_len) 
{
  int end_state = substr_len;
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
        for(int j = 0; j <= end_state; j++) 
        {
          if (lex_nfa[exp_state].words[j] == "" and not (j == 0 and exp_state == 0)) 
            continue;
          int new_word_state = substr_nfa[j].transitions[new_char][0];
          std::string new_word = lex_nfa[exp_state].words[j] + new_char;
          
          if (update_word(&lex_nfa[new_state], new_word, new_word_state)) {
#if PRINT_INFO
            std::cout << "Updating '" << new_word << "' (" << new_word_state 
                      << ") from state " << exp_state 
                      << " to state " << new_state << " (" 
                      << lex_nfa[new_state].finite << ")" << std::endl;
            //sleep(1)
#endif
            states_q.push(new_state);
          }
        }

        if (lex_nfa[new_state].finite and lex_nfa[new_state].words[end_state] != "") {
          return lex_nfa[new_state].words[end_state];
        }
      }
    }
  }
  std::cerr << "No string found!" << std::endl;
  return "";
}


#endif

