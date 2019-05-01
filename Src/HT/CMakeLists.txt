cmake_minimum_required(VERSION 3.0.2)
project(HT)

set(HT_src
    AppInit.cpp
    Actions/ActionError.cpp
    Actions/AddAction.cpp
    Actions/HelpAction.cpp
    Actions/InitAction.cpp
    Actions/ListAction.cpp
    Dao/DatabaseCreator.cpp
    Dao/HabitDefinitionDao.cpp
    Entity/HabitDefinitionEntity.cpp
    Entity/HabitEntity.cpp
    CommandLineParser.cpp)

# system dependent libraries
if (UNIX)
    set(SysDependencies stdc++fs)
endif()

add_library(${PROJECT_NAME} ${HT_src})
target_link_libraries(${PROJECT_NAME} ${SysDependencies} Core)
