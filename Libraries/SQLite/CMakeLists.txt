cmake_minimum_required(VERSION 3.0.2)
project(SQLite)

set(SQLite_src
    sqlite3.c)

add_library(${PROJECT_NAME} SHARED ${SQLite_src})
target_link_libraries(${PROJECT_NAME} pthread dl)