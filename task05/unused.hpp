#include <iostream>
#include <vector>
#include <queue>
#include "data_utils.hpp"
#include "print_utils.hpp"

#define PRINT_INFO 0

bool has_substring_on_end(std::string main_str, std::string sub_str);


bool has_substring_on_end(std::string main_str, std::string sub_str) {
  int sub_len = sub_str.length();
  int main_len = main_str.length();
  if(main_len < sub_len) 
    return false;
  int offset = main_len-sub_len;
  for(int i = 0; i < sub_len; i++) {
    if(main_str[i+offset] != sub_str[i]) 
      return false;
  }
  return true;
}

  // std::vector<int> vec;
  // std::string substring2 = "ccdcddcc"; 
  // nfa_state* substr_nfa = get_substr_nfa(substring2, 5);

  // std::cout << "TESTING " << substring2 << std::endl;
  // for(int i = 0; i <= substring2.size(); i++) {
  //   for(int j = 0; j < 5; j++) {
  //     std::cout << substr_nfa[i].transitions[('a' + j)].front() << " "; 
  //   }
  //   std::cout << std::endl;
  // }


// old function which stores only the string with its best state 
// into the states of the nfa, which does not have to be the base
// for the lex. smallest variant tha will be generated in the end
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

        // update if: 1) no str was assigned, 2) the new str is better, 
        // 3) the str contains the substr and needs to extend to the finite state
        if (lex_nfa[new_state].best_str == "" or new_str_state > old_str_state 
                                              or new_str_state == substr_len) 
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


// inserting into a vector
#include <iostream>
#include <vector>

int main ()
{
  std::vector<std::string> myvector = {"", "aa", "aaa", "caaaaaaaaaa", "bl", "ble", "blossom"};
  std::vector<std::string>::iterator it = myvector.begin();
  std::string new_str = "aaaaa";
  std::cout << "Size: " << new_str.size() << std::endl;
  int vec_size = myvector.size();
  for(int i = 0; i < vec_size; i++) {
    if(new_str < myvector[i]) 
    {
      myvector.insert(it+i, new_str);
      break;
    }
  }
  myvector.push_back(new_str);
  
  std::cout << "myvector contains: ";
  for (int i = 0; i < myvector.size(); i++)
    std::cout << myvector[i] << ", ";
  std::cout << '\n';

  return 0;
}
