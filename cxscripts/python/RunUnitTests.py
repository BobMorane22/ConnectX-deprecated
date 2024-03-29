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
 # @file        RunUnitTests.py
 # @author      Eric Poirier
 # @date        November 2016
 # @version     1
 #
 # Script to run an external test program.
 #
#**************************************************************************************************#

import os
import sys
import getopt
import subprocess
import datetime

# Error codes:
NB_ARGUMENTS_ERROR         = 1
COMMAND_SYNTAX_ERROR       = 2
TESTS_HAVE_FAILED          = 3
OTHER_ERROR                = 4

# Other:
NB_ARGUMENTS_MAX            = 4

# Internal variables:
testDirectory = ""        # Directory into which the test program is located.
testProgram    = ""       # The testing program.

def printHelp():
    """
    Prints an help page.
    """
    script = os.path.basename(__file__)

    print("\nUsage:")
    print("\t" + script + " OPTION\n")
    print("Options:")
    print("\t-h, --help\tPrint help.")
    print("\t-t, --tests\tTest program (full path).")
    print("\t-l, --log\tLog file (full path),\n ")
    print("Examples:")
    print("\t" + script + " --tests=/home/user/someTests")
    print("\t" + script + " -t /home/user/someTests")
    print("\t" + script + " -t /home/user/someTests -l /home/user/log/someLogFile.log")
    print("\t" + script + " --test=/home/user/someTests --log=/home/user/log/someLogFile.log")
    print("\t" + script + " -h")
    print("\t" + script + " --help\n")


def runTests(program, logFile):
    """
    Runs an external test program (or a program, in general). The program
    output is printed to the log file passed as the second argument.

    Args:
        program    The test program to run.
        logFile    A log file for the program.
    """

    now = datetime.datetime.now()
    header = "Application: " + program + "\n"
    headerLength = len(header)
    guard = ("-" * headerLength) + "\n"

    log = open(logFile, 'w')

    log.write(guard)
    log.write(str(now) + "\n")
    log.write(header)
    log.write(guard)

    process = subprocess.Popen([program], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    for line in process.stdout:
        sys.stdout.write(line)
        log.write(line)

    log.write(guard)

    # Exit with non zero exit code if all tests have not passed:
    streamdata = process.communicate()[0]
    rc = process.returncode

    if rc != 0:
        sys.exit(TESTS_HAVE_FAILED)


def main(argv):
    """
    Runs an external test program passed as an argument. The user can also call
    for help with the following options: "-h" or "--help".

    Args:
        argv    A list containing all the arguments.
    """

    nbArguments = len(argv)

    if nbArguments != 1 and nbArguments != NB_ARGUMENTS_MAX:
        print("Error: number of arguments.")
        sys.exit(NB_ARGUMENTS_ERROR)

    if (len(argv) == 1) and (argv[0] in ("-h", "--help")):
        printHelp()
        sys.exit()

    try:
        options, arguments = getopt.gnu_getopt(argv, "t:l:", ["tests=", "log="])

    except getopt.GetoptError:
        print("Error: Arguments!")
        sys.exit(COMMAND_SYNTAX_ERROR)

    tests   = ""
    log     = ""

    for option, argument in options:

        print(option, argument)

        if option == "-t" or option == "--tests":
            tests = argument

        elif option == "-l" or option == "--log":
            log = argument

        else:
            print("Error: other")
            sys.exit(OTHER_ERROR)

    runTests(tests, log)

    print("Log file: " + log)

    sys.exit()



if __name__ == "__main__":
    main(sys.argv[1:])
