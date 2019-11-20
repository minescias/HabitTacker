cmake_minimum_required(VERSION 3.11.0)
project(LibTests)

link_directories(${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googletest/include)

# https://github.com/HowardHinnant/date/issues/474
add_compile_definitions(HAS_UNCAUGHT_EXCEPTIONS=1) # availiable after 3.12


#set(BUILD_GMOCK_ON)
enable_testing()

set(LibTests_src
	DateTests.cpp
	FmtTests.cpp
	SqliteForeignKeyTests.cpp)

# system dependent libraries
if (UNIX)
    set(SysDependencies pthread stdc++fs)
endif()

add_executable(${PROJECT_NAME} main.cpp ${LibTests_src})
target_link_libraries(${PROJECT_NAME} gtest gmock fmt ${SysDependencies} Core)

add_test(NAME ${PROJECT_NAME}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND ${PROJECT_NAME})
