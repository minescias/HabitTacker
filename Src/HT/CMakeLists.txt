cmake_minimum_required(VERSION 3.0.2)
project(HT)

set(HT_Actions_src
    Actions/ActionRegister.cpp
    Actions/ActionError.cpp
    Actions/AddAction.cpp
    Actions/DefaultAction.cpp
    Actions/DoneAction.cpp
    Actions/InitAction.cpp
    Actions/ListAction.cpp)

set(HT_src
    AppInit.cpp
    AppInit/DaoFactoryInitializer.cpp
    AppInit/GetSettings.cpp
    AppInit/Help.cpp
    AppInit/Version.cpp
    Dao/DaoFactory.cpp
    Dao/DatabaseCreator.cpp
    Dao/HabitDao.cpp
    Dao/HabitDefinitionDao.cpp
    Entity/HabitDefinitionEntity.cpp
    Entity/HabitEntity.cpp
    Cli/CommandLineParser.cpp)

# system dependent libraries
if (UNIX)
    set(SysDependencies stdc++fs)
endif()

add_library(${PROJECT_NAME} ${HT_src} ${HT_Actions_src})
target_link_libraries(${PROJECT_NAME} ${SysDependencies} Core)
