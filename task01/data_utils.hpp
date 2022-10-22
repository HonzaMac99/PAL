#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "print_utils.hpp"

#define DATA_INFO 0

int* get_ints(std::string file_line);
int** get_stdin_data(int* towns, int* districts, int* roads);
int** get_file_data(std::string fname, int* towns, 
                int* district_towns, int* roads);
void swap_arrays(int* array1, int* array2);
void sort_array(int** in_array, int array_len);
void or_arrays(int* array1, int* array2);
int* copy_array(int* in_array, int len);
int* zero_array(int* array1, int len);


int* get_ints(std::string file_line) {
  std::stringstream ss;
  int *number_array = new int[3]; 

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
int** get_stdin_data(int* towns, int* districts, int* roads) {

  std::cin >> *towns; 
  std::cin >> *districts; 
  std::cin >> *roads;

  int **data = new int *[*roads];

  for(int i = 0; i < *roads; i++) { 
    int *num_array = new int[3];
    for(int j = 0; j < 3; j++) 
      std::cin >> num_array[j]; 
    data[i] = num_array;
  }

#if DATA_INFO 
  std::cout << std::endl;
  for(int i = 0; i < *roads; i++) {
    print_ints(data[i]);
  }
  std::cout << std::endl;
#endif

  return data;
}


// stores data from a file into a 2D array
// also stores values about the data 
int** get_file_data(std::string fname, int* towns, int* districts, int* roads) {

  std::fstream MyReadFile(fname);
  std::string fileLine;
   
  getline(MyReadFile, fileLine);
  int *params = get_ints(fileLine); 

  *towns = params[0];  
  *districts = params[1];
  *roads = params[2];
  
  int **data = new int *[*roads];
  int *num_array;

  int i = 0;
  while (getline(MyReadFile, fileLine)) {
    num_array = get_ints(fileLine);
    data[i++] = num_array;
  }

#if DATA_INFO
  for(int i = 0; i < *roads; i++) {
    print_ints(data[i]);
  }
  std::cout << std::endl;
#endif

  MyReadFile.close();
  delete [] params;

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




// part in the quick sort algorithm
int partition(int** arr, int start, int end)
{
 
    int pivot = arr[start][2];
 
    int count_var = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i][2] <= pivot)
            count_var++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count_var;
    swap_arrays(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i][2] <= pivot) {
            i++;
        }
 
        while (arr[j][2] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap_arrays(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 

// quick sort (fast)
void quickSort(int** arr, int start, int end)
{
 
    // base case
    if (start >= end)
        return;
 
    // partitioning the array
    int p = partition(arr, start, end);

    // Sorting the left part
    quickSort(arr, start, p - 1);
 
    // Sorting the right part
    quickSort(arr, p + 1, end);

#if DATA_INFO
    for(int i = 0; i < end; i++) 
        print_ints(arr[i]);
    std::cout << std::endl;
#endif
}


// TODO: check the memory management if necessary
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


