cmake_minimum_required(VERSION 3.10)
project(tfhello)

set(CMAKE_CXX_STANDARD 14)

link_libraries(tfhe-spqlios-avx)

#link_libraries(HEAAN)

link_libraries(ntl)


link_libraries(pthread)

aux_source_directory(src SRC_DIR)

include_directories(src)

add_executable(main main.cpp ${SRC_DIR})