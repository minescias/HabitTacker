cmake_minimum_required(VERSION 3.0.2)
project(HT)

set(HT_src
    AppInit.cpp)

add_library(${PROJECT_NAME} ${HT_src})
# target_link_libraries(${PROJECT_NAME} SQLite)
