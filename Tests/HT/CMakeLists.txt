add_executable(HtTests 
	Dao/HabitDaoTests.cpp
	Dao/HabitDefinitionDaoTests.cpp
	Dao/RequirementDaoTests.cpp
	main.cpp
)

target_link_libraries(HtTests
	Core
	date_interface
	fmt
	gmock
	gtest
	Ht
	pthread
	stdc++fs
)

add_test(NAME HtTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND HtTests)