cmake_minimum_required(VERSION 3.0.0)
project(A-star-algorithm VERSION 0.1.0)

add_executable(A-star-algorithm src/main.cpp)

target_link_libraries(A-star-algorithm SDL2main SDL2 GL)