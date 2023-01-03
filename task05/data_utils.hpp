#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <map>
#include "print_utils.hpp"

#define DATA_INFO 0 

struct nfa_st
{
  bool finite = false;
  map<char, vector<int>> transitions;

  std::vector<std::string> words = {"", "", "", "", "",
                                    "", "", "", "", "", ""};
}; 

struct st_info 
{
  int id = 0;
  std::string w = "";
  int w_state = 0;
};  

typedef struct nfa_st nfa_state;
typedef struct st_info state_info;

nfa_state* get_stdin_data(int n_states);


// stores data from a stdin 
nfa_state* get_stdin_data(int n_states)
{
  nfa_state* lex_nfa = new nfa_state[n_states];
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
    lex_nfa[i].finite = (state_type == 'F') ? true : false;

    int input_int = 0;
    char input_char;
    bool creating_int = false;

    int line_len = (int)input_line.length();
    for(int j = idx+1; j < line_len; j++) {
      if (input_line[j] == ' ' ) { 
        if (creating_int) {
          lex_nfa[i].transitions[input_char].push_back(input_int);
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
          lex_nfa[i].transitions[input_char].push_back(input_int);
          //std::cout << "Adding new int for key " << input_char << ": " << input_int << std::endl;
          input_int = 0;
        }
      }
    }

#if DATA_INFO
    // Print the dictionary
    std::cout << "PRINTING DICT:" << std::endl;
    std::cout << lex_nfa[i].finite << "  ";
    for (const auto &pair : lex_nfa[i].transitions) {
      std::cout << pair.first << ": ";
      for (const int &i : pair.second) {
        std::cout << i << " ";
      }
      std::cout << "  ";
    }
    std::cout << std::endl;
#endif
  }
  return lex_nfa;
}
#endif

