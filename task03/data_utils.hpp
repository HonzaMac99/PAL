#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "print_utils.hpp"

#define VEC vector<int>
#define VEC_2D vector<vector<int>>

#define DATA_INFO 1

int* get_ints(std::string file_line);
void get_stdin_data(VEC* old_network, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network, int* n_servers, int* n_connections, 
                      int* fast_network_ids, int* n_fast_servers);
void get_file_data(std::string fname, 
                    VEC* old_network, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network, int* n_servers, int* n_connections, 
                      int* fast_network_ids, int* n_fast_servers);
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
void get_stdin_data(VEC* old_network, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network, int* n_servers, int* n_connections, 
                      int* fast_servers, int* n_fast_servers) {

  std::cin >> *n_old_servers; 
  std::cin >> *n_old_connections; 

  old_network = new VEC[*n_old_connections];

  int server1, server2;
  for(int i = 0; i < *n_old_connections; i++) { 
    std::cin >> server1; 
    std::cin >> server2; 
    old_network[server1].push_back(server2);
  }

  std::cin >> *n_servers; 
  std::cin >> *n_connections; 
  std::cin >> *n_fast_servers; 

  fast_servers = new int[*n_fast_servers];

  for(int i = 0; i < *n_fast_servers; i++) {
    std::cin >> fast_servers[i]; 
  }

  for(int i = 0; i < *n_connections; i++) { 
    std::cin >> server1; 
    std::cin >> server2; 
    new_network[server1].push_back(server2);
  }

#if DATA_INFO 
  print_adj_list(old_network, *n_old_connections);
  for(int i = 0; i < *n_fast_servers; i++) {
    std::cout << fast_servers[i] << " ";
  }
  std::cout << std::endl;
  print_adj_list(new_network, *n_connections);
#endif
}


// stores data from a file into a 2D array
// also stores values about the data 
void get_file_data(std::string fname, 
                    VEC* old_network, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network, int* n_servers, int* n_connections, 
                      int* fast_servers, int* n_fast_servers) {

  std::ifstream MyReadFile(fname);
  std::stringstream ss;
  std::string fileLine;
   
  getline(MyReadFile, fileLine);
  ss << fileLine;
  ss >> *n_old_servers >> *n_old_connections;

  old_network = new VEC[*n_old_servers];

  int server1, server2;
  for(int i = 0; i < *n_old_connections; i++) { 
    getline(MyReadFile, fileLine);
    std::stringstream ss2;
    ss2 << fileLine;
    ss2 >> server1 >> server2; 
    old_network[server1].push_back(server2);
  }


  getline(MyReadFile, fileLine);
  std::stringstream ss3;
  ss3 << fileLine;
  ss3 >> *n_servers >> *n_connections >> *n_fast_servers; 

  fast_servers = new int[*n_fast_servers];

  getline(MyReadFile, fileLine);
  std::stringstream ss4;
  ss4 << fileLine;
  for(int i = 0; i < *n_fast_servers; i++) {
    ss4 >> fast_servers[i];
  }

  int cost;
  new_network = new VEC[*n_servers];
  
  // while (getline(MyReadFile, fileLine)) {
  for(int i = 0; i < *n_connections; i++) { 
    getline(MyReadFile, fileLine);
    std::stringstream ss5;
    ss5 << fileLine;
    ss5 >> server1 >> server2 >> cost; 
    new_network[server1].push_back(server2);
  }

#if DATA_INFO 
  print_adj_list(old_network, *n_old_connections);
  for(int i = 0; i < *n_fast_servers; i++) {
    std::cout << fast_servers[i] << " ";
  }
  std::cout << std::endl;
  print_adj_list(new_network, *n_connections);
#endif

  MyReadFile.close();
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


