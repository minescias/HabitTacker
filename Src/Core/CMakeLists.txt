cmake_minimum_required(VERSION 3.0.2)
project(Core)

set(Cli_src
	Cli/CommandLineParser.cpp
	Cli/ParamProperties.cpp
	Cli/Parameters.cpp
	Cli/Validator.cpp)

set(Config_src
    Config/ConfigFile.cpp
    Config/Settings.cpp)

set(Datetime_src
	DateTime/AddDays.cpp
	DateTime/DateFormat.cpp
	DateTime/DateLiteral.cpp
	DateTime/DateTime.cpp
	DateTime/DateTimeGetter.cpp
	DateTime/Duration.cpp
	DateTime/FormatDate.cpp
	DateTime/ParseDate.cpp)

set(Database_src
	Database/Database.cpp
	Database/Dataset.cpp
	Database/Parameters.cpp
	Database/Query.cpp
	Database/Row.cpp
	Database/ValueGetter.cpp)

set(Dao_src
	Dao/DaoFactory.cpp)

set(Logger_src
	Logger/Log.cpp
	Logger/Logger.cpp)

set(Strings_src
	Strings/Case.cpp
	Strings/Compare.cpp
	Strings/Replace.cpp)

set(Misc_src
    Exceptions/LogicError.cpp
    Exceptions/RuntimeError.cpp)

add_library(${PROJECT_NAME}
    ${Cli_src}
    ${Config_src}
    ${Dao_src}
    ${Datetime_src}
    ${Database_src}
    ${Logger_src}
    ${Strings_src}
    ${Misc_src})

target_link_libraries(${PROJECT_NAME} SQLite)
