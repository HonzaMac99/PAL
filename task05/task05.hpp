#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <unistd.h>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

//if the new string is better, update the nfa_state and return true if updated
nfa_state* get_substr_nfa(std::string substring);
bool insert_word(nfa_state lex_nfa_state, std::string new_word, int new_word_state);
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


// 2) if not in the new state word list, insert the word in lex. order
// 3) update the best_word state and index values
bool insert_word(nfa_state* lex_nfa_state, std::string new_word, int new_word_state) {
  bool inserted = false;
  bool to_insert = true;

  std::vector<int>::iterator it = lex_nfa_state->word_states.begin();
  std::vector<std::string>::iterator it_str = lex_nfa_state->words.begin();

  int n_new_st_words = lex_nfa_state->words.size();
  for(int k = 0; k < n_new_st_words; k++) 
  {
    std::string lex_word = lex_nfa_state->words[k];
    // note: you can use '<' and '>' on strings in c++11, but not in c++20
    if (new_word.size() > lex_word.size() or 
        (new_word.size() == lex_word.size() and new_word > lex_word)) 
      continue;

    if (new_word == lex_word) { 
      to_insert = false;
      break;
    }

    // insert before the first lexgraf. bigger word, 
    // if the new_word is not in the new_state.words list
    if (new_word.size() < lex_word.size() or
        (new_word.size() == lex_word.size() and new_word < lex_word))  
    {
      lex_nfa_state->word_states.insert(it+k, new_word_state);
      lex_nfa_state->words.insert(it_str+k, new_word); 

      if (new_word_state > lex_nfa_state->best_word_state or 
          (new_word_state == lex_nfa_state->best_word_state and 
           k < lex_nfa_state->best_word_idx)) 
      {
        lex_nfa_state->best_word_state = new_word_state;
        lex_nfa_state->best_word_idx = k;
      }
      inserted = true;
      to_insert = false;
      break;
    }
  }
  if (to_insert) {
    lex_nfa_state->word_states.push_back(new_word_state);
    lex_nfa_state->words.push_back(new_word); 
    if (new_word_state > lex_nfa_state->best_word_state) 
    {
      lex_nfa_state->best_word_state = new_word_state;
      lex_nfa_state->best_word_idx = n_new_st_words;
    }
    inserted = true;
  }
  return inserted;
}


std::string get_nfa_word(nfa_state* lex_nfa, nfa_state* substr_nfa, int alphabet_len, int substr_len) 
{
  std::string nfa_word;
  int exp_state;
  std::queue<int> states_q;
  std::set<int> states_set;
  states_q.push(0);
  states_set.insert(0);

  while(not states_q.empty()) {
    exp_state = states_q.front();
    states_q.pop();
    states_set.erase(exp_state);

    int n_exp_words = lex_nfa[exp_state].words.size();
    for(int i = 0; i < alphabet_len; i++) 
    {
      char new_char = 'a' + i;
      for(const int &new_state : lex_nfa[exp_state].transitions[new_char]) 
      {
        bool inserted = false; 
        for(int j = 0; j < n_exp_words; j++) 
        {
          // 1) create new words from the exp_state word list and the new_char
          int old_word_state = lex_nfa[exp_state].word_states[j];
          int new_word_state = substr_nfa[old_word_state].transitions[new_char][0];
          std::string new_word = lex_nfa[exp_state].words[j] + new_char;

          // 2) if not in the new state word list, insert them in lex. order
          // 3) update the best_word state and index values
          if (insert_word(&lex_nfa[new_state], new_word, new_word_state)) {
            bool finish = lex_nfa[new_state].finite;
            // std::cout << "Inserting '" << new_word << "' (" << new_word_state 
            //           << ") to state " << new_state << " (" << finish << ")"  
            //           << std::endl;
            // sleep(1);
            inserted = true;
          }
        }

        // using these vars for more clear code
        int best_st = lex_nfa[new_state].best_word_state;
        int best_idx = lex_nfa[new_state].best_word_idx;

        if (inserted) {
          int in_queue = states_set.count(new_state); 
          if (not in_queue) { 
            states_q.push(new_state);
            states_set.insert(new_state);
          }
        }

        if (lex_nfa[new_state].finite and best_st == substr_len) 
          return lex_nfa[new_state].words[best_idx];
      }
    }
  }
  std::cerr << "No string found!" << std::endl;
  return "";
}


#endif

