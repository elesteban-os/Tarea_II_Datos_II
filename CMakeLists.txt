cmake_minimum_required(VERSION 3.21)

set(testingProject)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMALE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)



add_subdirectory(test)