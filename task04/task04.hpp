#ifndef MAIN_LIB
#define MAIN_LIB

#include <iostream>
#include <vector>
#include <cmath>
#include "print_utils.hpp"

#define llong long long
#define ullong unsigned long long
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

  for(int i = 2; i <= sq; i++) {
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

//  
// note: originaly unsigned long changed to signed llong
llong modulo_multiplication(llong a, llong b, llong m) {
    llong a_hi = a >> 24, a_lo = a & ((1 << 24) - 1);
    llong b_hi = b >> 24, b_lo = b & ((1 << 24) - 1);
    llong result = ((((a_hi*b_hi << 16) % m) << 16) % m) << 16;
    result += ((a_lo*b_hi+a_hi*b_lo) << 24) + a_lo*b_lo;
    return result % m;
}


// due to overflowing when doing power of R to llong,
// another approach is required -> solve it dynamically
llong compute_modulo(llong M, llong R_power, int R)
{
  if (R_power == 1)
    return R;
  
  llong ret, a, b;
  if (R_power % 2 != 0) {
    a = R;
    b = compute_modulo(M, (R_power-1)/2, R);
    b = modulo_multiplication(b, b, M);
    ret = modulo_multiplication(a, b, M);
  } 
  else {
    b = compute_modulo(M, R_power/2, R);
    ret = modulo_multiplication(b, b, M);
  }

  return ret;
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
      llong R_pow = (M-1)/prime_factor;
      llong modulo, a, b;
			//print_pow(R, R_pow, M);

      if (R_pow == 1) { // only when M=3, R=2
        modulo = R;
      } 
      else if (R_pow % 2 != 0) {
        a = R;   
        b = compute_modulo(M, R_pow-1, R);
        modulo = modulo_multiplication(a, b, M);
      } 
      else {
        modulo = compute_modulo(M, R_pow, R);
      }

      if (modulo == 1) {
        is_prim_root = false;
        break;
      }
    }
  }
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
        // 281251 repeats
        // std::cout << "  M_new=" << M_new << " is a prime" << std::endl;
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

