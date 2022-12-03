#include <iostream>
#include <fstream>
#include <sstream>
#include "task04.hpp"
#include "print_utils.hpp"

#define llong long long
#define VEC vector<llong>
#define VEC_2D vector<vector<llong>>

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
    
  long long M_max;
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


  long long L;
  int R_max; 
<<<<<<< HEAD
  //get_lehmers(M_max, D, &L, &R_max);
  
  int test_m_max = 19;
  VEC prime_fs = eratosthenes(test_m_max); 
  std::cout << prime_fs.back() << std::endl;
  llong root = get_primitive_root(test_m_max, prime_fs);
  std::cout << root << std::endl;
  
  //VEC primes = eratosthenes(100000000);
  //std::cout << primes.back() << std::endl;
  
  //std::cout << L << " " << R_max << std::endl;
=======
  int* primes = get_prime_factors();
  get_lehmers(M_max, D, primes, &L, &R_max);


  std::cout << L << " " << R_max << std::endl;
>>>>>>> c8364b251ceefc4dcde97ef870730e1c512fc749

  return 0;
}
