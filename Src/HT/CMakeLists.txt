cmake_minimum_required(VERSION 3.0.2)
project(HT)

set(HT_src
    AppInit.cpp
    Actions/ActionError.cpp
    Actions/HelpAction.cpp
    Actions/InitAction.cpp
    Dao/DatabaseCreator.cpp
    Dao/HabitDefinitionDao.cpp
    Entity/HabitDefinitionEntity.cpp
    CommandLineParser.cpp)

add_library(${PROJECT_NAME} ${HT_src})
target_link_libraries(${PROJECT_NAME} stdc++fs Core)
