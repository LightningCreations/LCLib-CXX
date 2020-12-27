include_directories(../include)

function(add_compile_test name)
    add_library(
            ${name}
            STATIC EXCLUDE_FROM_ALL
            ${name}.cpp
    )
    target_link_libraries(${name} PRIVATE lc-c++)
    add_test(NAME ${name}
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${name} --config $<CONFIGURATION>
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )
endfunction()

function(add_unit_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE)
    add_test(NAME ${name}
        COMMAND ${name}
    )
endfunction()

add_subdirectory(version)
add_subdirectory(type_traits)
add_subdirectory(dynamic_array)