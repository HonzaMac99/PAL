#include <iostream>
#include <fstream>
#include <sstream>
#include "task01.hpp"

#define MAX_T 250000
#define MAX_D 2000
#define MAX_R 450000


void print_ints(int* ints) {
  std::cout << ints[0] <<" "<< ints[1] <<" "<< ints[2] << std::endl;
  // std::cout << std::endl;
}


int* get_ints(std::string file_line) {
  std::stringstream ss;
  std::string word;
  int *number_array = new int[3]; 

  ss << file_line;

  /* Check all words in the line for any ints */
  int i = 0;
  while(!ss.eof()) {
    ss >> number_array[i];
    i++;
  }
  return number_array;
}


void swap_arrays(int* array1, int* array2) {
  int* tmp_array = new int[3];
  for(int i = 0; i < 3; i++) {
    tmp_array[i] = array1[i];
    array1[i] = array2[i];
    array2[i] = tmp_array[i];
  }
}


// custom selection sort
int** sort_array(int** in_array, int array_len) {
  for(int i = 0; i < array_len; i++) {
    int arr_rest_min = in_array[i][2]; 
    int min_idx = i;
    for(int j = i; j < array_len; j++) {
      if (in_array[j][2] < arr_rest_min) {
        arr_rest_min = in_array[j][2];
        min_idx = j;
      }
    }
    swap_arrays(in_array[i], in_array[min_idx]);
  }
  return in_array;
}


int main(int argc, char* argv[])
{
  // Read from the text file
  std::string file_name = "/home/honzamac/PAL/task01/datapub/pub01.in";
  if (argc > 1) 
    file_name = argv[1];

  std::fstream MyReadFile(file_name);
  std::string fileLine;
   
  getline(MyReadFile, fileLine);
  int *params = get_ints(fileLine); 

  // 0 < Edge_cost <= 250
  // For any district town D′ other than D
  // rd(T, D) ≤ rd(T, D′), and
  // rd(T, D) = rd(T, D′) implies id(D) < id(D′).
  int T = params[0];  // T <= 250 k
  int D = params[1];  // D <=   2 k
  int R = params[2];  // R <= 450 k  
  
  // START: store the input data
  int **data = new int *[R];
  int *num_array = new int[3];

  int i = 0;
  while (getline(MyReadFile, fileLine)) {
    num_array = get_ints(fileLine);
    // print_ints(num_array);
    data[i++] = num_array;
  }

  // Algorithm structure
  for(int i = 0; i < R; i++) {
    print_ints(data[i]);
  }

  int **sorted_data = new int *[R];
  sorted_data = sort_array(data, R);
  std::cout << std::endl;

  for(int i = 0; i < R; i++) {
    print_ints(sorted_data[i]);
  }

  // END procedures
  MyReadFile.close();

  delete [] num_array;

  return 0;
}
