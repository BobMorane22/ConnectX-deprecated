#!/usr/bin/python
#coding=utf-8

import os
import sys
import getopt
import subprocess
import datetime

# Error codes:
NB_ARGUMENTS_ERROR         = 1
COMMAND_SYNTAX_ERROR       = 2
TEST_PROGRAM_ERROR         = 3
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
    
    print("Usage:")
    print("\t" + script + " OPTION\n")
    print("Options:")
    print("\t-h, --help\tPrint help.")
    print("\t-t, --tests\tTest program (full path).\n")
    print("Examples:")
    print("\t" + script + " --tests=/home/user/someTests")
    print("\t" + script + " -t /home/user/someTests")
    print("\t" + script + " -h")
    print("\t" + script + " --help")


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
    
    processus = subprocess.Popen([program], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    
    for line in processus.stdout:
        sys.stdout.write(line)
        log.write(line)
        
    log.write(guard)


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