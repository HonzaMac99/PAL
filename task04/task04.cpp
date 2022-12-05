#include <iostream>
#include <fstream>
#include <sstream>
#include "task04.hpp"
#include "print_utils.hpp"

#define llong long long
#define VEC std::vector<int>

#define PRINT 1


int main(int argc, char* argv[])
{
  // Read the input from file or stdin
  std::string file_name;
  int stdin_input = 1;
  if (argc > 1) {
    file_name = argv[1];
    if (file_name == "-f")
      file_name = "/home/honzamac/PAL/task04/datapub/pub01.in";
    stdin_input = 0;
  } 
  else {
    std::cerr << "Specify the file name (or -f) in argument" << std::endl;
    return 1;
  }
    
  llong M_max;
  int D;
  if (stdin_input) {
    std::cin >> M_max; 
    std::cin >> D;
  }
  else {
    std::ifstream MyReadFile(file_name);
    std::stringstream ss;
    std::string fileLine;
    getline(MyReadFile, fileLine);
    ss << fileLine;

    ss >> M_max; 
    ss >> D;
  }


  llong L = 0;
  int R_max = 0; 
  VEC primes = get_primes(D);
  // starting with M = 1 + 2 = 3
  VEC prime_factors = {2};
  llong M = 3;
  int index = 0;

  // llong test = compute_modulo(7, 3, 6);
  // std::cout << "Test modulo: " << test << std::endl;
  // break_point();
  
  // check if the first combination is ok
  if (M < M_max) {
    L++;
    get_prim_root(M, prime_factors, &R_max);
    get_lehmers(primes, prime_factors, M, index, M_max, &L, &R_max);
  }

  std::cout << L << " " << R_max << std::endl;

  return 0;
}
