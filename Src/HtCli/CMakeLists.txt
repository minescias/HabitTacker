add_library(HtCli 
	Actions/ActionError.cpp
	Commands/CommandRegister.cpp
	Actions/AddAction.cpp
	Actions/BaseAction.cpp
	Actions/BaseCommand.cpp
	Actions/DefaultAction.cpp
	Actions/DoneAction.cpp
	Actions/EditAction.cpp
	Actions/InitAction.cpp
	Actions/ListAction.cpp
	AppInit.cpp
	AppInit/GetSettings.cpp
	AppInit/Help.cpp
	AppInit/InitDaoFactory.cpp
	AppInit/RegisterCommands.cpp
	AppInit/Version.cpp
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
