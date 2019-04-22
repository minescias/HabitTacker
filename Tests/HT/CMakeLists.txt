cmake_minimum_required(VERSION 3.0.2)
project(HtTests)

link_directories(${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.0/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.0/googletest/include)

#set(BUILD_GMOCK_ON)
enable_testing()

set(HtTests_src
    main.cpp
    Actions/InitActionTests.cpp
    CommandLineParserTests.cpp
    Dao/HabitDefinitionDaoTests.cpp)

add_executable(${PROJECT_NAME} ${HtTests_src})
target_link_libraries(${PROJECT_NAME} gtest gmock pthread stdc++fs HT)

add_test(${PROJECT_NAME} runTest)
