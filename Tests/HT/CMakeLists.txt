cmake_minimum_required(VERSION 3.0.2)
project(HtTests)

link_directories(${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googlemock/include)
include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googletest/include)

#set(BUILD_GMOCK_ON)
enable_testing()

set(HtTests_src
    main.cpp
    Actions/ActionRegisterTests.cpp
    Actions/AddActionTests.cpp
    Actions/DefaultActionTests.cpp
    Actions/DoneActionTests.cpp
    Actions/EditActionTests.cpp
    Actions/InitActionTests.cpp
    Actions/ListActionTests.cpp
    CommandLineParserTests.cpp
    Dao/HabitDefinitionDaoTests.cpp
    Dao/HabitDaoTests.cpp)

# system dependent libraries
if (UNIX)
    set(SysDependencies pthread stdc++fs)
endif()

add_executable(${PROJECT_NAME} ${HtTests_src})
target_link_libraries(${PROJECT_NAME} gtest gmock ${SysDependencies} HT)

add_test(${PROJECT_NAME} runTest)
