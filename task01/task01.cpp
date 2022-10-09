#include <iostream>
#include <fstream>
#include <sstream>
#include "task01.hpp"

int* get_ints(std::string file_line) {
  std::stringstream ss;
  std::string word;
  int *number_array = new int(3); 
  // int found;

  ss << file_line;

  /* Check all words in the line for any ints */
  int i = 0;
  while(!ss.eof()) {
    ss >> number_array[i];
    i++;
  }
  return number_array;
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
  int* params = get_ints(fileLine); 
  std::cout << params[0] <<" "<< params[1] <<" "<< params[2] << std::endl;
  std::cout << std::endl;

  int T = params[0];  // T <= 250 k
  int D = params[1];  // D <=   2 k
  int R = params[2];  // R <= 450 k  
  // 0 < Edge_cost <= 250

  int* closed_nodes = new int(T);
  
  while (getline(MyReadFile, fileLine)) {
    // Output the text from the file
    int* num_array = get_ints(fileLine);
    std::cout << num_array[0] <<" "<< num_array[1] <<" "<< num_array[2] << std::endl;
    std::cout << std::endl;
  }

  // Close the file
  MyReadFile.close();

  return 0;
}
