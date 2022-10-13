cmake_minimum_required(VERSION 3.10)

# set the project name
project(Cpp_tutorials) 

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(array_pointers array_pointers.cpp)
add_executable(vector vector.cpp)
add_executable(tree tree.cpp)
add_executable(lambda lambda.cpp)
