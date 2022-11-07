#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <cmath>
#include "print_utils.hpp"

#define llong long long
#define VEC vector<llong>
#define VEC_2D vector<vector<llong>>

#define PRINT_INFO 0

VEC eratosthenes(int max_n);
void get_lehmers(llong M_max, int D, llong* L, int* R_max);


// get all primes that are not larger than max_n
VEC eratosthenes(int max_n) 
{
  int* numbers = new int[max_n+1];
  std::fill(numbers, numbers+max_n+1, 1);

  int sq = sqrt(max_n);

  for(int i = 2; i < sq; i++) {
    if(numbers[i]) {
      for(int j = pow(i, 2); j <= max_n; j+=i) {
        numbers[j] = 0;
      }
    }
  }

  VEC primes;
  for(int i = 0; i <= max_n; i++) {
    if (numbers[i] and i >= 2) 
      primes.push_back(i);
  }
  delete [] numbers;
  return primes;
}


bool is_prime(int n) 
{
  // Corner cases
  if (n <= 1)  
    return false;
  else if (n <= 3)  
    return true;
 
  // This is checked so that we can skip 
  // middle five numbers in below loop
  if (n % 2 == 0 || n % 3 == 0) 
    return false;
 
  for (int i = 5; i*i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
 
  return true;
}


bool is_prime(int n, int* n_array, int size) 
{
  if (n < size) {
    return n_array[n];
  } 
  else {
    return is_prime(n);
  }
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


int get_next_pf(llong M, llong pf) {
  int next_pf = get_next_prime(pf);
  while(M%next_pf != 0) {
    next_pf = get_next_prime(next_pf);
    if(pow(next_pf,2) > M) 
      return 0;
  }
  return next_pf;
}


llong get_primitive_root(llong M, VEC pf) 
{
  llong R = 2; // root
  int is_root = 0; 
  while(not is_root) {
    is_root = 1;
    for(int i = 0; i < (int)pf.size(); i++) {
      llong cond = (llong)pow(R, (M-1)/pf[i])%M;
      if(cond == 1) {
        is_root = 0;
        R++;
        break;
      }
    }
  }

  return R;
}


void generate_modulos(VEC primes, llong M_max, int* L, int* R_max) {

}


void get_lehmers(llong M_max, int D, int* L, int* R_max) {


  VEC primes = eratosthenes(D);
  //TODO: maybe get just the 0/1 array of all numbers


  *L = M_max*0;
  *R_max = D*0;
}


#endif


