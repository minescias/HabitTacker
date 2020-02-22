add_executable(CoreTests 
	Cli/TableTests.cpp
	Config/ConfigFileTests.cpp
	Config/SettingsTests.cpp
	Dao/DaoFactoryTests.cpp
	Database/DatasetTests.cpp
	Database/ParametersTest.cpp
	Database/QueryTests.cpp
	Database/RowTests.cpp
	Database/ValueGetterTest.cpp
	DateTime/DateLiteralTests.cpp
	DateTime/FormatDateTests.cpp
	DateTime/OperatorsTests.cpp
	DateTime/ParseDateTests.cpp
	Format/DateFormatterTests.cpp
	Format/OptionalFormatterTests.cpp
	Logger/LogTests.cpp
	main.cpp
	Strings/CaseTests.cpp
	Strings/CompareTests.cpp
	Strings/ReplaceTests.cpp
	Types/DemangledTypeNameTests.cpp
	Types/IsOptionalTests.cpp
)

target_link_libraries(CoreTests 
	Core
	date_interface 
	fmt 
	gmock
	gtest
	pthread
	nlohmann_json
	stdc++fs
)

add_test(NAME CoreTests
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../build
	COMMAND CoreTests)
