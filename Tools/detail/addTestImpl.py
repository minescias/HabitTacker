import os

from cmake.cmakeFileManager import addFileToCmake
from cmake.findCmakeFile import findCmakeFile
from detail.genCpp import generateTest


def addTestsImpl(filename):
    testPath = os.getcwd().replace("Src", "Tests")
    testFileName = "{0}Tests".format(os.path.splitext(filename)[0])

    testCmakePath = findCmakeFile(testPath)
    if testCmakePath is None:
        pritn('No CMakeLists.txt found for {0}'.format(testPath))
        return

    print('CMakeLists found at {0}'.format(testCmakePath))
    print("Add test file in {0}/{1}.cpp? (Y/n)".format(testPath, testFileName))
    answer = input()

    if answer != "" and answer != "Y" and answer != "y":
        return

    generateTest(testFileName, testPath)
    addFileToCmake(testCmakePath, testFileName + ".cpp", testPath)
