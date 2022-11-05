#include <iostream>
#include <algorithm>
#include "task05.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"

#define VEC vector<int>
#define VEC_2D vector<vector<int>>

#define PRINT 1



int main(int argc, char* argv[])
{
  // Read the input from file or stdin
  std::string file_name;
  int stdin_input = 1;
  if (argc > 1) {
    file_name = argv[1];
    if (file_name == "-f")
      file_name = "/home/honzamac/PAL/task05/datapub/pub01.in";
    stdin_input = 0;
  }
    
  int m_max, d;
  if (stdin_input) {
    std::cin >> m_max; 
    std::cin >> d; 
  }
  else {
    std::ifstream MyReadFile(file_name);
    std::stringstream ss;
    std::string fileLine;
    getline(MyReadFile, fileLine);
    ss << fileLine;

    ss >> m_max; 
    ss >> d;
  }

  std::cout << "0 0" << std::endl;

  return 0;
}
