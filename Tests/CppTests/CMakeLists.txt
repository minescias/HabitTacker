cmake_minimum_required(VERSION 3.0.2)
project(CppTests)

link_directories(${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googletest/include)

#set(BUILD_GMOCK_ON)
enable_testing()

set(CppTests_src
	LambdaTests.cpp
	RegexTests.cpp
	SmartPtrTests.cpp
	StringTests.cpp
	VariableParametersTest.cpp
	main.cpp)

# system dependent libraries
if (UNIX)
    set(SysDependencies pthread stdc++fs)
endif()

add_executable(${PROJECT_NAME} ${CppTests_src})
target_link_libraries(${PROJECT_NAME} gtest gmock ${SysDependencies})

add_test(${PROJECT_NAME} runTest)
