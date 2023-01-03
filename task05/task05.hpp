#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
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
  bool starting = true;
  bool ending = false;
  int ending_state = -1;
  std::string best_string;
  std::queue<state_info> states_q;
  state_info first_state;
  states_q.push(first_state);

  while(not states_q.empty()) 
  {
    state_info exp_state = states_q.front();
    states_q.pop();

    // std::string ref_str = "aaccbbbaccabacdcaaadcbdcadddaacdcccdcddcc";
    // if (exp_state.w == "aaccbbbaccabacdcaaadcbdcadddaacdcccdcddcc") {
    //   std::cout << "State " << exp_state.id << std::endl;
    //   for(int j = 0; j <= end_state; j++) 
    //   {
    //     std::string new_str = lex_nfa[exp_state.id].words[j];
    //     if (not(new_str == "")) { 
    //       for(int k = 0; k < new_str.size(); k++) {
    //         if(new_str[k] == ref_str[k]) 
    //           std::cout << "_";
    //         else 
    //          std::cout << new_str[k];
    //       }
    //       std::cout << " " << j << std::endl;
    //     }
    //   }
    // }

    bool updated = update_word(&lex_nfa[exp_state.id], exp_state.w, exp_state.w_state);
    if (not updated and not starting) 
      continue;

#if PRINT_INFO
    std::cout << "Updating '" << exp_state.w << "' (" << exp_state.w_state 
              << ") to state " << exp_state.id << " (" 
              << lex_nfa[exp_state.id].finite << ")" << std::endl;
    //sleep(1);
#endif

    if (lex_nfa[exp_state.id].finite and lex_nfa[exp_state.id].words[end_state] != "") {
      ending = true;
      if (ending_state == -1 or exp_state.id == ending_state) 
      {
        ending_state = exp_state.id;
        best_string = lex_nfa[exp_state.id].words[end_state];
      }
    }
    
    for(int i = 0; i < alphabet_len; i++) 
    {
      char new_char = 'a' + i;
      for(const int new_st_id : lex_nfa[exp_state.id].transitions[new_char]) 
      {
        for(int j = 0; j <= end_state; j++) 
        {
          if (lex_nfa[exp_state.id].words[j] == "" and not (j==0 and starting)) 
            continue;

          state_info new_state;
          new_state.id = new_st_id;
          new_state.w = lex_nfa[exp_state.id].words[j] + new_char;
          new_state.w_state = substr_nfa[j].transitions[new_char][0];
          
          if(not ending) 
            states_q.push(new_state);
        }
      }
    }
    if(starting)
      starting = false;
  }
  return best_string;
  //std::cerr << "No string found!" << std::endl;
  //return "";
}


#endif

