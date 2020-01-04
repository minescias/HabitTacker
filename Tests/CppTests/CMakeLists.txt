add_executable(CppTests 
	ForLoopTests.cpp
	LambdaTests.cpp
	main.cpp
	RegexTests.cpp
	SmartPtrTests.cpp
	StringTests.cpp
	TypeTraitsTests.cpp
	VariableParametersTest.cpp
)

target_link_libraries(CppTests 
	pthread
	stdc++fs
	gtest
	gmock
	date_interface
)

add_test(NAME CppTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND CppTests)