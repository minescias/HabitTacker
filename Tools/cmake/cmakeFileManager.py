import os
import sys

logEnabled = False


def log(line):
    if logEnabled is True:
        print('[INFO]: ' + line)


def addFileToCmake(pathToCmake, filename, filePath=os.getcwd()):
    relFilePath = os.path.relpath(
        filePath, pathToCmake) + '/' + filename

    log('Relative file path: ' + relFilePath)

    cmakeFile = open(os.path.join(pathToCmake, "CMakeLists.txt"))
    cmakeLines = cmakeFile.readlines()
    cmakeFile.close()

    targetFound = False

    for index, line in enumerate(cmakeLines):
        if targetFound is False:
            if (line.startswith("add_library(") or
                    line.startswith("add_executable(")):
                targetFound = True
        else:
            trimmedLine = line.lstrip().rstrip()
            if relFilePath < trimmedLine:
                log("Adding file {0} before {1}".format(filename, trimmedLine))
                cmakeLines[index] = "\t{0}\n\t{1}\n".format(
                    relFilePath, trimmedLine)
                break
            elif trimmedLine == ")":
                log("Adding file {0} at the end of list".format(relFilePath))
                cmakeLines[index] = "\t{0}\n)\n".format(relFilePath)
                break

    if targetFound is False:
        print('[ERROR]: no target found in CMakeLists')
        return

    cmakeFile = open(os.path.join(pathToCmake, "CMakeLists.txt"), "w")
    cmakeFile.writelines(cmakeLines)
    cmakeFile.close()
