#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <sstream>
#include <map>
#include "print_utils.hpp"

#define DATA_INFO 0

struct nfa_st
{
  bool finite = false;
  map<char, vector<int>> transitions;
}; 

typedef std::vector<int> VEC;
typedef std::vector<vector<int>> VEC_2D;
typedef struct nfa_st nfa_state;

nfa_state* get_stdin_data(int n_states, int n_chars);


// stores data from a stdin 
nfa_state* get_stdin_data(int n_states, int n_chars)
{
  nfa_state* nf_automaton = new nfa_state[n_states];
  std::string input_line; 
  std::getline(std::cin, input_line);
  
  for(int i = 0; i < n_states; i++) {

    std::getline(std::cin, input_line);
    //std::cout << "Newline: " << input_line << std::endl;
    //std::cout << "Line_len: " << input_line.length() << std::endl;

    int state_id = 0; 
    char state_type;
    int idx = 0;
    while(input_line[idx] == ' ') {
      idx++;
    }
    while(input_line[idx] != ' ') {
      state_id = state_id*10 + (int)(input_line[idx] - '0');
      idx++;
    }
    state_type = input_line[++idx];

    //std::cout << "state_id: " << state_id << std::endl;
    //std::cout << "state_type: " << state_type << std::endl;
    nf_automaton[i].finite = (state_type == 'F') ? true : false;

    int input_int = 0;
    char input_char;
    bool creating_int = false;

    int line_len = (int)input_line.length();
    for(int j = idx+1; j < line_len; j++) {
      if (input_line[j] == ' ' ) { 
        if (creating_int) {
          nf_automaton[i].transitions[input_char].push_back(input_int);
          //std::cout << "Adding new int for key " << input_char << ": " << input_int << std::endl;
          input_int = 0;
          creating_int = false;
        }
        continue;
      }
      else if (isalpha(input_line[j])) {
        input_char = input_line[j];
        //std::cout << "New key: " << input_char 
        //          << " on index " << j << std::endl;
      } 
      else {
        creating_int = true;
        input_int = input_int*10 + (int)(input_line[j] - '0');
        if (j == line_len-1) {
          nf_automaton[i].transitions[input_char].push_back(input_int);
          //std::cout << "Adding new int for key " << input_char << ": " << input_int << std::endl;
          input_int = 0;
        }
      }
    }

    // Print the dictionary
    //std::cout << "PRINTING DICT:" << std::endl;
    std::cout << nf_automaton[i].finite << "  ";
    for (const auto &pair : nf_automaton[i].transitions) {
      std::cout << pair.first << ": ";
      for (const int &i : pair.second) {
        std::cout << i << " ";
      }
      std::cout << "  ";
    }
    std::cout << std::endl;
  }
  return nf_automaton;
}
#endif

