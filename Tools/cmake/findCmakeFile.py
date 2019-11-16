import os
import sys


def findCmakeFile(fullPath):
    tmpPath = fullPath

    if cmakeFileExist(tmpPath):
        return tmpPath

    while os.path.dirname(tmpPath) != '':
        if cmakeFileExist(tmpPath):
            return tmpPath
        tmpPath = goUpOneLevel(tmpPath)

    return None


def goUpOneLevel(path):
    folders = path.split(os.path.sep)
    if len(folders) == 1:
        return os.path.join('')

    tmpPath = os.path.sep.join(folders[:-1])
    return os.path.join(tmpPath)


def cmakeFileExist(path):
    return os.path.exists(os.path.join(path, "CMakeLists.txt"))
