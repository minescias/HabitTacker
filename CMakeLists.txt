cmake_minimum_required(VERSION 3.12.4)
project(HT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS YES)

add_compile_options(-Wall)
add_compile_options(-pedantic)

link_directories(${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/Src)

enable_testing()

# external libraries settings
# https://github.com/HowardHinnant/date/issues/474
add_compile_definitions(HAS_UNCAUGHT_EXCEPTIONS=1) # availiable after 3.12
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(USE_SYSTEM_TZ_DB ON CACHE BOOL "Use the operating system's timezone database")
set(ENABLE_DATE_TESTING OFF CACHE BOOL "Enable unit tests")

# external libraries
add_subdirectory(Libraries/date-2.4.1)
add_subdirectory(Libraries/fmt-6.0.0)
add_subdirectory(Libraries/googletest-1.8.1/googlemock)
add_subdirectory(Libraries/SQLite)

# libraries
add_subdirectory(Src/Core)
add_subdirectory(Src/HT)
add_subdirectory(Src/HtCli)

# tests
add_subdirectory(Tests/Core)
add_subdirectory(Tests/HT)
add_subdirectory(Tests/HtCli)

add_subdirectory(Tests/CppTests)
add_subdirectory(Tests/LibTests)

# executables
add_subdirectory(Src/HtCli_exe)

#other
add_custom_target(Doc ALL 
    make html
    WORKING_DIRECTORY ../Docs)

add_custom_target(graphviz ALL
    COMMAND ${CMAKE_COMMAND} "--graphviz=DepsGraph.dot" ..
    COMMAND dot -Tpng foo.dot -o ${CMAKE_SOURCE_DIR}/bin/DepGraph.png
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
