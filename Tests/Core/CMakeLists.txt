cmake_minimum_required(VERSION 3.0.2)
project(CoreTests)

link_directories(${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googletest/include)

#set(BUILD_GMOCK_ON)
enable_testing()

set(CoreTests_src
	Config/ConfigFileTests.cpp
	Config/SettingsTests.cpp
	Database/DatasetTests.cpp
	Database/QueryTests.cpp
	Database/RowTests.cpp
	Database/ValueGetterTest.cpp
	DateTime/DateLiteralTests.cpp
	DateTime/DateTimeTests.cpp
	DateTime/DurationTests.cpp
	Strings/FormatTests.cpp
	Utils/Strings/CaseTests.cpp
	Utils/Strings/CompareTests.cpp
	Utils/Strings/ReplaceTests.cpp
	main.cpp)

# system dependent libraries
if (UNIX)
    set(SysDependencies pthread stdc++fs)
endif()

add_executable(${PROJECT_NAME} ${CoreTests_src})
target_link_libraries(${PROJECT_NAME} gtest gmock ${SysDependencies} Core)

add_test(${PROJECT_NAME} runTest)
