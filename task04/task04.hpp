#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <cmath>
#include "print_utils.hpp"

#define llong long long
#define VEC std::vector<int>

#define PRINT_INFO 0
#define MAX_D 40

VEC get_primes(int max_num);
bool is_prime(llong num);
void get_lehmers(VEC primes, VEC prime_factors, llong M_old, int index, 
                  llong M_max, llong* L, int* R_max);
void get_prim_root(llong M, VEC prime_factors, int* R_max);


// get all primes that are not larger than D (max_num) 
VEC get_primes(int max_num)
{
  int* numbers = new int[max_num+1];

  std::fill(numbers, numbers+max_num+1, 1);

  int sq = ceil(sqrt(max_num));

  for(int i = 2; i < sq; i++) {
    if(numbers[i]) {
      for(int j = int(pow(i, 2)); j <= max_num; j+=i) {
        numbers[j] = 0;
      }
    }
  }

  VEC primes;
  for(int i = 0; i <= max_num; i++) {
    if (numbers[i] and i >= 2)
      primes.push_back(i);
  }
  delete [] numbers;
  return primes;
}


bool is_prime(llong num) 
{
  // Corner cases
  if (num <= 1)  
    return false;
  else if (num <= 3)  
    return true;
 
  // This is checked so that we can skip 
  // middle five numbers in the loop below
  if (num % 2 == 0 || num % 3 == 0)
    return false;
 
  for (llong i = 5; i*i <= num; i+=6)
    if (num % i == 0 || num % (i + 2) == 0) {
      return false;
    }
 

  return true;
}


// Function to return the smallest
// prime number greater than N
int get_next_prime(int N)
{
  // Base case
  if (N <= 1)
    return 2;

  int prime = N;
  bool found = false;

  // Loop continuously until isPrime returns
  // true for a number greater than n
  while (!found) {
    prime++;
    if (is_prime(prime))
      found = true;
  }
  return prime;
}


void get_prim_root(llong M, VEC prime_factors, int* R_max) 
{
  int R = 1;
  bool is_prim_root = false;
  while(not is_prim_root) {
    R++;
    is_prim_root = true;
    for(int i = 0; i < int(prime_factors.size()); i++) {
       llong prime_factor = (llong)prime_factors[i];
       llong powr = (M-1)/prime_factor;
       //TODO: solve this overflow
       llong R_pow = pow(R, powr);
       if (R_pow % M == 1) {
         is_prim_root = false;
         break;
       }
    }
  }
  std::cout << "M = " << M << ", R = " << R << std::endl;
  break_point();
  *R_max = (R > *R_max) ? R : *R_max;
}


void get_lehmers(VEC primes, VEC prime_factors, llong M_old, int index, 
                  llong M_max, llong* L, int* R_max) 
{
  bool expanded_pf = false;
  for(int i = index; i < int(primes.size()); i++) 
  {
    llong M_new = (M_old-1)*primes[i]+1;
    
    /*
    std::cout << "M_new = 1 + " << M_old-1 << "*" << primes[i] 
              << " = " << M_new << std::endl; 
    */
    
    if (M_new > M_max) {
      break;
    } 
    else 
    {
      if (i != index) {
        prime_factors.push_back(primes[i]);
        expanded_pf = true;
      }
      if (is_prime(M_new)) {
        (*L)++;
        //std::cout << "  M_new=" << M_new << " is a prime" << std::endl;
        get_prim_root(M_new, prime_factors, R_max);
        //std::cout << "  R_max=" << *R_max << std::endl;
      }
      //break_point();
      get_lehmers(primes, prime_factors, M_new, i, M_max, L, R_max);
    } 
  }

  if (expanded_pf)
    prime_factors.pop_back();
  return;    
}
#endif

