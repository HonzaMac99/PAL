#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "print_utils.hpp"

#define DATA_INFO 0

int* get_ints(std::string file_line);
int** get_stdin_data(int* crossings, int* streets);
int** get_file_data(std::string fname, int* towns, 
                int* district_towns, int* roads);
void or_arrays(int* array1, int* array2);
int* copy_array(int* in_array, int len);
int* zero_array(int* array1, int len);


int* get_ints(std::string file_line) {
  std::stringstream ss;
  int *number_array = new int[2]; 

  ss << file_line;

  // Check all words in the line for any ints 
  int i = 0;
  while(!ss.eof()) {
    ss >> number_array[i];
    i++;
  }
  return number_array;
}


// stores data from a stdin into a 2D array
// also stores values about the data 
int** get_stdin_data(int* crossings, int* streets) {

  std::cin >> *crossings; 
  std::cin >> *streets; 

  int **data = new int *[*streets];

  for(int i = 0; i < *streets; i++) { 
    int *num_array = new int[2];
    for(int j = 0; j < 2; j++) 
      std::cin >> num_array[j]; 
    data[i] = num_array;
  }

#if DATA_INFO 
  std::cout << std::endl;
  for(int i = 0; i < *streets; i++) {
    print_ints(data[i]);
  }
  std::cout << std::endl;
#endif

  return data;
}


// stores data from a file into a 2D array
// also stores values about the data 
int** get_file_data(std::string fname, int* crossings, int* streets) {

  std::fstream MyReadFile(fname);
  std::string fileLine;
   
  getline(MyReadFile, fileLine);
  int *params = get_ints(fileLine); 

  *crossings = params[0];  
  *streets = params[1];
  
  int **data = new int *[*streets];
  int *num_array;

  int i = 0;
  while (getline(MyReadFile, fileLine)) {
    num_array = get_ints(fileLine);
    data[i++] = num_array;
  }

#if DATA_INFO
  for(int i = 0; i < *streets; i++) {
    print_ints(data[i]);
  }
  std::cout << std::endl;
#endif

  MyReadFile.close();
  delete [] params;

  return data;
}


int* copy_array(int* in_array, int len) {
  int* out_array = new int[len];

  for(int i = 0; i < len; i++ )
    out_array[i] = in_array[i];  

  return out_array;
}


// perform or on every element of the arrays
void or_arrays(int* array1, int* array2, int len) {
  for(int i = 0; i < len; i++) {
    array1[i] = array1[i] | array2[i];
  }
}


int* zero_array(int* array1, int len) {
  std::fill(array1, array1+len, 0);
  return array1;
}
#endif


