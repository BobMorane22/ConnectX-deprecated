#!/usr/bin/python
#coding=utf-8

# TODO: script is yet incomplete!!

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