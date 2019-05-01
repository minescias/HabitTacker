cmake_minimum_required(VERSION 3.0.2)
project(HabitTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_directories(${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Src)

# external libraries
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(Libraries/googletest-1.8.1/googlemock)
add_subdirectory(Libraries/SQLite)

# libraries
add_subdirectory(Src/Core)
add_subdirectory(Src/HT)

# tests
add_subdirectory(Tests/Core)
add_subdirectory(Tests/HT)

# executables
add_subdirectory(Src/Main)
