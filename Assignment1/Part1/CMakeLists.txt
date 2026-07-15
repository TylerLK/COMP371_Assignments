# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("Assignment1_Part1")

# Add executable files
add_executable (Assignment1_Part1 "src/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Assignment1_Part1 PROPERTY CXX_STANDARD 20)
endif()