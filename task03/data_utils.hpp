#ifndef DATA_LIB
#define DATA_LIB

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "print_utils.hpp"

#define VEC vector<int>
#define VEC_2D vector<vector<int>>

#define DATA_INFO 0

int* get_ints(std::string file_line);
void get_stdin_data(VEC* old_network_adj, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network_adj, int* n_servers, int* n_connections, 
                      int** new_network_con, int* fast_servers, int* n_fast_servers);
void get_file_data(std::string fname, 
                    VEC* old_network_adj, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network_adj, int* n_servers, int* n_connections, 
                      int** new_network_con, int* fast_servers, int* n_fast_servers);
void or_arrays(int* array1, int* array2);
int* copy_array(int* in_array, int len);
int* zero_array(int* array1, int len);


int* get_ints(std::string file_line, int quant) {
  std::stringstream ss;
  int *number_array = new int[quant]; 

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
void get_stdin_data(VEC* old_network_adj, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network_adj, int* n_servers, int* n_connections, 
                      int** new_network_con, int* fast_servers, int* n_fast_servers)
{

  std::cin >> *n_old_servers; 
  std::cin >> *n_old_connections; 

  old_network_adj = new VEC[*n_old_connections];

  int server1, server2;
  for(int i = 0; i < *n_old_connections; i++) 
  { 
    std::cin >> server1 >> server2; 
    old_network_adj[server1].push_back(server2);
  }

  std::cin >> *n_servers; 
  std::cin >> *n_connections; 
  std::cin >> *n_fast_servers; 

  fast_servers = new int[*n_fast_servers];

  for(int i = 0; i < *n_fast_servers; i++) 
  {
    std::cin >> fast_servers[i]; 
  }

  new_network_adj = new VEC[*n_servers];
  new_network_con = new int*[*n_connections];

  for(int i = 0; i < *n_connections; i++) 
  { 
    int* new_con = new int[3];

    // new_server1, new_server2, cost; 
    std::cin >> new_con[0] >> new_con[1] >> new_con[2]; 
    new_network_adj[new_con[0]].push_back(new_con[1]);
    new_network_con[i] = new_con;
  }

#if DATA_INFO 
  print_adj_list(old_network_adj, *n_old_servers);
  for(int i = 0; i < *n_fast_servers; i++) {
    std::cout << fast_servers[i] << " ";
  }
  std::cout << std::endl;
  print_adj_list(new_network_adj, *n_servers);
  for(int i = 0; i < *n_connections; i++) {
    std::cout << new_network_con[i][0] << " "
              << new_network_con[i][1] << " "
              << new_network_con[i][2] << std::endl;
  }
#endif
}


// stores data from a file into a 2D array
// also stores values about the data 
void get_file_data(std::string fname, 
                    VEC* old_network_adj, int* n_old_servers, int* n_old_connections, 
                     VEC* new_network_adj, int* n_servers, int* n_connections, 
                      int** new_network_con, int* fast_servers, int* n_fast_servers)
{
  std::ifstream MyReadFile(fname);
  std::stringstream ss;
  std::string fileLine;
   
  getline(MyReadFile, fileLine);
  ss << fileLine;

  ss >> *n_old_servers; 
  ss >> *n_old_connections;

  old_network_adj = new VEC[*n_old_servers];

  int server1, server2;
  for(int i = 0; i < *n_old_connections; i++) 
  { 
    std::stringstream ss2;
    getline(MyReadFile, fileLine);
    ss2 << fileLine;

    ss2 >> server1 >> server2; 
    old_network_adj[server1].push_back(server2);
  }

  std::stringstream ss3;
  getline(MyReadFile, fileLine);
  ss3 << fileLine;

  ss3 >> *n_servers;
  ss3 >> *n_connections;
  ss3 >> *n_fast_servers; 

  fast_servers = new int[*n_fast_servers];

  std::stringstream ss4;
  getline(MyReadFile, fileLine);
  ss4 << fileLine;

  for(int i = 0; i < *n_fast_servers; i++) {
    ss4 >> fast_servers[i];
  }

  new_network_adj = new VEC[*n_servers];
  new_network_con = new int*[*n_connections];

  for(int i = 0; i < *n_connections; i++) 
  { 
    getline(MyReadFile, fileLine);
    int* new_con = get_ints(fileLine, 3);

    new_network_adj[new_con[0]].push_back(new_con[1]);
    new_network_con[i] = new_con;
  }

#if DATA_INFO 
  print_adj_list(old_network_adj, *n_old_servers);
  for(int i = 0; i < *n_fast_servers; i++) {
    std::cout << fast_servers[i] << " ";
  }
  std::cout << std::endl;
  print_adj_list(new_network_adj, *n_servers);
  for(int i = 0; i < *n_connections; i++) {
    std::cout << new_network_con[i][0] << " "
              << new_network_con[i][1] << " "
              << new_network_con[i][2] << std::endl;
  }
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


