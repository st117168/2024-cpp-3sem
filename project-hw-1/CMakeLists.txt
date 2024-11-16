cmake_minimum_required(VERSION 3.0)

add_executable(test main.cpp dataset.cpp)
target_link_libraries(test gtest pthread)
