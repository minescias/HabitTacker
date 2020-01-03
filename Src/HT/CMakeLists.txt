cmake_minimum_required(VERSION 3.0.2)
project(HT)

set(HT_src
	Dao/DatabaseCreator.cpp
	Dao/HabitDao.cpp
	Dao/HabitDefinitionDao.cpp
	Dao/RequirementDao.cpp
	Entity/HabitDefinitionEntity.cpp
	Entity/HabitEntity.cpp
	Entity/Requirement.cpp)

# system dependent libraries
if (UNIX)
    set(SysDependencies stdc++fs)
endif()

add_library(${PROJECT_NAME} ${HT_src})
target_link_libraries(${PROJECT_NAME} ${SysDependencies} Core fmt date_interface)
