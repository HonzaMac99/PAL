cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Task02) 

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(task02 task02.cpp)

enable_testing()
add_test(NAME Runs COMMAND task02 -f)

function(do_test target arg result)
  add_test(NAME Comp<${arg}> COMMAND ${target} ${arg})
  set_tests_properties(Comp<${arg}>
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# do a bunch of result based tests
foreach(i RANGE 1 9) 
  #message(STATUS "I=${i}")
  file(READ "./datapub/pub0${i}.out" outStringRef)
  do_test(task02 "../datapub/pub0${i}.in" ${outStringRef}) 
endforeach()

file(READ "./datapub/pub10.out" outStringRef)
do_test(task02 "../datapub/pub10.in" ${outStringRef}) 


