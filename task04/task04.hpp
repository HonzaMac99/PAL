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
#define MAX_D 40

int* get_prime_factors();
bool is_prime(int num);
bool is_prime(int num, int* n_array);
void get_lehmers(llong M_max, int D, int* primes, int* L, int* R_max);


// get all primes that are not larger than maximal value of D 
int* get_prime_factors()
{
  int* numbers = new int[MAX_D+1];

  std::fill(numbers, numbers+MAX_D+1, 1);

  int sq = sqrt(MAX_D);

  for(int i = 2; i < sq; i++) {
    if(numbers[i]) {
      for(int j = pow(i, 2); j <= MAX_D; j+=i) {
        numbers[j] = 0;
      }
    }
  }

  // VEC primes;
  // for(int i = 0; i <= MAX_D; i++) {
  //   if (numbers[i] and i >= 2) 
  //     primes.push_back(i);
  // }
  // delete [] numbers;
  // return primes;
  
  return numbers;
}


bool is_prime(int num) 
{
  // Corner cases
  if (num <= 1)  
    return false;
  else if (num <= 3)  
    return true;
 
  // This is checked so that we can skip 
  // middle five numbers in below loop
  if (num % 2 == 0 || num % 3 == 0) 
    return false;
 
  for (int i = 5; i*i <= num; i+=6)
    if (num % i == 0 || num % (i + 2) == 0)
      return false;
 
  return true;
}


bool is_prime(int num, int* primes_array) 
{
  if (num <= MAX_D) {
    return primes_array[num];
  } 
  else {
    return is_prime(num);
  }
}


// Function to return the smallest
// prime number greater than N
int get_next_prime(int N, int* primes)
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
    if (is_prime(prime, primes))
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


int get_lehmers(llong M_max, int D, int* prime_factors, int* L, int* R_max, int index)
{
<<<<<<< HEAD
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
  //TODO: maybe just get the 0/1 array of all numbers

=======
  int ret =    
>>>>>>> c8364b251ceefc4dcde97ef870730e1c512fc749

}


#endif


