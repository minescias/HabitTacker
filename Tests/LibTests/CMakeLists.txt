add_executable(LibTests
	DateTests.cpp
	FmtTests.cpp
	main.cpp 
	Sqlite_returnIdOfInsertedObject.cpp
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

target_include_directories(LibTests PRIVATE ${CMAKE_SOURCE_DIR})

add_test(NAME LibTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND LibTests)
