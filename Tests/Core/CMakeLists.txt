cmake_minimum_required(VERSION 3.0.2)
project(CoreTests)

link_directories(${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.0/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.0/googletest/include)

#set(BUILD_GMOCK_ON)
enable_testing()

set(CoreTests_src
    main.cpp
    Database/DatasetTests.cpp
    Database/QueryTests.cpp
    Utils/Strings/CaseTests.cpp
    Utils/Strings/CompareTests.cpp
    Utils/Strings/ReplaceTests.cpp)

add_executable(${PROJECT_NAME} ${CoreTests_src})
target_link_libraries(${PROJECT_NAME} gtest gmock pthread Core)

add_test(${PROJECT_NAME} runTest)
