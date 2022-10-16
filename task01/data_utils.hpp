#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <fstream>
#include <sstream>

#define PRINT_INFO 1 

void print_ints(int* ints);
int* get_ints(std::string file_line);
int** get_data(std::string fname, int* towns, 
                int* district_towns, int* roads);
void swap_arrays(int* array1, int* array2);
void sort_array(int** in_array, int array_len);
int* or_arrays(int* array1, int* array2);
int* copy_array(int* in_array, int len);
int* zero_array(int* array1, int len);


void print_ints(int* ints) {
  std::cout << ints[0] <<" "<< ints[1] <<" "<< ints[2] << std::endl;
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


// stores data from a file into a 2D array
// also stores values about the data 
int** get_data(std::string fname, int* towns, int* districts, int* roads) {

  std::fstream MyReadFile(fname);
  std::string fileLine;
   
  getline(MyReadFile, fileLine);
  int *params = get_ints(fileLine); 

  *towns = params[0];  
  *districts = params[1];
  *roads = params[2];
  
  int **data = new int *[*roads];
  int *num_array = new int[3];

  int i = 0;
  while (getline(MyReadFile, fileLine)) {
    num_array = get_ints(fileLine);
    data[i++] = num_array;
  }

#if PRINT_INFO
  for(int i = 0; i < *roads; i++) {
    print_ints(data[i]);
  }
  std::cout << std::endl;
#endif

  MyReadFile.close();
  return data;
}


void swap_arrays(int* array1, int* array2) {
  int tmp;
  for(int i = 0; i < 3; i++) {
    tmp = array1[i];
    array1[i] = array2[i];
    array2[i] = tmp;
  }
}


// selection sort (slow)
// TODO: quick/merge/heap sort??
// sort array by the cost of the 3rd element 
void sort_array(int** in_array, int array_len) {
  for(int i = 0; i < array_len; i++) {
    int arr_rest_min = in_array[i][2]; 
    int min_idx = i;
    for(int j = i+1; j < array_len; j++) {
      if (in_array[j][2] < arr_rest_min) {
        arr_rest_min = in_array[j][2];
        min_idx = j;
      }
    }
    if (min_idx != i)
      swap_arrays(in_array[i], in_array[min_idx]);
  }

#if PRINT_INFO
  for(int i = 0; i < array_len; i++) 
    print_ints(in_array[i]);
  std::cout << std::endl;
#endif
}


// perform or on every element of the arrays
int* or_arrays(int* array1, int* array2, int len) {
  int* or_array = new int[len];

  for(int i = 0; i < len; i++) {
    or_array[i] = array1[i] | array2[i];
  }

  return or_array;
}


// TODO: check the memory management if necessary
int* copy_array(int* in_array, int len) {
  int* out_array = new int[len];

  for(int i = 0; i < len; i++ )
    out_array[i] = in_array[i];  

  return out_array;
}


int* zero_array(int* array1, int len) {
  for(int i = 0; i < len; i++)
    array1[i] = 0;

  return array1;
}

#endif
