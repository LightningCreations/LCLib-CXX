project(LCLib CXX)
cmake_minimum_required(VERSION 3.15)


set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_library(LCLib SHARED include/lclib-c++/TypeTraits.hpp include/lclib-c++/Time.hpp include/lclib-c++/Ranges.hpp include/lclib-c++/Numerics.hpp include/lclib-c++/IOWrapper.hpp src/IOWrapper.cpp include/lclib-c++/Polymorphic.hpp)
