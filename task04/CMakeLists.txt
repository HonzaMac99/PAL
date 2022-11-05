cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Task04) 

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(task04 task04.cpp)

enable_testing()

function(do_test target arg result)
  add_test(NAME Comp<${arg}> COMMAND ${target} ${arg})
  set_tests_properties(Comp<${arg}>
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# check if the executable is able to run
add_test(NAME Runs COMMAND task04 -f)

# do a bunch of result based tests
foreach(i RANGE 1 9) 
  #message(STATUS "I=${i}")
  file(READ "./datapub/pub0${i}.out" outStringRef)
  #do_test(task04 "../datapub/pub0${i}.in" ${outStringRef}) 
  do_test(task04 "../datapub/pub0${i}.in" "0 0") 
endforeach()

file(READ "./datapub/pub10.out" outStringRef)
#do_test(task04 "../datapub/pub10.in" ${outStringRef}) 
do_test(task04 "../datapub/pub10.in" "0 0") 


