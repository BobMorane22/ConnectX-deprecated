#!/usr/bin/python
#coding=utf-8

#***************************************************************************************************
 # 
 # Copyright (C) 2016 Connect X team
 #
 # This file is part of Connect X.
 #
 # Connect X is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # Connect X is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with Connect X.  If not, see <http://www.gnu.org/licenses/>.
 #
#**************************************************************************************************#

#***************************************************************************************************
 # @file        CreateCopy.py
 # @author      Eric Poirier
 # @date        May 2017
 # @version     1
 #
 # Script to copy an existing file into an existing directory.
 #
#**************************************************************************************************#
import os
import shutil
import sys

from os.path import isdir
from os.path import isfile
from os.path import exists

from sys     import exit
from shutil  import copy2


# Error codes:
ERROR_COPY               = 1
ERROR_NOT_ENOUGH_ARGS    = 2
ERROR_TOO_MANY_ARGUMENTS = 3
ERROR_COMMAND_SYNTAX     = 4

#Other:
EXEC_OK = 0


def printHelp():
    """
    Prints an help page.
    """

    script = os.path.basename(__file__)
    
    print("\nSYNOPSIS:")
    print("\t" + script + " [-h | --help] [SRC DEST]\n")
    
    print("\tDEST must be a previously existing directory.\n")
    
    print("OPTION:")
    print("\t-h, --help\tPrint usage.\n")
    
    print("EXAMPLES:")
    print("\t" + script + " /home/user/someFile /home/user/someDirectory/")
    print("\t" + script + " -h")
    print("\t" + script + " --help\n")
    print("\tNote that in the first example, \"/home/user/someDirectory/\"")
    print("\talready existed before the script was called. Also, the paths")
    print("\t can be relative.")
    

    
def createCopy(p_source, p_destination):
    """
    Copies an existing file into an existing directory.
    
    Args:
        p_source         The path to the file to copy.
        p_destination    The path to the directory into which to copy the file.
    """

    if isfile(p_source) and isdir(p_destination):
        copy2(p_source, p_destination)
        exit(EXEC_OK)

    else:
        if not isfile(p_source):
            print("Error: " + p_source + " is either not a file or does not exist.")
            
        if not isdir(p_destination):
            print("Error: " + p_destination + " is not a directory.")
            
        exit(ERROR_COPY)


def main(argv):
    """
    Copies an existing file into an existing directory.. The user can also call 
    for help with the following options: "-h" or "--help".
    
    Args:
        argv    A list containing all the arguments.
    """

    nbArguments = len(argv)
    
    # Called without arguments:
    if nbArguments == 0:
        print("Error: not enough arguments.")
        exit(ERROR_NOT_ENOUGH_ARGS)

    # Help requested:
    if (nbArguments == 1) and (argv[0] in ("-h", "--help")):
        printHelp()
        exit(EXEC_OK)

    # File copy:
    if nbArguments == 2:
        createCopy(argv[0], argv[1])
        
    # Too many arguments:
    if nbArguments >= 3:
        print("Error: too many arguments.")
        exit(ERROR_TOO_MANY_ARGUMENTS)

    try:
        options, arguments = getopt.gnu_getopt(argv, "t", ["tree="])

    except getopt.GetoptError:
        script = os.path.basename(__file__)
        print("Error: command syntax error. Type " + script + " -h or " + script + "--help to see usage.")
        exit(ERROR_COMMAND_SYNTAX)


if __name__ == "__main__":
    main(sys.argv[1:])