cmake_minimum_required(VERSION 3.15)
project(LCLib CXX)



set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_library(lc-c++-objects OBJECT include/lclib-c++/TypeTraits.hpp include/lclib-c++/Time.hpp include/lclib-c++/Ranges.hpp include/lclib-c++/Numerics.hpp include/lclib-c++/IOWrapper.hpp src/IOWrapper.cpp include/lclib-c++/Polymorphic.hpp include/lclib-c++/Config.hpp)
set_target_properties(lc-c++-objects PROPERTIES
        POSITION_INDEPENDENT_CODE ON)

add_library(lc-c++-shared SHARED $<TARGET_OBJECTS:lc-c++-objects>)
set_target_properties(lc-c++-shared PROPERTIES OUTPUT_NAME lc-c++
        SOVERSION 1.0.0)
add_library(lc-c++-static STATIC $<TARGET_OBJECTS:lc-c++-objects>)
set_target_properties(lc-c++-static PROPERTIES OUTPUT_NAME lc-c++)

install(TARGETS lc-c++-shared lc-c++-static EXPORT lc-c++
        BINARY DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
install(DIRECTORY include/lclib-c++ DESTINATION include)

install(EXPORT lc-c++ DESTINATION share/cmake/lc-c++)