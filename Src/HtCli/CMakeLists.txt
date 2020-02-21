add_library(HtCli 
	AppInit.cpp
	AppInit/GetSettings.cpp
	AppInit/Help.cpp
	AppInit/InitDaoFactory.cpp
	AppInit/RegisterCommands.cpp
	AppInit/Version.cpp
	Commands/AddCommand.cpp
	Commands/BaseCommand.cpp
	Commands/CommandError.cpp
	Commands/DoneCommand.cpp
	Commands/EditCommand.cpp
	Commands/CommandRegister.cpp
	Commands/InitCommand.cpp
	Commands/ListCommand.cpp
	Commands/ShowCommand.cpp
)

target_link_libraries(HtCli PRIVATE
	CLI11
	date_interface
	fmt
	nlohmann_json
	stdc++fs
	Core
	Ht
)
