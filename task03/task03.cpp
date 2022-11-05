#include <iostream>
#include <algorithm>
#include "task03.hpp"
#include "data_utils.hpp"
#include "print_utils.hpp"
#include "node.hpp"

#define VEC vector<int>
#define VEC_2D vector<vector<int>>

#define PRINT 1



int main(int argc, char* argv[])
{
  // Read the input from file or stdin
  std::string file_name;
  int stdin_input = 1;
  if (argc > 1) {
    file_name = argv[1];
    if (file_name == "-f")
      file_name = "/home/honzamac/PAL/task03/datapub/pub01.in";
    stdin_input = 0;
  }
    
  int n_old_servers, n_old_connections;
  int n_servers, n_connections, n_fast_servers;
  int *fast_servers;
  int **new_net_con;
  VEC *old_network, *new_network;
  if (stdin_input) {
    get_stdin_data(old_network, &n_old_servers, &n_old_connections, 
                     new_network, &n_servers, &n_connections, 
                       new_net_con, fast_servers, &n_fast_servers);
  }
  else {
    get_file_data(file_name, 
                    old_network, &n_old_servers, &n_old_connections, 
                      new_network, &n_servers, &n_connections, 
                        new_net_con, fast_servers, &n_fast_servers);
  }

  std::cout << "0 0" << std::endl;

  return 0;
}
