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

// std::cout << "TESTING" << std::endl;
// std::vector<int> vec;
// std::string substring2 = "abcabdabcd"; 
// nfa_state* substr_nfa = get_substr_nfa(substring2, 4);
// vec = substr_nfa[0].transitions['a'];
// std::cout << "0 a " << vec.front() << std::endl;
// vec = substr_nfa[5].transitions['c'];
// std::cout << "5 c " << vec.front() << std::endl;
// vec = substr_nfa[8].transitions['d'];
// std::cout << "8 d " << vec.front() << std::endl;
