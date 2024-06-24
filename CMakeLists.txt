cmake_minimum_required(VERSION 3.20)

project(main_usvfs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main_usvfs main_usvfs.cpp)
target_include_directories(main_usvfs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main_usvfs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/usvfs_x64.lib)
set_target_properties(main_usvfs PROPERTIES
 RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}
 LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR})
