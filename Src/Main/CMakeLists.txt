cmake_minimum_required(VERSION 3.0.2)
project(htr)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} HT)
