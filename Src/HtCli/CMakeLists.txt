add_library(HtCli 
	Actions/ActionError.cpp
	Actions/ActionRegister.cpp
	Actions/AddAction.cpp
	Actions/BaseAction.cpp
	Actions/DefaultAction.cpp
	Actions/DoneAction.cpp
	Actions/EditAction.cpp
	Actions/InitAction.cpp
	Actions/ListAction.cpp
	AppInit.cpp
	AppInit/GetSettings.cpp
	AppInit/Help.cpp
	AppInit/InitDaoFactory.cpp
	AppInit/RegisterActions.cpp
	AppInit/Version.cpp
)

target_link_libraries(HtCli PRIVATE
	Core
	date_interface
	fmt
	Ht
	stdc++fs
)
