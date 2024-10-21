cmake_minimum_required(VERSION 3.0)

add_executable(test main.cpp lib-text-editor/text-editor.cpp lib-bank/bank.cpp lib-bank/bank-account.cpp)
target_link_libraries(test gtest pthread)
