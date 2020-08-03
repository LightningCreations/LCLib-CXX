cmake_minimum_required(VERSION 3.15)
project(LCLib CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_20 _pos)
if(_pos LESS 0)
    set(CMAKE_CXX_STANDARD 17)
else()
    set(CMAKE_CXX_STANDARD 20)
endif()
endif()
message(STATUS "Building lclib-c++ for c++${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(LIBLC_CXX_SOCKET_SRC src/WinSock.cpp src/WinDLL.cpp)
else()
    set(LIBLC_CXX_SOCKET_SRC src/PosixSocket.cpp src/PosixDSO.cpp)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_definitions($<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebugInfo>>:LCLIB_CXX_DEBUG>)

add_library(lc-c++-objects OBJECT include/lclib-c++/TypeTraits.hpp include/lclib-c++/Ranges.hpp include/lclib-c++/Numerics.hpp include/lclib-c++/IOWrapper.hpp src/IOWrapper.cpp include/lclib-c++/Polymorphic.hpp include/lclib-c++/Config.hpp include/lclib-c++/Sockets.hpp
        ${LIBLC_CXX_SOCKET_SRC} include/lclib-c++/Dynamic.hpp include/lclib-c++/Version.hpp
        src/Version.cpp include/lclib-c++/BinaryIOHelpers.hpp
        include/lclib-c++/Time.hpp)
set_target_properties(lc-c++-objects PROPERTIES
        POSITION_INDEPENDENT_CODE ON)
target_include_directories(lc-c++-objects PUBLIC include)

if(NOT WIN32)
target_link_libraries(lc-c++-objects dl)
endif()

add_library(lc-c++-shared SHARED $<TARGET_OBJECTS:lc-c++-objects>)
set_target_properties(lc-c++-shared PROPERTIES OUTPUT_NAME lc-c++
        SOVERSION 1.0.0)
add_library(lc-c++-static STATIC $<TARGET_OBJECTS:lc-c++-objects>)
if(NOT WIN32)
set_target_properties(lc-c++-static PROPERTIES OUTPUT_NAME lc-c++)
else()
set_target_properties(lc-c++-static PROPERTIES OUTPUT_NAME lc-c++_static)
endif()

install(TARGETS lc-c++-static lc-c++-shared)


if(NOT LIBLC_CXX_LINK_SHARED)
    add_library(lc-c++ ALIAS lc-c++-static)
else()
    add_library(lc-c++ ALIAS lc-c++-shared)
endif()

option(LIBLC_CXX_BUILD_TESTS "Build the lclib-c++ test suite" ON)

if(LIBLC_CXX_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(DIRECTORY include/lclib-c++ TYPE INCLUDE)
