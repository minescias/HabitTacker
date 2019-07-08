import os
import sys
from collections import namedtuple

GroupInfo = namedtuple("Groupinfo", "fileList startIndex endIndex")


def addFileToCmake(pathToCmake, filename):
    cmakeFile = open(os.path.join(pathToCmake, "CMakeLists.txt"))
    cmakeLines = cmakeFile.readlines()
    cmakeFile.close()

    sourceFileGropus = getSourceFileGroups(cmakeLines)

    print("Select group to add file '" + filename +
          "' or type name to create new. Type q to exit.")

    for i in range(len(sourceFileGropus)):
        print(str(i) + ": " + sourceFileGropus[i])

    userInput = input()
    if userInput.isnumeric():
        groupId = int(userInput)
        if groupId < 0 or len(sourceFileGropus)-1 < groupId:
            sys.exit("Incorrect group number")

        addFileToGroup(pathToCmake, cmakeLines,
                       filename, sourceFileGropus[groupId])
    elif userInput == "q":
        sys.exit()
    else:
        sys.exit("Not implemented yet")


def getSourceFileGroups(cmakeLines):
    groups = []
    for line in cmakeLines:
        if isGroupDeclaration(line.rstrip()) is True:
            groups.append(line.rstrip()[4:])

    return list(filter(None, groups))


def isGroupDeclaration(line):
    return line.startswith("set(") is True and line.endswith("_src") is True


def addFileToGroup(pathToCmake, cmakeLines, filename, groupName):
    groupInfo = getGroupInfo(cmakeLines, groupName)

    pathToAddedFile = os.path.join(os.getcwd(), filename)
    commonPath = os.path.commonpath([pathToCmake, pathToAddedFile])

    groupInfo.fileList.append(os.path.relpath(pathToAddedFile, commonPath))
    groupInfo.fileList.sort()

    writreGroupToFile(cmakeLines, pathToCmake, groupName, groupInfo)


def getGroupInfo(cmakeLines, groupName):
    startIndex = None
    endIndex = None
    files = []

    for i in range(len(cmakeLines)):
        trimedLine = cmakeLines[i].lstrip().rstrip()
        if startIndex is not None:
            if trimedLine.endswith(")"):
                files.append(trimedLine[:-1])
                endIndex = i
                break

            files.append(trimedLine)

        if trimedLine.startswith("set(" + groupName):
            startIndex = i

    return GroupInfo(files, startIndex, endIndex)


def writreGroupToFile(cmakeLines, pathToCmake, groupName, groupInfo):
    groupStr = "set(" + groupName

    for file in groupInfo.fileList:
        groupStr = groupStr + "\n\t" + file

    groupStr = groupStr + ")\n"

    cmakeFile = open(os.path.join(pathToCmake, "CMakeLists.txt"), "w")
    cmakeFile.writelines(cmakeLines[:groupInfo.startIndex])
    cmakeFile.write(groupStr)
    cmakeFile.writelines(cmakeLines[groupInfo.endIndex+1:])
    cmakeFile.close()
