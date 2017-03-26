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


import os
import shutil
import sys

from os.path import isdir
from os.path import isfile
from os.path import exists


# Error codes:
ERROR_NB_ARGS               = 1
ERROR_SYNTAX                = 2
ERROR_COPY_A_FILE           = 3
ERROR_COPY_FILES            = 4
ERROR_COPY_A_TREE           = 5
ERROR_OTHER                 = 6

# Other:
ALL_GOOD                    = 0
MAX_NB_ARGS                 = 4


def printHelp():

    script = os.path.basename(__file__)
    
    print("SYNOPSIS:")
    print("\t" + script + " [-h | --help] [[OPTION] SRC... DEST]\n")
    
    print("OPTION:")
    print("\t-t, --tree\tCopy whole tree from SRC to DEST. DEST must not previously exist.\n")
    
    print("EXAMPLES:")
    print("\t" + script + " /home/user/someFile /home/user/someOtherFile")
    print("\t" + script + " /home/user/someFile /home/user/someDirectory")
    print("\t" + script + " /home/user/someFile /home/user/someOtherFile /home/user/someDirectory")
    print("\t" + script + " -t /home/user/someTreeDirectory /home/user/someOtherDirectory")
    print("\t" + script + " -h")
    print("\t" + script + " --help")

    
def createCopy(p_source, p_destination, p_isTree):

    # Tree:
    if p_isTree == True and isdir(p_source) and isdir(p_destination) and not exists(p_destination):
        shutil.copytree(p_source, p_destination)
        sys.exit(ALL_GOOD)

    # One file copy:
    elif len(p_source) == 1 and isfile(p_source):
        shutil.copy2(p_source, p_destination)
        sys.exit(ALL_GOOD)

    # Multiple files copy to same location:
    elif len(p_source) > 1 and isdir(p_destination):

        allSourcesAreFiles = True

        for source in p_source:
            if not isfile(source):
                allSourcesAreFiles = False
                sys.exit(ERROR_COPY_A_FILE)

        if allSourcesAreFiles:
            for source in p_source:
                shutil.copy2(source, p_destination)
                sys.exit(ALL_GOOD)

    # All other options have failed...
    else:
        sys.exit(ERROR_OTHER)


def main(argv):
    print("Bob")
    #TODO: Populate main function.
    #TODO: Add argument parsing.


if __name__ == "__main__":
    main(sys.argv[1:])