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

target_include_directories(HtTests PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME HtTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND HtTests)