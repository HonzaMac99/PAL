cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Task02) 

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(task02 task02.cpp)
add_executable(test test.cpp)

