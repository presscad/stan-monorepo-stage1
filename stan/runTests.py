#!/usr/bin/python

"""
replacement for runtest target in Makefile
"""

import os
import os.path
import platform
import sys
import subprocess
import time
import imp

mathRunTestPath = os.path.abspath(os.path.join(os.path.dirname(__file__), '../math/runTests.py'))
mathRunTests = imp.load_source('runTests', mathRunTestPath)

# set up good makefile target name
def mungeName(name):
    if (name.startswith("src")):
        name = name.replace("src/","",1)
    if (name.endswith(mathRunTests.testsfx)):
        name = name.replace(mathRunTests.testsfx,"_test")
        if (mathRunTests.isWin()):
            name += mathRunTests.winsfx
            name = name.replace("\\","/")
    return name


def main():
    mathRunTests.mungeName = mungeName
    mathRunTests.main()


if __name__ == "__main__":
    main()
