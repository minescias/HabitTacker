from pathlib import Path

def generateCMake(argv):
	projectName = argv[2]
	testProject = False

	if len(argv) == 4:
		if argv[3] == "test":
			testProject = True

	ensureFileDoesNotExitsts("CMakeLists.txt")
	cmakeFile = open("CMakeLists.txt", "w")
	cmakeFile.write("cmake_minimum_required(VERSION 3.0.2)\n")
	cmakeFile.write("project(" + projectName + ")\n")
	cmakeFile.write("\n")

	if testProject:
		cmakeFile.write("link_directories(${CMAKE_SOURCE_DIR}/bin)\n")
		cmakeFile.write("include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googlemock/include)\n")
		cmakeFile.write("include_directories(${CMAKE_SOURCE_DIR}/Libraries/googletest-1.8.1/googletest/include)\n")
		cmakeFile.write("\n")

	cmakeFile.write("set(" + projectName + "_src)\n")
	cmakeFile.write("\n")

	if testProject:
		cmakeFile.write("# system dependent libraries\n")
		cmakeFile.write("if (UNIX)\n")
		cmakeFile.write("	set(SysDependencies pthread stdc++fs)\n")
		cmakeFile.write("endif()\n")
		cmakeFile.write("\n")

	if testProject:
		cmakeFile.write("add_executable(${PROJECT_NAME} ${CppTests_src})\n")
		cmakeFile.write("target_link_libraries(${PROJECT_NAME} gtest gmock ${SysDependencies})\n")
		cmakeFile.write("add_test(${PROJECT_NAME} runTest)\n")
	else:
		cmakeFile.write("add_library(${PROJECT_NAME} ${" + projectName + "_src})\n")

	cmakeFile.close()


def ensureFileDoesNotExitsts(filename):
	config = Path(filename)
	if config.is_file():
		exit("File " + filename + " already exists")
