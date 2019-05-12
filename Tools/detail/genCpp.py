import os
import re

from pathlib import Path

def generateClass(className):
	print("Namespace name: = ", end='')
	namespace = input()
	generateHeaderFile(className, className, namespace)
	generateSourceFile(className, className, namespace)

def generateFile(filename):
	print("Namespace name: = ", end='')
	namespace = input()
	generateHeaderFile(filename, "", namespace)
	generateSourceFile(filename, "", namespace)

def generateTest(testName):
	generateTestFile(testName)

def generateHeaderFile(filename, className, namespace):
	ensureFileDoesNotExitsts(filename + ".h")
	headerFile = open(filename + ".h" ,"w")
	includeGuard = getIncludeGuardFromClassName(filename)
	headerFile.write("#ifndef " + includeGuard + "\n")
	headerFile.write("#define " + includeGuard + "\n")
	headerFile.write("\n")

	if namespace:
		headerFile.write("namespace " + namespace + "\n")
		headerFile.write("{\n")

	headerFile.write("\n")

	if className:

		headerFile.write("class " + className + "\n")
		headerFile.write("{\n")
		headerFile.write("public:\n")
		headerFile.write("\t" + className + "();\n")
		headerFile.write("};\n")
		headerFile.write("\n")

	if namespace:
		headerFile.write("} // namespace " + namespace + "\n")

	headerFile.write("\n")
	headerFile.write("#endif // " + includeGuard + "\n")
	headerFile.close()

def generateSourceFile(filename, className, namespace):
	ensureFileDoesNotExitsts(filename + ".cpp")
	srcFile = open(filename + ".cpp" ,"w")
	srcFile.write("#include \"" + getRelativeIncludePatch(filename) + "\"\n")
	srcFile.write("\n")

	if namespace:
		srcFile.write("namespace " + namespace + "\n")
		srcFile.write("{\n")
		srcFile.write("\n")

	if className:
		srcFile.write(className + "::" + className + "()\n")
		srcFile.write("{\n")
		srcFile.write("}\n")
		srcFile.write("\n")

	if namespace:
		srcFile.write("} // namespace " + namespace + "\n")

	srcFile.close()

def generateTestFile(testName):
	ensureFileDoesNotExitsts(testName + ".cpp")
	srcFile = open(testName + ".cpp" ,"w")
	srcFile.write("#include <gmock/gmock.h>\n")
	srcFile.write("\n")

	srcFile.write("namespace Tests\n")
	srcFile.write("{\n")
	srcFile.write("\n")
	srcFile.write("using namespace testing;\n")
	srcFile.write("\n")

	srcFile.write("class " + testName + " : public testing::Test\n")
	srcFile.write("{\n")
	srcFile.write("public:\n")
	srcFile.write("\t" + testName + "(){};\n")
	srcFile.write("};\n")
	srcFile.write("\n")

	srcFile.write("} // namespace Tests\n")

	srcFile.close()

def getIncludeGuardFromClassName(className):
	return "__" + re.sub( '(?<!^)(?=[A-Z])', '_', className).upper() + "_H"

def getRelativeIncludePatch(className):
	path = os.path.dirname(os.path.realpath(className + ".h"))
	path = path + "/" + className + ".h"
	mainDirectory = "Src/"

	return path[path.find(mainDirectory) + len(mainDirectory):]

def ensureFileDoesNotExitsts(filename):
	config = Path(filename)
	if config.is_file():
		exit("File " + filename + " already exists")
