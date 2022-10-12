cmake_minimum_required(VERSION 3.10)

# set the project name
project(Random_stuff) 

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(pointers array_pointers.cpp)
add_executable(vector array_vector.cpp)
add_executable(tree tree.cpp)
