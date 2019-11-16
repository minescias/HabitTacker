from cmake.findCmakeFile import findCmakeFile
from cmake.cmakeFileManager import addFileToCmake
from detail.genCpp import generateTest
import os
import sys

sys.path.append("../")


def aksToAddFileToCmake(filename):
    cwd = os.getcwd()
    cmakeFilePath = findCmakeFile(cwd)

    if cmakeFilePath is None:
        return

    print("CMakeLists.txt found at {0}.".format(cmakeFilePath))
    print("add {0} file to CMakeLists.txt? (Y/n)".format(filename))
    answer = input()

    if answer != "" and answer != "Y" and answer != "y":
        return

    addFileToCmake(cmakeFilePath, filename + ".cpp")


def askToAddTests(filename):
    cwd = os.getcwd()
    testPath = cwd.replace("Src", "Tests")
    filePathWithoutExtension = "{0}/{1}Tests".format(testPath, filename)

    print("Add test file in {0}.cpp? (Y/n)".format(filePathWithoutExtension))
    answer = input()

    if answer != "" and answer != "Y" and answer != "y":
        return

    generateTest(filePathWithoutExtension)
    testCmakePath = findCmakeFile(testPath)

    if testCmakePath is None:
        return

    addFileToCmake(testCmakePath, filename + "Tests.cpp")
