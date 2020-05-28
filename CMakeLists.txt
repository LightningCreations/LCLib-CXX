cmake_minimum_required(VERSION 3.15)
project(LCLib CXX)



set(CMAKE_CXX_STANDARD_REQUIRED 17)
include_directories(include)

if(WIN32)
    set(LIBLC_CXX_SOCKET_SRC src/WinSock.hpp)
else()
    set(LIBLC_CXX_SOCKET_SRC src/PosixSocket.cpp src/PosixDSO.cpp)
endif()


add_library(lc-c++ OBJECT include/lclib-c++/TypeTraits.hpp include/lclib-c++/Ranges.hpp include/lclib-c++/Numerics.hpp include/lclib-c++/IOWrapper.hpp src/IOWrapper.cpp include/lclib-c++/Polymorphic.hpp include/lclib-c++/Config.hpp include/lclib-c++/Sockets.hpp
        ${LIBLC_CXX_SOCKET_SRC} include/lclib-c++/Dynamic.hpp include/lclib-c++/Version.hpp
        src/Version.cpp)
set_target_properties(lc-c++ PROPERTIES
        POSITION_INDEPENDENT_CODE ON)

if(NOT WIN32)
target_link_libraries(lc-c++ dl)
endif()

add_library(lc-c++-shared SHARED $<TARGET_OBJECTS:lc-c++>)
set_target_properties(lc-c++-shared PROPERTIES OUTPUT_NAME lc-c++
        SOVERSION 1.0.0)
add_library(lc-c++-static STATIC $<TARGET_OBJECTS:lc-c++>)
set_target_properties(lc-c++-static PROPERTIES OUTPUT_NAME lc-c++)

install(TARGETS lc-c++-shared lc-c++-static EXPORT lc-c++
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
install(DIRECTORY include/lclib-c++ DESTINATION include)

install(EXPORT lc-c++ DESTINATION share/cmake/lc-c++)