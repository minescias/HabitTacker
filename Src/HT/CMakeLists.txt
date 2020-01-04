add_library(Ht 
	Dao/DatabaseCreator.cpp
	Dao/HabitDao.cpp
	Dao/HabitDefinitionDao.cpp
	Dao/RequirementDao.cpp
	Entity/HabitDefinitionEntity.cpp
	Entity/HabitEntity.cpp
	Entity/Requirement.cpp
)
target_link_libraries(Ht PRIVATE
	Core
	date_interface
	fmt
	stdc++fs
)
