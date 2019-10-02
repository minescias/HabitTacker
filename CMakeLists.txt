cmake_minimum_required(VERSION 3.11)
project(HabitTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

link_directories(${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Src)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/date/include)

# external libraries settings
# https://github.com/HowardHinnant/date/issues/474
add_compile_definitions(HAS_UNCAUGHT_EXCEPTIONS=1) # availiable after 3.12

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

add_subdirectory(Tests/CppTests)
add_subdirectory(Tests/LibTests)

# executables
add_subdirectory(Src/HT_cli)

#other
add_custom_target(Doc ALL make html WORKING_DIRECTORY ../Docs)
