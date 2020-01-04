add_executable(LibTests
	DateTests.cpp
	FmtTests.cpp
	main.cpp 
	SqliteForeignKeyTests.cpp
)

target_link_libraries(LibTests
	Core
	date_interface
	fmt
	gmock
	gtest
	pthread
	stdc++fs
	SQLite
)

add_test(NAME LibTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND LibTests)
