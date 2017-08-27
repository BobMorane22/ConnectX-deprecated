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
 # @file        GenerateLibraryStructure.py
 # @author      Eric Poirier
 # @date        July 2017
 # @version     1
 #
 # Generates the library structure required by the Connect X project on disc. Run this script 
 # instead of creating the directories and files yourself to enforce uniformity among libraries.
 #
#**************************************************************************************************#

import os
import sys
import getpass
import time
import datetime


NB_ARGUMENTS = 2

# Codes d'execution:
EXEC_OK                              = 0
ERROR_NB_ARGUMENTS                   = 1
ERROR_PATH_DOES_NOT_EXIST            = 2
ERROR_LIB_NAME_INVALID               = 3
ERROR_DIRECTORY_ALREADY_EXISTS       = 4
ERROR_LIB_MAKEFILE_NOT_CREATED       = 5
ERROR_UNITTESTS_MAKEFILE_NOT_CREATED = 6
ERROR_DOXYGEN_MAKEFILE_NOT_CREATED   = 7
ERROR_TEST_MAIN_FILE_NOT_CREATED     = 8
ERROR_DOXYFILE_NOT_CREATED           = 9
ERROR_DOXYINTRO_NOT_CREATED          = 10


# Classes:
class HeaderInformation:
    """
    Utility data structure holding information about comments' 
    headers.
    
    Members:
        userName: The username as defined by the USER environment 
                  variable (*NIX systems).
        date:     The date at which the structure is constructed in 
                  the form \"Month, AAAA\".
    """

    def __init__(self):
        """
        Data structure constructor.
        
        Args:
            self: The data structure about to be constructed.
        """
        self.userName = getpass.getuser()
        
        year  = datetime.datetime.now().year
        month = time.strftime("%B")
        date  = month + ", " + str(year)
        
        self.date = date



def printHelp():
    """
    Prints an help page.
    """
    
    script = os.path.basename(__file__)
    
    print("\nSYNOPSIS:")
    print("\t" + script + " [-h | --help] DEST LIBNAME\n")
    
    print("\tDEST    : A previously existing directory.\n")
    print("\tLIBNAME : The library name for which we want to generate the structure.")
    
    print("OPTION:")
    print("\t-h, --help\tPrint usage.\n")
    
    print("EXAMPLES:")
    print("\t" + script + " /home/user/someDirectory/ cxfoo")
    print("\t" + script + " /home/user/someDirectory/ cXfOo")
    print("\t" + script + " -h")
    print("\t" + script + " --help\n")
    print("\tNote that in the two first examples, \"/home/user/someDirectory/\"")
    print("\talready existed before the script was called. The paths can be")
    print("\trelative. Furthermore, the library name\'s case is not important.")
    print("\tIt will always be brought down to lowercase. However, characters")
    print("\tmust be alphanumeric.")



def fixPath(p_path):
    """
    Appends a foward slash to the path if needed. This ensures a consistent 
    syntax across the script.

    Args:
        p_path: The path to fix.
        
    Returns:
        The path with a forward slash at the end.
    """
    # We make sure the given path respects the needed syntax,
    # that is, it ends with a forward slash:
    if not p_path.endswith("/"):
        goodPath = p_path + '/'
    else:
        goodPath = p_path

    return goodPath



def libNameToLowerCase(p_capturedLibName):
    """
    Transforms the library name specified by the user to lowercase.

    Args:
        p_capturedLibName: The library name as specified by the user.

    Return:
        The library name in lowercase.
    """

    return p_capturedLibName.lower()



def generateDirectoryStructure(p_path, p_libName):
    """
    Generates the directory structure needed to host the library's source 
    files, its unit tests files and its documentation's source and output.
    
    Args:
        p_path:    The path on disc where to create the library structure.
        p_libName: The name of the library (in lowercase).
    """

    fullPath = p_path + p_libName + '/'

    directories = [
        fullPath + "src",
        fullPath + "include",
        fullPath + "test/unit",
        fullPath + "doc/doxygen",
        fullPath + "doc/doxygen/examples",
        fullPath + "doc/doxygen/uml",
        fullPath + "doc/external",
        fullPath + "tools"
        ]

    # We also check not to overwrite anything:
    for directory in directories:
        if os.path.exists(directory):
            print ("The directory " + directory + " already exists!\n")
            sys.exit(ERROR_DIRECTORY_ALREADY_EXISTS)

    # All clear, we can start creating the structure:
    for directory in directories:
        os.makedirs(directory)



def generateLibraryMakefile(p_path, p_libName, p_headerInfo):
    """
    Generates the Makefile necessary to build the (static) library.
    
    Args:
        p_path:    The path on disc where to create the library structure.
        p_libName: The name of the library (in lowercase).
    """

    makefilePath = p_path + p_libName + "/Makefile"
    makefile = open(makefilePath, "w+")

    makefile.write("#--------------------------------------------------------------------------------------------------#\n"  )
    makefile.write("#\n"                                                                                                     )
    makefile.write("# @file    Makefile\n"                                                                                   )
    makefile.write("# @author  " + p_headerInfo.userName + "\n"                                                              )
    makefile.write("# @date    " + p_headerInfo.date + "\n"                                                                  )
    makefile.write("# @version 1\n"                                                                                          )
    makefile.write("#\n"                                                                                                     )
    makefile.write("# This makefile defines how " + p_libName + " should be built. The following\n"                          )
    makefile.write("# build step is done from here:\n"                                                                       )
    makefile.write("#\n"                                                                                                     )
    makefile.write("#    1. Build lib" + p_libName + ".a\n"                                                                  )
    makefile.write("#\n"                                                                                                     )
    makefile.write("# To use this makefile, you need at least these tools installed on your\n"                               )
    makefile.write("# machine:\n"                                                                                            )
    makefile.write("#\n"                                                                                                     )
    makefile.write("#    1. GNU make (tested with)\n"                                                                        )
    makefile.write("#    2. gcc compiler (g++ is used)\n"                                                                    )
    makefile.write("#\n"                                                                                                     )
    makefile.write("#--------------------------------------------------------------------------------------------------#\n\n")

    makefile.write("# Compiler:\n"                                                                                           )
    makefile.write("CPPFLAGS             = $(OPT_FLAGS) $(DEBUG_FLAGS) $(NO_LINKER_FLAGS) $(STANDARD_FLAGS) \\\n"            )
    makefile.write("                       $(WARN_AS_ERRORS_FLAGS)\n\n"                                                                          )

    makefile.write("# Source files, headers, etc.:\n"                                                                        )
    makefile.write("MAKEFILE_LOC = $(CX_SRC_ROOT)/" + p_libName + "\n"                                                       )
    makefile.write("OBJ_DIR      = $(CX_BUILD_ROOT)/connectx\n"                                                              )
    makefile.write("OUT_DIR      = $(CX_BUILD_ROOT)/connectx\n"                                                              )
    makefile.write("LIBS_OUT     = $(CX_BUILD_ROOT)/connectx/libs\n"                                                         )
    makefile.write("INCLUDES     = -I$(MAKEFILE_LOC)/src -I$(MAKEFILE_LOC)/include\n"                                        )
    makefile.write("VPATH        = src\n\n"                                                                                  )

    makefile.write("SRCS     = \\\n"                                                                                         )

    makefile.write("OBJS     = $(OBJ_DIR)/\\\n"                                                                              )

    makefile.write("LIBS =\n\n"                                                                                              )

    makefile.write("# Build output:\n\n"                                                                                     )

    makefile.write("# Product:\n"                                                                                            )
    makefile.write("MAIN = lib" + p_libName + ".a # static library\n\n\n"                                                    )


    makefile.write("all: make_dir $(MAIN)\n"                                                                                 )
    makefile.write("\t@echo $(MAIN) has been compiled!\n\n"                                                                  )

    makefile.write("$(MAIN): $(OBJS)\n"                                                                                      )
    makefile.write("\t@echo Invoquing GCC Archiver...\n"                                                                     )
    makefile.write("\tar -r $(LIBS_OUT)/$(MAIN) $(OBJS)\n"                                                                   )
    makefile.write("\t@echo Static library $(MAIN) created!\n\n"                                                             )

    makefile.write("$(OBJ_DIR)/%.o: %.cpp\n"                                                                                 )
    makefile.write("\t@echo Invoquing GCC...\n"                                                                              )
    makefile.write("\t$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@\n"                                                         )
    makefile.write("\t@echo Object files created!\n\n"                                                                       )

    makefile.write("make_dir:\n"                                                                                             )
    makefile.write("\tmkdir -p $(OBJ_DIR)\n"                                                                                 )
    makefile.write("\tmkdir -p $(LIBS_OUT)\n\n"                                                                              )

    makefile.write("clean:\n"                                                                                                )
    makefile.write("\t@echo Removing object files...\n"                                                                      )
    makefile.write("\t$(RM) $(OBJ_DIR)/*.o\n"                                                                                )
    makefile.write("\t@echo Object files removed!\n\n"                                                                       )

    makefile.write("mrproper:\n"                                                                                             )
    makefile.write("\t@echo Cleaning project...\n"                                                                           )
    makefile.write("\t$(RM) $(OBJ_DIR)/*.o\n"                                                                                )
    makefile.write("\t$(RM) $(OUT_DIR)/$(MAIN)\n"                                                                            )
    makefile.write("\t@echo Project cleaned!\n\n"                                                                            )

    makefile.write("depend: $(SRCS)\n"                                                                                       )
    makefile.write("\t@echo Finding dependencies...\n"                                                                       )
    makefile.write("\tmakedepend $(INCLUDES) $^\n"                                                                           )
    makefile.write("\t@echo Dependencies found!\n\n"                                                                         )

    if not os.path.exists(makefilePath):
        print("Error: The library makefile was not created!")
        sys.exit(ERROR_LIB_MAKEFILE_NOT_CREATED)



def generateTestMakefile(p_path, p_libName, p_headerInfo):
    """
    Generates the Makefile necessary to build the library's unit tests 
    executable.
    
    Args:
        p_path:     The path on disc where to create the structure.
        p_libName:  The name of the library (in lowercase).
    """

    makefilePath = p_path + p_libName + "/test/Makefile"
    makefile = open(makefilePath, "w+")

    makefile.write("#--------------------------------------------------------------------------------------------------#\n"  )
    makefile.write("#\n"                                                                                                     )
    makefile.write("# @file    Makefile\n"                                                                                   )
    makefile.write("# @author  " + p_headerInfo.userName + "\n"                                                              )
    makefile.write("# @date    " + p_headerInfo.date + "\n"                                                                  )
    makefile.write("# @version 1\n"                                                                                          )
    makefile.write("#\n"                                                                                                     )
    makefile.write("# This makefile defines how the unit tests for " + p_libName + " are built.\n"                           )
    makefile.write("#\n"                                                                                                     )
    makefile.write("# To use this makefile, you need at least these tools installed on your\n"                               )
    makefile.write("# machine:\n"                                                                                            )
    makefile.write("#\n"                                                                                                     )
    makefile.write("#    1. GNU make (tested with)\n"                                                                        )
    makefile.write("#    2. gcc compiler (g++ is used)\n"                                                                    )
    makefile.write("#    3. Google Tests\n"                                                                                  )
    makefile.write("#\n"                                                                                                     )
    makefile.write("#--------------------------------------------------------------------------------------------------#\n\n")

    makefile.write("# Compiler:\n"                                                                                           )
    makefile.write("CPPFLAGS = $(OPT_FLAGS) $(DEBUG_FLAGS) $(STANDARD_FLAGS) \\\n"                                           )
    makefile.write("           $(WARN_AS_ERRORS_FLAGS)\n\n"                                                                  )

    makefile.write("# Source files, headers, etc.:\n"                                                                        )
    makefile.write("OBJ_DIR      = $(CX_BUILD_ROOT)/tests/unit\n"                                                            )
    makefile.write("OUT_DIR      = $(CX_BUILD_ROOT)/tests/unit\n"                                                            )
    makefile.write("INCLUDES     = -I$(CX_SRC_ROOT)/" + p_libName + "\n"                                                     )
    makefile.write("LIBINCLUDES  = -L$(CX_BUILD_ROOT)/connectx/libs\n"                                                       )
    makefile.write("VPATH        = unit\n\n"                                                                                )

    makefile.write("SRCS      = " + p_libName + "Test.cpp\\\n\n"                                                            )

    makefile.write("OBJS      =\n\n"                                                                                         )

    makefile.write("OBJS := $(addprefix $(OBJ_DIR)/,$(OBJS))\n"                                                              )
    makefile.write("\n"                                                                                                      )
    makefile.write("LIBS      = -lgtest\\\n"                                                                                 )
    makefile.write("            -lgtest_main\\\n"                                                                            )
    makefile.write("            -lpthread\\\n"                                                                               )
    makefile.write("            -l" + p_libName + "\n\n"                                                                     )

    makefile.write("# Product:\n"                                                                                            )
    makefile.write("MAIN = " + p_libName + "Test.out\n\n"                                                                   )

    makefile.write("all: make_dir make_log $(MAIN)\n\n"                                                                      )

    makefile.write("$(MAIN): $(OBJS)\n"                                                                                      )
    makefile.write("\t@echo Invoquing GCC...\n"                                                                              )
    makefile.write("\t$(CPPC) $(LIBINCLUDES) -o $(OUT_DIR)/$(MAIN) $(OBJS) $(LIBS)\n"                                        )
    makefile.write("\t@echo $(MAIN) has been compiled and linked!\n\n"                                                       )

    makefile.write("$(OBJ_DIR)/%.o: %.cpp\n"                                                                                 )
    makefile.write("\t@echo Invoquing GCC...\n"                                                                              )
    makefile.write("\t$(CPPC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@\n"                                                         )
    makefile.write("\t@echo Object files created!\n\n"                                                                       )

    makefile.write("make_dir:\n"                                                                                             )
    makefile.write("\tmkdir -p $(OBJ_DIR)\n"                                                                                 )
    makefile.write("\tmkdir -p $(OUT_DIR)\n\n"                                                                               )

    makefile.write("make_log:\n"                                                                                             )
    makefile.write("\tmkdir -p $(OUT_DIR)/log\n"                                                                             )
    makefile.write("\ttouch $(OUT_DIR)/log/" + p_libName + "UnitTests.log\n\n"                                                 )

    makefile.write("clean:\n"                                                                                                )
    makefile.write("\t@echo Removing object files...\n"                                                                      )
    makefile.write("\t$(RM) $(OBJ_DIR)/*.o\n"                                                                                )
    makefile.write("\t@echo Object files removed!\n\n"                                                                       )

    makefile.write("mrproper: clean\n"                                                                                       )
    makefile.write("\t@echo Cleaning project...\n"                                                                           )
    makefile.write("\t$(RM) $(OUT_DIR)/$(MAIN)\n"                                                                            )
    makefile.write("\t@echo Project cleaned!\n\n"                                                                            )

    makefile.write("depend: $(SRCS)\n"                                                                                       )
    makefile.write("\t@echo Finding dependencies...\n"                                                                       )
    makefile.write("\tmakedepend $(INCLUDES) $^\n"                                                                           )
    makefile.write("\t@echo Dependencies found!\n\n"                                                                         )

    makefile.close()

    if not os.path.exists(makefilePath):
        print("Error: The unit tests makefile was not created!")
        sys.exit(ERROR_UNITTESTS_MAKEFILE_NOT_CREATED)



def generateDoxygenMakefile(p_path, p_libName, p_headerInfo):
    """
    Generates the Makefile necessary to build the library's Doxygen
    documentation.

    Args:
        p_path:    The path on disc where to create the library structure.
        p_libName: The name of the library (in lowercase).
    """

    makefilePath = p_path + p_libName + "/doc/Makefile"
    makefile = open(makefilePath, "w+")

    makefile.write("#--------------------------------------------------------------------------------------------------#\n")
    makefile.write("#\n"                                                                                                   )
    makefile.write("# @file    Makefile\n"                                                                                 )
    makefile.write("# @author  " + p_headerInfo.userName + "\n"                                                            )
    makefile.write("# @date    " + p_headerInfo.date + "\n"                                                                )
    makefile.write("# @version 1\n"                                                                                        )
    makefile.write("#\n"                                                                                                   )
    makefile.write("# This makefile defines how the " + p_libName + " documentation is built.\n"                           )
    makefile.write("#\n"                                                                                                   )
    makefile.write("# To use this makefile, you need at least these tools installed on your\n"                             )
    makefile.write("# machine:\n"                                                                                          )
    makefile.write("#\n"                                                                                                   )
    makefile.write("#    1. GNU make (tested with)\n"                                                                      )
    makefile.write("#    2. Doxygen\n"                                                                                     )
    makefile.write("#\n"                                                                                                   )
    makefile.write("#--------------------------------------------------------------------------------------------------#\n\n")

    makefile.write("MAKEFILE_LOC = $(CX_SRC_ROOT)/" + p_libName + "/doc\n\n"                                               )

    makefile.write("# Doxygen:\n"                                                                                          )
    makefile.write("DOXYDIR  = $(MAKEFILE_LOC)/doxygen\n"                                                                  )
    makefile.write("DOXYFILE = $(DOXYDIR)/Doxyfile\n\n"                                                             )

    makefile.write(".PHONY: doxygen clean\n\n"                                                                             )

    makefile.write("doxygen:\n"                                                                                            )
    makefile.write("\t@echo Generating Doxygen documentation...\n"                                                         )
    makefile.write("\tdoxygen $(DOXYFILE)\n"                                                                               )
    makefile.write("\t@echo Doxygen documentation created!\n\n"                                                            )

    makefile.write("mrproper: clean\n\n"                                                                                   )

    makefile.write("clean:\n"                                                                                              )
    makefile.write("\t@echo Deleting Doxygen documentation...\n"                                                           )
    makefile.write("\t$(RM) -r $(DOXYDIR)/html\n"                                                                          )
    makefile.write("\t@echo Doxygen documentation deleted!\n\n"                                                            )
    
    makefile.close()

    if not os.path.exists(makefilePath):
        print("Error: The Doxygen makefile was not created!")
        sys.exit(ERROR_DOXYGEN_MAKEFILE_NOT_CREATED)



def generateMakefiles(p_path, p_libName, p_headerInfo):
    """
    Generates all required Makefiles required to build the library and 
    its documentation.
    
    Args:
        p_path:     The path on disc where to create the library structure.
        p_libName:  The name of the library (in lowercase).
    """

    generateLibraryMakefile(p_path, p_libName, p_headerInfo)
    generateTestMakefile   (p_path, p_libName, p_headerInfo)
    generateDoxygenMakefile(p_path, p_libName, p_headerInfo)



def generateUnitTestMain(p_path, p_libName):
    """
    Generates the file for the library unit tests which contains
    the main() function.
    
    Args:
        p_path:     The path on disc where to create the library structure.
        p_libName:  The name of the library (in lowercase).
    """

    testFilePath = p_path + p_libName + "/test/" + p_libName + "Test.cpp"
    
    testFile = open(testFilePath, "w+")

    # Populate the file:
    testFile.write("/***************************************************************************************************\n")
    testFile.write("* \n"                                                                                                  )
    testFile.write("* Copyright (C) 2016 Connect X team\n"                                                                 )
    testFile.write("* \n"                                                                                                  )
    testFile.write("* This file is part of Connect X.\n"                                                                   )
    testFile.write("* \n"                                                                                                  )
    testFile.write("* Connect X is free software: you can redistribute it and/or modify\n"                                 )
    testFile.write("* it under the terms of the GNU General Public License as published by\n"                              )
    testFile.write("* the Free Software Foundation, either version 3 of the License, or\n"                                 )
    testFile.write("* (at your option) any later version.\n"                                                               )
    testFile.write("* \n"                                                                                                  )
    testFile.write("* Connect X is distributed in the hope that it will be useful\n"                                       )
    testFile.write("* but WITHOUT ANY WARRANTY; without even the implied warranty of\n"                                    )
    testFile.write("* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"                                     )
    testFile.write("* GNU General Public License for more details.\n"                                                      )
    testFile.write("* \n"                                                                                                  )
    testFile.write("* You should have received a copy of the GNU General Public License\n"                                 )
    testFile.write("* along with Connect X.  If not, see <http://www.gnu.org/licenses./>.\n"                               )
    testFile.write("* \n"                                                                                                  )
    testFile.write("**************************************************************************************************\n\n")

    testFile.write("/***********************************************************************************************//*\n" )
    testFile.write("* @file    " + p_libName + "Test.cpp\n"                                                                )
    testFile.write("* @author  elliotchance\n"                                                                             )
    testFile.write("* @date    September 2016\n"                                                                           )
    testFile.write("* @version 0.1\n"                                                                                      )
    testFile.write("* \n"                                                                                                  )
    testFile.write("* Unit tests main. All unit tests for the " + p_libName + "library run from here. All source code from this\n")
    testFile.write("* file comes from <a href=\"https://gist.github.com/ \"elliotchance/8215283\"> here </a>.\n"           )
    testFile.write("* \n"                                                                                                  )
    testFile.write("**************************************************************************************************/\n" )

    testFile.write("#include \"gtest/gtest.h\"\n\n"                                                                        )

    testFile.write("using namespace testing;\n\n\n"                                                                        )


    testFile.write("class ConfigurableEventListener : public TestEventListener\n\n\n"                                      )
    testFile.write("{\n\n"                                                                                                 )

    testFile.write("protected:\n"                                                                                          )
    testFile.write("    TestEventListener* eventListener;\n\n"                                                             )

    testFile.write("public:\n\n"                                                                                           )

    testFile.write("    /**\n"                                                                                             )
    testFile.write("     * Show the names of each test case.\n"                                                            )
    testFile.write("     */\n"                                                                                             )
    testFile.write("    bool showTestCases;\n\n"                                                                           )

    testFile.write("    /**\n"                                                                                             )
    testFile.write("     * Show the names of each test.\n"                                                                 )
    testFile.write("     */\n"                                                                                             )
    testFile.write("    bool showTestNames;\n\n"                                                                           )

    testFile.write("    /**\n"                                                                                             )
    testFile.write("     * Show each success.\n"                                                                           )
    testFile.write("     */\n"                                                                                             )
    testFile.write("    bool showSuccesses;\n\n"                                                                           )

    testFile.write("    /**\n"                                                                                             )
    testFile.write("     * Show each failure as it occurs. You will also see it at the bottom after the full suite is run.\n")
    testFile.write("     */\n"                                                                                             )
    testFile.write("    bool showInlineFailures;\n\n"                                                                      )

    testFile.write("    /**\n"                                                                                             )
    testFile.write("     * Show the setup of the global environment.\n"                                                    )
    testFile.write("     */\n"                                                                                             )
    testFile.write("    bool showEnvironment;\n\n"                                                                         )

    testFile.write("    explicit ConfigurableEventListener(TestEventListener* theEventListener) : eventListener(theEventListener)\n")
    testFile.write("    {\n"                                                                                               )
    testFile.write("        showTestCases        = true;\n"                                                                )
    testFile.write("        showTestNames        = true;\n"                                                                )
    testFile.write("        showSuccesses        = true;\n"                                                                )
    testFile.write("        showInlineFailures   = true;\n"                                                                )
    testFile.write("        showEnvironment      = true;\n"                                                                )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual ~ConfigurableEventListener()\n"                                                            )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        delete eventListener;\n"                                                                       )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestProgramStart(const UnitTest& unit_test)\n"                                      )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        eventListener->OnTestProgramStart(unit_test);\n"                                               )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestIterationStart(const UnitTest& unit_test, int iteration)\n"                     )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        eventListener->OnTestIterationStart(unit_test, iteration);\n"                                  )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnEnvironmentsSetUpStart(const UnitTest& unit_test)\n"                                )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if(showEnvironment) {\n"                                                                       )
    testFile.write("            eventListener->OnEnvironmentsSetUpStart(unit_test);\n"                                     )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnEnvironmentsSetUpEnd(const UnitTest& unit_test)\n"                                  )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if(showEnvironment) {\n"                                                                       )
    testFile.write("            eventListener->OnEnvironmentsSetUpEnd(unit_test);\n"                                       )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestCaseStart(const TestCase& test_case)\n"                                         )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if(showTestCases) {\n"                                                                         )
    testFile.write("            eventListener->OnTestCaseStart(test_case);\n"                                              )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestStart(const TestInfo& test_info)\n"                                             )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if(showTestNames) {\n"                                                                         )
    testFile.write("            eventListener->OnTestStart(test_info);\n"                                                  )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestPartResult(const TestPartResult& result)\n"                                     )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        eventListener->OnTestPartResult(result);\n"                                                    )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestEnd(const TestInfo& test_info)\n"                                               )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if((showInlineFailures && test_info.result()->Failed()) || (showSuccesses && !test_info.result()->Failed())) {\n")
    testFile.write("            eventListener->OnTestEnd(test_info);\n"                                                    )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestCaseEnd(const TestCase& test_case)\n"                                           )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if(showTestCases) {\n"                                                                         )
    testFile.write("            eventListener->OnTestCaseEnd(test_case);\n"                                                )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnEnvironmentsTearDownStart(const UnitTest& unit_test)\n"                             )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if(showEnvironment) {\n"                                                                       )
    testFile.write("            eventListener->OnEnvironmentsTearDownStart(unit_test);\n"                                  )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnEnvironmentsTearDownEnd(const UnitTest& unit_test)\n"                               )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        if(showEnvironment) {\n"                                                                       )
    testFile.write("            eventListener->OnEnvironmentsTearDownEnd(unit_test);\n"                                    )
    testFile.write("        }\n"                                                                                           )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestIterationEnd(const UnitTest& unit_test, int iteration)\n"                       )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        eventListener->OnTestIterationEnd(unit_test, iteration);\n"                                    )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("    virtual void OnTestProgramEnd(const UnitTest& unit_test)\n"                                        )
    testFile.write("    {\n"                                                                                               )
    testFile.write("        eventListener->OnTestProgramEnd(unit_test);\n"                                                 )
    testFile.write("    }\n\n"                                                                                             )

    testFile.write("};\n\n"                                                                                                )

    testFile.write("int main(int argc, char **argv)\n"                                                                     )
    testFile.write("{\n"                                                                                                   )
    testFile.write("    // initialize\n"                                                                                   )
    testFile.write("    ::testing::InitGoogleTest(&argc, argv);\n\n"                                                       )

    testFile.write("    // remove the default listener\n\n"                                                                )

    testFile.write("    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();\n"         )
    testFile.write("    auto default_printer = listeners.Release(listeners.default_result_printer());\n\n\n"               )


    testFile.write("    // add our listener, by default everything is on (the same as using the default listener)\n"       )
    testFile.write("    // here I am turning everything off so I only see the 3 lines for the result\n"                    )
    testFile.write("    // (plus any failures at the end), like:\n\n"                                                      )

    testFile.write("    // [==========] Running 149 tests from 53 test cases.\n"                                           )
    testFile.write("    // [==========] 149 tests from 53 test cases ran. (1 ms total)\n"                                  )
    testFile.write("    // [  PASSED  ] 149 tests.\n\n"                                                                    )

    testFile.write("    ConfigurableEventListener *listener = new ConfigurableEventListener(default_printer);\n"           )
    testFile.write("    listener->showEnvironment = false;\n"                                                              )
    testFile.write("    listener->showTestCases = false;\n"                                                                )
    testFile.write("    listener->showTestNames = false;\n"                                                                )
    testFile.write("    listener->showSuccesses = false;\n"                                                                )
    testFile.write("    listener->showInlineFailures = false;\n"                                                           )
    testFile.write("    listeners.Append(listener);\n\n"                                                                   )

    testFile.write("    // run\n"                                                                                          )
    testFile.write("    return RUN_ALL_TESTS();\n"                                                                         )
    testFile.write("}\n"                                                                                                   )
    
    testFile.close()
    
    if not os.path.exists(testFilePath):
        print("Error: The test main file was not created!")
        sys.exit(ERROR_TEST_MAIN_FILE_NOT_CREATED)



def generateDoxyfile(p_path, p_libName):
    """
    Generates the library's Doxyfile.
    
    Args:
        p_path:     The path on disc where to create the library structure.
        p_libName:  The name of the library (in lowercase).
    """

    doxyfilePath = p_path + p_libName + "/doc/doxygen/Doxyfile"
    
    doxyfile = open(doxyfilePath, "w+")

    doxyfile.write("# Doxyfile 1.8.11\n\n"                                                             )

    doxyfile.write("# This file describes the settings to be used by the documentation system\n"       )
    doxyfile.write("# doxygen (www.doxygen.org) for a project.\n"                                      )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# All text after a double hash (##) is considered a comment and is placed in\n"    )
    doxyfile.write("# front of the TAG it is preceding.\n"                                             )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# All text after a single hash (#) is considered a comment and will be ignored.\n" )
    doxyfile.write("# The format is:\n"                                                                )
    doxyfile.write("# TAG = value [value, ...]\n"                                                      )
    doxyfile.write("# For lists, items can also be appended using:\n"                                  )
    doxyfile.write("# TAG += value [value, ...]\n"                                                     )
    doxyfile.write("# Values that contain spaces should be placed between quotes (\" \").\n\n"         )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Project related configuration options\n"                                         )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# This tag specifies the encoding used for all characters in the config file\n"    )
    doxyfile.write("# that follow. The default is UTF-8 which is also the encoding used for all text\n")
    doxyfile.write("# before the first occurrence of this tag. Doxygen uses libiconv (or the iconv\n"  )
    doxyfile.write("# built into libc) for the transcoding. See http://www.gnu.org/software/libiconv\n")
    doxyfile.write("# for the list of possible encodings.\n"                                           )
    doxyfile.write("# The default value is: UTF-8.\n\n"                                                )

    doxyfile.write("DOXYFILE_ENCODING = UTF-8\n\n"                                                     )

    doxyfile.write("# The PROJECT_NAME tag is a single word (or a sequence of words surrounded by\n"   )
    doxyfile.write("# double-quotes, unless you are using Doxywizard) that should identify the\n"      )
    doxyfile.write("# project for which the documentation is generated. This name is used in the\n"    )
    doxyfile.write("# title of most generated pages and in a few other places.\n"                      )
    doxyfile.write("# The default value is: My Project.\n\n"                                           )

    doxyfile.write("PROJECT_NAME = \"" + p_libName + "\"\n\n"                                          )

    doxyfile.write("# The PROJECT_NUMBER tag can be used to enter a project or revision number. This\n")
    doxyfile.write("# could be handy for archiving the generated documentation or if some version\n"   )
    doxyfile.write("# control system is used.\n\n"                                                     )

    doxyfile.write("PROJECT_NUMBER = 0.1\n\n"                                                          )

    doxyfile.write("# Using the PROJECT_BRIEF tag one can provide an optional one line description\n"  )
    doxyfile.write("# for a project that appears at the top of each page and should give viewer a\n"   )
    doxyfile.write("# quick idea about the purpose of the project. Keep the description short.\n\n"    )

    doxyfile.write("PROJECT_BRIEF = \n\n"                                                              )

    doxyfile.write("# With the PROJECT_LOGO tag one can specify a logo or an icon that is included\n"  )
    doxyfile.write("# in the documentation. The maximum height of the logo should not exceed 55\n"     )
    doxyfile.write("# pixels and the maximum width should not exceed 200 pixels. Doxygen will copy\n"  )
    doxyfile.write("# the logo to the output directory.\n\n"                                           )

    doxyfile.write("PROJECT_LOGO = \n\n"                                                               )

    doxyfile.write("# The OUTPUT_DIRECTORY tag is used to specify the (relative or absolute) path\n"   )
    doxyfile.write("# into which the generated documentation will be written. If a relative path is\n" )
    doxyfile.write("# entered, it will be relative to the location where doxygen was started. If\n"    )
    doxyfile.write("# left blank the current directory will be used.\n\n"                              )

    doxyfile.write("OUTPUT_DIRECTORY = ./doxygen\n\n"                                                  )

    doxyfile.write("# If the CREATE_SUBDIRS tag is set to YES then doxygen will create 4096 sub-\n"    )
    doxyfile.write("# directories (in 2 levels) under the output directory of each output format and\n")
    doxyfile.write("# will distribute the generated files over these directories. Enabling this\n"     )
    doxyfile.write("# option can be useful when feeding doxygen a huge amount of source files, where\n")
    doxyfile.write("# putting all generated files in the same directory would otherwise causes\n"      )
    doxyfile.write("# performance problems for the file system.\n"                                     )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("CREATE_SUBDIRS = NO\n\n"                                                           )

    doxyfile.write("# If the ALLOW_UNICODE_NAMES tag is set to YES, doxygen will allow non-ASCII\n"    )
    doxyfile.write("# characters to appear in the names of generated files. If set to NO, non-ASCII\n" )
    doxyfile.write("# characters will be escaped, for example _xE3_x81_x84 will be used for Unicode\n" )
    doxyfile.write("# U+3044.\n"                                                                       )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("ALLOW_UNICODE_NAMES = NO\n\n"                                                      )

    doxyfile.write("# The OUTPUT_LANGUAGE tag is used to specify the language in which all\n"          )
    doxyfile.write("# documentation generated by doxygen is written. Doxygen will use this\n"          )
    doxyfile.write("# information to generate all constant output in the proper language.\n"           )
    doxyfile.write("# Possible values are: Afrikaans, Arabic, Armenian, Brazilian, Catalan, Chinese,\n")
    doxyfile.write("# Chinese-Traditional, Croatian, Czech, Danish, Dutch, English (United States),\n" )
    doxyfile.write("# Esperanto, Farsi (Persian), Finnish, French, German, Greek, Hungarian,\n"        )
    doxyfile.write("# Indonesian, Italian, Japanese, Japanese-en (Japanese with English messages),\n"  )
    doxyfile.write("# Korean, Korean-en (Korean with English messages), Latvian, Lithuanian,\n"        )
    doxyfile.write("# Macedonian, Norwegian, Persian (Farsi), Polish, Portuguese, Romanian, Russian,\n")
    doxyfile.write("# Serbian, Serbian-Cyrillic, Slovak, Slovene, Spanish, Swedish, Turkish,\n"        )
    doxyfile.write("# Ukrainian and Vietnamese.\n"                                                     )
    doxyfile.write("# The default value is: English.\n\n"                                              )

    doxyfile.write("OUTPUT_LANGUAGE = English\n\n"                                                     )

    doxyfile.write("# If the BRIEF_MEMBER_DESC tag is set to YES, doxygen will include brief member\n" )
    doxyfile.write("# descriptions after the members that are listed in the file and class\n"          )
    doxyfile.write("# documentation (similar to Javadoc). Set to NO to disable this.\n"                )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("BRIEF_MEMBER_DESC = YES\n\n"                                                       )

    doxyfile.write("# If the REPEAT_BRIEF tag is set to YES, doxygen will prepend the brief\n"         )
    doxyfile.write("# description of a member or function before the detailed description\n"           )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note: If both HIDE_UNDOC_MEMBERS and BRIEF_MEMBER_DESC are set to NO, the\n"     )
    doxyfile.write("# brief descriptions will be completely suppressed.\n"                             )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("REPEAT_BRIEF = YES\n\n"                                                            )

    doxyfile.write("# This tag implements a quasi-intelligent brief description abbreviator that is\n" )
    doxyfile.write("# used to form the text in various listings. Each string in this list, if found\n" )
    doxyfile.write("# as the leading text of the brief description, will be stripped from the text\n"  )
    doxyfile.write("# and the result, after processing the whole list, is used as the annotated\n"     )
    doxyfile.write("# text. Otherwise, the brief description is used as-is. If left blank, the\n"      )
    doxyfile.write("# following values are used ($name is automatically replaced with the name of\n"   )
    doxyfile.write("# the entity):The $name class, The $name widget, The $name file, is, provides,\n"  )
    doxyfile.write("# specifies, contains, represents, a, an and the.\n\n"                             )

    doxyfile.write("ABBREVIATE_BRIEF = \n\n"                                                           )

    doxyfile.write("# If the ALWAYS_DETAILED_SEC and REPEAT_BRIEF tags are both set to YES then\n"     )
    doxyfile.write("# doxygen will generate a detailed section even if there is only a brief\n"        )
    doxyfile.write("# description.\n"                                                                  )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("ALWAYS_DETAILED_SEC = NO\n\n"                                                      )

    doxyfile.write("# If the INLINE_INHERITED_MEMB tag is set to YES, doxygen will show all\n"         )
    doxyfile.write("# inherited members of a class in the documentation of that class as if those\n"   )
    doxyfile.write("# members were ordinary class members. Constructors, destructors and assignment\n" )
    doxyfile.write("# operators of the base classes will not be shown.\n"                              )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("INLINE_INHERITED_MEMB = NO\n\n"                                                    )

    doxyfile.write("# If the FULL_PATH_NAMES tag is set to YES, doxygen will prepend the full path\n"  )
    doxyfile.write("# before files name in the file list and in the header files. If set to NO the\n"  )
    doxyfile.write("# shortest path that makes the file name unique will be used\n"                    )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("FULL_PATH_NAMES = NO\n\n"                                                          )

    doxyfile.write("# The STRIP_FROM_PATH tag can be used to strip a user-defined part of the path.\n" )
    doxyfile.write("# Stripping is only done if one of the specified strings matches the left-hand\n"  )
    doxyfile.write("# part of the path. The tag can be used to show relative paths in the file list.\n")
    doxyfile.write("# If left blank the directory from which doxygen is run is used as the path to\n"  )
    doxyfile.write("# strip.\n"                                                                        )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that you can specify absolute paths here, but also relative paths, which\n" )
    doxyfile.write("# will be relative from the directory where doxygen is started.\n"                 )
    doxyfile.write("# This tag requires that the tag FULL_PATH_NAMES is set to YES.\n\n"               )

    doxyfile.write("STRIP_FROM_PATH = \n\n"                                                            )

    doxyfile.write("# The STRIP_FROM_INC_PATH tag can be used to strip a user-defined part of the\n"   )
    doxyfile.write("# path mentioned in the documentation of a class, which tells the reader which\n"  )
    doxyfile.write("# header file to include in order to use a class. If left blank only the name of\n")
    doxyfile.write("# the header file containing the class definition is used. Otherwise one should\n" )
    doxyfile.write("# specify the list of include paths that are normally passed to the compiler\n"    )
    doxyfile.write("# using the -I flag.\n\n"                                                          )

    doxyfile.write("STRIP_FROM_INC_PATH = \n\n"                                                        )

    doxyfile.write("# If the SHORT_NAMES tag is set to YES, doxygen will generate much shorter (but\n" )
    doxyfile.write("# less readable) file names. This can be useful is your file systems doesn't\n"    )
    doxyfile.write("# support long names like on DOS, Mac, or CD-ROM.\n"                               )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SHORT_NAMES = NO\n\n"                                                              )

    doxyfile.write("# If the JAVADOC_AUTOBRIEF tag is set to YES then doxygen will interpret the\n"    )
    doxyfile.write("# first line (until the first dot) of a Javadoc-style comment as the brief\n"      )
    doxyfile.write("# description. If set to NO, the Javadoc-style will behave just like regular Qt-\n")
    doxyfile.write("# style comments (thus requiring an explicit @brief command for a brief\n"         )
    doxyfile.write("# description.)\n"                                                                 )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("JAVADOC_AUTOBRIEF = NO\n\n"                                                        )

    doxyfile.write("# If the QT_AUTOBRIEF tag is set to YES then doxygen will interpret the first\n"   )
    doxyfile.write("# line (until the first dot) of a Qt-style comment as the brief description. If\n" )
    doxyfile.write("# set to NO, the Qt-style will behave just like regular Qt-style comments (thus\n" )
    doxyfile.write("# requiring an explicit \brief command for a brief description.)\n"                )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("QT_AUTOBRIEF = NO\n\n"                                                             )

    doxyfile.write("# The MULTILINE_CPP_IS_BRIEF tag can be set to YES to make doxygen treat a\n"      )
    doxyfile.write("# multi-line C++ special comment block (i.e. a block of //! or /// comments) as\n" )
    doxyfile.write("# a brief description. This used to be the default behavior. The new default is\n" )
    doxyfile.write("# to treat a multi-line C++ comment block as a detailed description. Set this\n"   )
    doxyfile.write("# tag to YES if you prefer the old behavior instead.\n"                            )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that setting this tag to YES also means that rational rose comments are\n"  )
    doxyfile.write("# not recognized any more.\n"                                                      )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("MULTILINE_CPP_IS_BRIEF = NO\n\n"                                                   )

    doxyfile.write("# If the INHERIT_DOCS tag is set to YES then an undocumented member inherits the\n")
    doxyfile.write("# documentation from any documented member that it re-implements.\n"               )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("INHERIT_DOCS = YES\n\n"                                                            )

    doxyfile.write("# If the SEPARATE_MEMBER_PAGES tag is set to YES then doxygen will produce a new\n")
    doxyfile.write("# page for each member. If set to NO, the documentation of a member will be part\n")
    doxyfile.write("# of the file/class/namespace that contains it.\n"                                 )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SEPARATE_MEMBER_PAGES = NO\n\n"                                                    )

    doxyfile.write("# The TAB_SIZE tag can be used to set the number of spaces in a tab. Doxygen\n"    )
    doxyfile.write("# uses this value to replace tabs by spaces in code fragments.\n"                  )
    doxyfile.write("# Minimum value: 1, maximum value: 16, default value: 4.\n\n"                      )

    doxyfile.write("TAB_SIZE = 4\n\n"                                                                  )

    doxyfile.write("# This tag can be used to specify a number of aliases that act as commands in\n"   )
    doxyfile.write("# the documentation. An alias has the form:\n"                                     )
    doxyfile.write("# name=value\n"                                                                    )
    doxyfile.write("# For example adding\n"                                                            )
    doxyfile.write("# \"sideeffect=@par Side Effects:\"\n\n"                                             )
    doxyfile.write("# will allow you to put the command \sideeffect (or @sideeffect) in the\n"         )
    doxyfile.write("# documentation, which will result in a user-defined paragraph with heading\n"     )
    doxyfile.write("# \"Side Effects:\". You can put 's in the value part of an alias to insert\n"     )
    doxyfile.write("# newlines.\n\n"                                                                   )

    doxyfile.write("ALIASES = \n\n"                                                                    )

    doxyfile.write("# This tag can be used to specify a number of word-keyword mappings (TCL only).\n" )
    doxyfile.write("# A mapping has the form \"name=value\". For example adding \"class=itcl::class\"\n")
    doxyfile.write("# will allow you to use the command class in the itcl::class meaning.\n\n"         )

    doxyfile.write("TCL_SUBST = \n\n"                                                                  )

    doxyfile.write("# Set the OPTIMIZE_OUTPUT_FOR_C tag to YES if your project consists of C sources\n")
    doxyfile.write("# only. Doxygen will then generate output that is more tailored for C. For\n"      )
    doxyfile.write("# instance, some of the names that are used will be different. The list of all\n"  )
    doxyfile.write("# members will be omitted, etc.\n"                                                 )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("OPTIMIZE_OUTPUT_FOR_C = NO\n\n"                                                    )

    doxyfile.write("# Set the OPTIMIZE_OUTPUT_JAVA tag to YES if your project consists of Java or\n"   )
    doxyfile.write("# Python sources only. Doxygen will then generate output that is more tailored\n"  )
    doxyfile.write("# for that language. For instance, namespaces will be presented as packages,\n"    )
    doxyfile.write("# qualified scopes will look different, etc.\n"                                    )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("OPTIMIZE_OUTPUT_JAVA = NO\n\n"                                                     )

    doxyfile.write("# Set the OPTIMIZE_FOR_FORTRAN tag to YES if your project consists of Fortran\n"   )
    doxyfile.write("# sources. Doxygen will then generate output that is tailored for Fortran.\n"      )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("OPTIMIZE_FOR_FORTRAN = NO\n\n"                                                     )

    doxyfile.write("# Set the OPTIMIZE_OUTPUT_VHDL tag to YES if your project consists of VHDL\n"      )
    doxyfile.write("# sources. Doxygen will then generate output that is tailored for VHDL.\n"         )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("OPTIMIZE_OUTPUT_VHDL = NO\n\n"                                                     )

    doxyfile.write("# Doxygen selects the parser to use depending on the extension of the files it\n"  )
    doxyfile.write("# parses. With this tag you can assign which parser to use for a given\n"          )
    doxyfile.write("# extension. Doxygen has a built-in mapping, but you can override or extend it\n"  )
    doxyfile.write("# using this tag. The format is ext=language, where ext is a file extension, and\n")
    doxyfile.write("# language is one of the parsers supported by doxygen: IDL, Java, Javascript,\n"   )
    doxyfile.write("# C#, C, C++, D, PHP, Objective-C, Python, Fortran (fixed format Fortran:\n"       )
    doxyfile.write("# FortranFixed, free formatted Fortran: FortranFree, unknown formatted Fortran:\n" )
    doxyfile.write("# Fortran. In the later case the parser tries to guess whether the code is fixed\n")
    doxyfile.write("# or free formatted code, this is the default for Fortran type files), VHDL. For\n")
    doxyfile.write("# instance to make doxygen treat .inc files as Fortran files (default is PHP),\n"  )
    doxyfile.write("# and .f files as C (default is Fortran), use: inc=Fortran f=C.\n"                 )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note: For files without extension you can use no_extension as a placeholder.\n"  )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that for custom extensions you also need to set FILE_PATTERNS otherwise\n"  )
    doxyfile.write("# the files are not read by doxygen.\n\n"                                          )

    doxyfile.write("EXTENSION_MAPPING = \n\n"                                                          )

    doxyfile.write("# If the MARKDOWN_SUPPORT tag is enabled then doxygen pre-processes all comments\n")
    doxyfile.write("# according to the Markdown format, which allows for more readable\n"              )
    doxyfile.write("# documentation. See http://daringfireball.net/projects/markdown/ for details.\n"  )
    doxyfile.write("# The output of markdown processing is further processed by doxygen, so you can\n" )
    doxyfile.write("# mix doxygen, HTML, and XML commands with Markdown formatting. Disable only in\n" )
    doxyfile.write("# case of backward compatibilities issues.\n"                                      )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("MARKDOWN_SUPPORT = NO\n\n"                                                         )

    doxyfile.write("# When enabled doxygen tries to link words that correspond to documented\n"        )
    doxyfile.write("# classes, or namespaces to their corresponding documentation. Such a link can\n"  )
    doxyfile.write("# be prevented in individual cases by putting a % sign in front of the word or\n"  )
    doxyfile.write("# globally by setting AUTOLINK_SUPPORT to NO.\n"                                   )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("AUTOLINK_SUPPORT = YES\n\n"                                                        )

    doxyfile.write("# If you use STL classes (i.e. std::string, std::vector, etc.) but do not want\n"  )
    doxyfile.write("# to include (a tag file for) the STL sources as input, then you should set this\n")
    doxyfile.write("# tag to YES in order to let doxygen match functions declarations and\n"           )
    doxyfile.write("# definitions whose arguments contain STL classes (e.g. func(std::string);\n"      )
    doxyfile.write("# versus func(std::string) {}). This also make the inheritance and collaboration\n")
    doxyfile.write("# diagrams that involve STL classes more complete and accurate.\n"                 )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("BUILTIN_STL_SUPPORT = NO\n\n"                                                      )

    doxyfile.write("# If you use Microsoft's C++/CLI language, you should set this option to YES to\n" )
    doxyfile.write("# enable parsing support.\n"                                                       )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("CPP_CLI_SUPPORT = NO\n\n"                                                          )

    doxyfile.write("# Set the SIP_SUPPORT tag to YES if your project consists of sip (see:\n"          )
    doxyfile.write("# http://www.riverbankcomputing.co.uk/software/sip/intro) sources only. Doxygen\n" )
    doxyfile.write("# will parse them like normal C++ but will assume all classes use public instead\n")
    doxyfile.write("# of private inheritance when no explicit protection keyword is present.\n"        )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SIP_SUPPORT = NO\n\n"                                                              )

    doxyfile.write("# For Microsoft's IDL there are propget and propput attributes to indicate\n"      )
    doxyfile.write("# getter and setter methods for a property. Setting this option to YES will make\n")
    doxyfile.write("# doxygen to replace the get and set methods by a property in the documentation.\n")
    doxyfile.write("# This will only work if the methods are indeed getting or setting a simple\n"     )
    doxyfile.write("# type. If this is not the case, or you want to show the methods anyway, you\n"    )
    doxyfile.write("# should set this option to NO.\n"                                                 )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("IDL_PROPERTY_SUPPORT = YES\n\n"                                                    )

    doxyfile.write("# If member grouping is used in the documentation and the DISTRIBUTE_GROUP_DOC\n"  )
    doxyfile.write("# tag is set to YES then doxygen will reuse the documentation of the first\n"      )
    doxyfile.write("# member in the group (if any) for the other members of the group. By default\n"   )
    doxyfile.write("# all members of a group must be documented explicitly.\n"                         )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("DISTRIBUTE_GROUP_DOC = NO\n\n"                                                     )

    doxyfile.write("# If one adds a struct or class to a group and this option is enabled, then also\n")
    doxyfile.write("# any nested class or struct is added to the same group. By default this option\n" )
    doxyfile.write("# is disabled and one has to add nested compounds explicitly via \ingroup.\n"      )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("GROUP_NESTED_COMPOUNDS = NO\n\n"                                                   )

    doxyfile.write("# Set the SUBGROUPING tag to YES to allow class member groups of the same type\n"  )
    doxyfile.write("# (for instance a group of public functions) to be put as a subgroup of that\n"    )
    doxyfile.write("# type (e.g. under the Public Functions section). Set it to NO to prevent\n"       )
    doxyfile.write("# subgrouping. Alternatively, this can be done per class using the\n"              )
    doxyfile.write("# osubgrouping command.\n"                                                         )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("SUBGROUPING = YES\n\n"                                                             )

    doxyfile.write("# When the INLINE_GROUPED_CLASSES tag is set to YES, classes, structs and unions\n")
    doxyfile.write("# are shown inside the group in which they are included (e.g. using \ingroup)\n"   )
    doxyfile.write("# instead of on a separate page (for HTML and Man pages) or section (for LaTeX\n"  )
    doxyfile.write("# and RTF).\n"                                                                     )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that this feature does not work in combination with\n"                      )
    doxyfile.write("# SEPARATE_MEMBER_PAGES.\n"                                                        )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("INLINE_GROUPED_CLASSES = NO\n\n"                                                   )

    doxyfile.write("# When the INLINE_SIMPLE_STRUCTS tag is set to YES, structs, classes, and unions\n")
    doxyfile.write("# with only public data fields or simple typedef fields will be shown inline in\n" )
    doxyfile.write("# the documentation of the scope in which they are defined (i.e. file,\n"          )
    doxyfile.write("# namespace, or group documentation), provided this scope is documented. If set\n" )
    doxyfile.write("# to NO, structs, classes, and unions are shown on a separate page (for HTML and\n")
    doxyfile.write("# Man pages) or section (for LaTeX and RTF).\n"                                    )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("INLINE_SIMPLE_STRUCTS = NO\n\n"                                                    )

    doxyfile.write("# When TYPEDEF_HIDES_STRUCT tag is enabled, a typedef of a struct, union, or\n"    )
    doxyfile.write("# enum is documented as struct, union, or enum with the name of the typedef. So\n" )
    doxyfile.write("# typedef struct TypeS {} TypeT, will appear in the documentation as a struct\n"   )
    doxyfile.write("# with name TypeT. When disabled the typedef will appear as a member of a file,\n" )
    doxyfile.write("# namespace, or class. And the struct will be named TypeS. This can typically be\n")
    doxyfile.write("# useful for C code in case the coding convention dictates that all compound\n"    )
    doxyfile.write("# types are typedef'ed and only the typedef is referenced, never the tag name.\n"  )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("TYPEDEF_HIDES_STRUCT = NO\n\n"                                                     )

    doxyfile.write("# The size of the symbol lookup cache can be set using LOOKUP_CACHE_SIZE. This\n"  )
    doxyfile.write("# cache is used to resolve symbols given their name and scope. Since this can be\n")
    doxyfile.write("# an expensive process and often the same symbol appears multiple times in the\n"  )
    doxyfile.write("# code, doxygen keeps a cache of pre-resolved symbols. If the cache is too small\n")
    doxyfile.write("# doxygen will become slower. If the cache is too large, memory is wasted. The\n"  )
    doxyfile.write("# cache size is given by this formula: 2^(16+LOOKUP_CACHE_SIZE). The valid range\n")
    doxyfile.write("# is 0..9, the default is 0, corresponding to a cache size of 2^16=65536\n"        )
    doxyfile.write("# symbols. At the end of a run doxygen will report the cache usage and suggest\n"  )
    doxyfile.write("# the optimal cache size from a speed point of view.\n"                            )
    doxyfile.write("# Minimum value: 0, maximum value: 9, default value: 0.\n\n"                       )

    doxyfile.write("LOOKUP_CACHE_SIZE = 0\n\n"                                                         )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Build related configuration options\n"                                           )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the EXTRACT_ALL tag is set to YES, doxygen will assume all entities in\n"     )
    doxyfile.write("# documentation are documented, even if no documentation was available. Private\n" )
    doxyfile.write("# class members and static file members will be hidden unless the\n"               )
    doxyfile.write("# EXTRACT_PRIVATE respectively EXTRACT_STATIC tags are set to YES.\n"              )
    doxyfile.write("# Note: This will also disable the warnings about undocumented members that are\n" )
    doxyfile.write("# normally produced when WARNINGS is set to YES.\n"                                )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXTRACT_ALL = YES\n\n"                                                             )

    doxyfile.write("# If the EXTRACT_PRIVATE tag is set to YES, all private members of a class will\n" )
    doxyfile.write("# be included in the documentation.\n"                                             )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXTRACT_PRIVATE = NO\n\n"                                                          )

    doxyfile.write("# If the EXTRACT_PACKAGE tag is set to YES, all members with package or internal\n")
    doxyfile.write("# scope will be included in the documentation.\n"                                  )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXTRACT_PACKAGE = NO\n\n"                                                          )

    doxyfile.write("# If the EXTRACT_STATIC tag is set to YES, all static members of a file will be\n" )
    doxyfile.write("# included in the documentation.\n"                                                )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXTRACT_STATIC = NO\n\n"                                                           )

    doxyfile.write("# If the EXTRACT_LOCAL_CLASSES tag is set to YES, classes (and structs) defined\n" )
    doxyfile.write("# locally in source files will be included in the documentation. If set to NO,\n"  )
    doxyfile.write("# only classes defined in header files are included. Does not have any effect\n"   )
    doxyfile.write("# for Java sources.\n"                                                             )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("EXTRACT_LOCAL_CLASSES = YES\n\n"                                                   )

    doxyfile.write("# This flag is only useful for Objective-C code. If set to YES, local methods,\n"  )
    doxyfile.write("# which are defined in the implementation section but not in the interface are\n"  )
    doxyfile.write("# included in the documentation. If set to NO, only methods in the interface are\n")
    doxyfile.write("# included.\n"                                                                     )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXTRACT_LOCAL_METHODS = NO\n\n"                                                    )

    doxyfile.write("# If this flag is set to YES, the members of anonymous namespaces will be\n"       )
    doxyfile.write("# extracted and appear in the documentation as a namespace called\n"               )
    doxyfile.write("# 'anonymous_namespace{file}', where file will be replaced with the base name of\n")
    doxyfile.write("# the file that contains the anonymous namespace. By default anonymous namespace\n")
    doxyfile.write("# are hidden.\n"                                                                   )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXTRACT_ANON_NSPACES = NO\n\n"                                                     )

    doxyfile.write("# If the HIDE_UNDOC_MEMBERS tag is set to YES, doxygen will hide all\n"            )
    doxyfile.write("# undocumented members inside documented classes or files. If set to NO these\n"   )
    doxyfile.write("# members will be included in the various overviews, but no documentation\n"       )
    doxyfile.write("# section is generated. This option has no effect if EXTRACT_ALL is enabled.\n"    )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("HIDE_UNDOC_MEMBERS = NO\n\n"                                                       )

    doxyfile.write("# If the HIDE_UNDOC_CLASSES tag is set to YES, doxygen will hide all\n"            )
    doxyfile.write("# undocumented classes that are normally visible in the class hierarchy. If set\n" )
    doxyfile.write("# to NO, these classes will be included in the various overviews. This option\n"   )
    doxyfile.write("# has no effect if EXTRACT_ALL is enabled.\n"                                      )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("HIDE_UNDOC_CLASSES = NO\n\n"                                                       )

    doxyfile.write("# If the HIDE_FRIEND_COMPOUNDS tag is set to YES, doxygen will hide all friend\n"  )
    doxyfile.write("# (class|struct|union) declarations. If set to NO, these declarations will be\n"   )
    doxyfile.write("# included in the documentation.\n"                                                )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("HIDE_FRIEND_COMPOUNDS = NO\n\n"                                                    )

    doxyfile.write("# If the HIDE_IN_BODY_DOCS tag is set to YES, doxygen will hide any\n"             )
    doxyfile.write("# documentation blocks found inside the body of a function. If set to NO, these\n" )
    doxyfile.write("# blocks will be appended to the function's detailed documentation block.\n"       )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("HIDE_IN_BODY_DOCS = NO\n\n"                                                        )

    doxyfile.write("# The INTERNAL_DOCS tag determines if documentation that is typed after a\n"       )
    doxyfile.write("# \internal command is included. If the tag is set to NO then the documentation\n" )
    doxyfile.write("# will be excluded. Set it to YES to include the internal documentation.\n"        )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("INTERNAL_DOCS = NO\n\n"                                                            )

    doxyfile.write("# If the CASE_SENSE_NAMES tag is set to NO then doxygen will only generate file\n" )
    doxyfile.write("# names in lower-case letters. If set to YES, upper-case letters are also\n"       )
    doxyfile.write("# allowed. This is useful if you have classes or files whose names only differ\n"  )
    doxyfile.write("# in case and if your file system supports case sensitive file names. Windows\n"   )
    doxyfile.write("# and Mac users are advised to set this option to NO.\n"                           )
    doxyfile.write("# The default value is: system dependent.\n\n"                                     )

    doxyfile.write("CASE_SENSE_NAMES = YES\n\n"                                                        )

    doxyfile.write("# If the HIDE_SCOPE_NAMES tag is set to NO then doxygen will show members with\n"  )
    doxyfile.write("# their full class and namespace scopes in the documentation. If set to YES, the\n")
    doxyfile.write("# scope will be hidden.\n"                                                         )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("HIDE_SCOPE_NAMES = NO\n\n"                                                         )

    doxyfile.write("# If the HIDE_COMPOUND_REFERENCE tag is set to NO (default) then doxygen will\n"   )
    doxyfile.write("# append additional text to a page's title, such as Class Reference. If set to\n"  )
    doxyfile.write("# YES the compound reference will be hidden.\n"                                    )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("HIDE_COMPOUND_REFERENCE = NO\n\n"                                                  )

    doxyfile.write("# If the SHOW_INCLUDE_FILES tag is set to YES then doxygen will put a list of\n"   )
    doxyfile.write("# the files that are included by a file in the documentation of that file.\n"      )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("SHOW_INCLUDE_FILES = YES\n\n"                                                      )

    doxyfile.write("# If the SHOW_GROUPED_MEMB_INC tag is set to YES then Doxygen will add for each\n" )
    doxyfile.write("# grouped member an include statement to the documentation, telling the reader\n"  )
    doxyfile.write("# which file to include in order to use the member.\n"                             )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SHOW_GROUPED_MEMB_INC = NO\n\n"                                                    )

    doxyfile.write("# If the FORCE_LOCAL_INCLUDES tag is set to YES then doxygen will list include\n"  )
    doxyfile.write("# files with double quotes in the documentation rather than with sharp brackets.\n")
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("FORCE_LOCAL_INCLUDES = NO\n\n"                                                     )

    doxyfile.write("# If the INLINE_INFO tag is set to YES then a tag [inline] is inserted in the\n"   )
    doxyfile.write("# documentation for inline members.\n"                                             )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("INLINE_INFO = YES\n\n"                                                             )

    doxyfile.write("# If the SORT_MEMBER_DOCS tag is set to YES then doxygen will sort the\n"          )
    doxyfile.write("# (detailed) documentation of file and class members alphabetically by member\n"   )
    doxyfile.write("# name. If set to NO, the members will appear in declaration order.\n"             )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("SORT_MEMBER_DOCS = YES\n\n"                                                        )

    doxyfile.write("# If the SORT_BRIEF_DOCS tag is set to YES then doxygen will sort the brief\n"     )
    doxyfile.write("# descriptions of file, namespace and class members alphabetically by member\n"    )
    doxyfile.write("# name. If set to NO, the members will appear in declaration order. Note that\n"   )
    doxyfile.write("# this will also influence the order of the classes in the class list.\n"          )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SORT_BRIEF_DOCS = NO\n\n"                                                          )

    doxyfile.write("# If the SORT_MEMBERS_CTORS_1ST tag is set to YES then doxygen will sort the\n"    )
    doxyfile.write("# (brief and detailed) documentation of class members so that constructors and\n"  )
    doxyfile.write("# destructors are listed first. If set to NO the constructors will appear in the\n")
    doxyfile.write("# respective orders defined by SORT_BRIEF_DOCS and SORT_MEMBER_DOCS.\n"            )
    doxyfile.write("# Note: If SORT_BRIEF_DOCS is set to NO this option is ignored for sorting brief\n")
    doxyfile.write("# member documentation.\n"                                                         )
    doxyfile.write("# Note: If SORT_MEMBER_DOCS is set to NO this option is ignored for sorting\n"     )
    doxyfile.write("# detailed member documentation.\n"                                                )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SORT_MEMBERS_CTORS_1ST = NO\n\n"                                                   )

    doxyfile.write("# If the SORT_GROUP_NAMES tag is set to YES then doxygen will sort the hierarchy\n")
    doxyfile.write("# of group names into alphabetical order. If set to NO the group names will\n"     )
    doxyfile.write("# appear in their defined order.\n"                                                )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SORT_GROUP_NAMES = NO\n\n"                                                         )

    doxyfile.write("# If the SORT_BY_SCOPE_NAME tag is set to YES, the class list will be sorted by\n" )
    doxyfile.write("# fully-qualified names, including namespaces. If set to NO, the class list will\n")
    doxyfile.write("# be sorted only by class name, not including the namespace part.\n"               )
    doxyfile.write("# Note: This option is not very useful if HIDE_SCOPE_NAMES is set to YES.\n"       )
    doxyfile.write("# Note: This option applies only to the class list, not to the alphabetical\n"     )
    doxyfile.write("# list.\n"                                                                         )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SORT_BY_SCOPE_NAME = NO\n\n"                                                       )

    doxyfile.write("# If the STRICT_PROTO_MATCHING option is enabled and doxygen fails to do proper\n" )
    doxyfile.write("# type resolution of all parameters of a function it will reject a match between\n")
    doxyfile.write("# the prototype and the implementation of a member function even if there is\n"    )
    doxyfile.write("# only one candidate or it is obvious which candidate to choose by doing a\n"      )
    doxyfile.write("# simple string match. By disabling STRICT_PROTO_MATCHING doxygen will still\n"    )
    doxyfile.write("# accept a match between prototype and implementation in such cases.\n"            )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("STRICT_PROTO_MATCHING = NO\n\n"                                                    )

    doxyfile.write("# The GENERATE_TODOLIST tag can be used to enable (YES) or disable (NO) the todo\n")
    doxyfile.write("# list. This list is created by putting \todo commands in the documentation.\n"    )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("GENERATE_TODOLIST = YES\n\n"                                                       )

    doxyfile.write("# The GENERATE_TESTLIST tag can be used to enable (YES) or disable (NO) the test\n")
    doxyfile.write("# list. This list is created by putting \test commands in the documentation.\n"    )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("GENERATE_TESTLIST = YES\n\n"                                                       )

    doxyfile.write("# The GENERATE_BUGLIST tag can be used to enable (YES) or disable (NO) the bug\n"  )
    doxyfile.write("# list. This list is created by putting \bug commands in the documentation.\n"     )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("GENERATE_BUGLIST = YES\n\n"                                                        )

    doxyfile.write("# The GENERATE_DEPRECATEDLIST tag can be used to enable (YES) or disable (NO)\n"   )
    doxyfile.write("# the deprecated list. This list is created by putting \deprecated commands in\n"  )
    doxyfile.write("# the documentation.\n"                                                            )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("GENERATE_DEPRECATEDLIST = YES\n\n"                                                 )

    doxyfile.write("# The ENABLED_SECTIONS tag can be used to enable conditional documentation\n"      )
    doxyfile.write("# sections, marked by \if <section_label> ... \endif and \cond <section_label>\n"  )
    doxyfile.write("# ... \endcond blocks.\n\n"                                                        )

    doxyfile.write("ENABLED_SECTIONS = \n\n"                                                           )

    doxyfile.write("# The MAX_INITIALIZER_LINES tag determines the maximum number of lines that the\n" )
    doxyfile.write("# initial value of a variable or macro / define can have for it to appear in the\n")
    doxyfile.write("# documentation. If the initializer consists of more lines than specified here\n"  )
    doxyfile.write("# it will be hidden. Use a value of 0 to hide initializers completely. The\n"      )
    doxyfile.write("# appearance of the value of individual variables and macros / defines can be\n"   )
    doxyfile.write("# controlled using \showinitializer or \hideinitializer command in the\n"          )
    doxyfile.write("# documentation regardless of this setting.\n"                                     )
    doxyfile.write("# Minimum value: 0, maximum value: 10000, default value: 30.\n\n"                  )

    doxyfile.write("MAX_INITIALIZER_LINES = 30\n\n"                                                    )

    doxyfile.write("# Set the SHOW_USED_FILES tag to NO to disable the list of files generated at\n"   )
    doxyfile.write("# the bottom of the documentation of classes and structs. If set to YES, the\n"    )
    doxyfile.write("# list will mention the files that were used to generate the documentation.\n"     )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("SHOW_USED_FILES = YES\n\n"                                                         )

    doxyfile.write("# Set the SHOW_FILES tag to NO to disable the generation of the Files page. This\n")
    doxyfile.write("# will remove the Files entry from the Quick Index and from the Folder Tree View\n")
    doxyfile.write("# (if specified).\n"                                                               )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("SHOW_FILES = YES\n\n"                                                              )

    doxyfile.write("# Set the SHOW_NAMESPACES tag to NO to disable the generation of the Namespaces\n" )
    doxyfile.write("# page. This will remove the Namespaces entry from the Quick Index and from the\n" )
    doxyfile.write("# Folder Tree View (if specified).\n"                                              )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("SHOW_NAMESPACES = YES\n\n"                                                         )

    doxyfile.write("# The FILE_VERSION_FILTER tag can be used to specify a program or script that\n"   )
    doxyfile.write("# doxygen should invoke to get the current version for each file (typically from\n")
    doxyfile.write("# the version control system). Doxygen will invoke the program by executing (via\n")
    doxyfile.write("# popen()) the command command input-file, where command is the value of the\n"    )
    doxyfile.write("# FILE_VERSION_FILTER tag, and input-file is the name of an input file provided\n" )
    doxyfile.write("# by doxygen. Whatever the program writes to standard output is used as the file\n")
    doxyfile.write("# version. For an example see the documentation.\n\n"                              )

    doxyfile.write("FILE_VERSION_FILTER = \n\n"                                                        )

    doxyfile.write("# The LAYOUT_FILE tag can be used to specify a layout file which will be parsed\n" )
    doxyfile.write("# by doxygen. The layout file controls the global structure of the generated\n"    )
    doxyfile.write("# output files in an output format independent way. To create the layout file\n"   )
    doxyfile.write("# that represents doxygen's defaults, run doxygen with the -l option. You can\n"   )
    doxyfile.write("# optionally specify a file name after the option, if omitted DoxygenLayout.xml\n" )
    doxyfile.write("# will be used as the name of the layout file.\n"                                  )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that if you run doxygen from a directory containing a file called\n"        )
    doxyfile.write("# DoxygenLayout.xml, doxygen will parse it automatically even if the LAYOUT_FILE\n")
    doxyfile.write("# tag is left empty.\n\n"                                                          )

    doxyfile.write("LAYOUT_FILE = \n\n"                                                                )

    doxyfile.write("# The CITE_BIB_FILES tag can be used to specify one or more bib files containing\n")
    doxyfile.write("# the reference definitions. This must be a list of .bib files. The .bib\n"        )
    doxyfile.write("# extension is automatically appended if omitted. This requires the bibtex tool\n" )
    doxyfile.write("# to be installed. See also http://en.wikipedia.org/wiki/BibTeX for more info.\n"  )
    doxyfile.write("# For LaTeX the style of the bibliography can be controlled using\n"               )
    doxyfile.write("# LATEX_BIB_STYLE. To use this feature you need bibtex and perl available in the\n")
    doxyfile.write("# search path. See also \cite for info how to create references.\n\n"              )

    doxyfile.write("CITE_BIB_FILES = \n\n"                                                             )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to warning and progress messages\n"                )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# The QUIET tag can be used to turn on/off the messages that are generated to\n"   )
    doxyfile.write("# standard output by doxygen. If QUIET is set to YES this implies that the\n"      )
    doxyfile.write("# messages are off.\n"                                                             )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("QUIET = NO\n\n"                                                                    )

    doxyfile.write("# The WARNINGS tag can be used to turn on/off the warning messages that are\n"     )
    doxyfile.write("# generated to standard error (stderr) by doxygen. If WARNINGS is set to YES\n"    )
    doxyfile.write("# this implies that the warnings are on.\n"                                        )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Tip: Turn warnings on while writing the documentation.\n"                        )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("WARNINGS = YES\n\n"                                                                )

    doxyfile.write("# If the WARN_IF_UNDOCUMENTED tag is set to YES then doxygen will generate\n"      )
    doxyfile.write("# warnings for undocumented members. If EXTRACT_ALL is set to YES then this flag\n")
    doxyfile.write("# will automatically be disabled.\n"                                               )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("WARN_IF_UNDOCUMENTED = YES\n\n"                                                    )

    doxyfile.write("# If the WARN_IF_DOC_ERROR tag is set to YES, doxygen will generate warnings for\n")
    doxyfile.write("# potential errors in the documentation, such as not documenting some parameters\n")
    doxyfile.write("# in a documented function, or documenting parameters that don't exist or using\n" )
    doxyfile.write("# markup commands wrongly.\n"                                                      )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("WARN_IF_DOC_ERROR = YES\n\n"                                                       )

    doxyfile.write("# This WARN_NO_PARAMDOC option can be enabled to get warnings for functions that\n")
    doxyfile.write("# are documented, but have no documentation for their parameters or return\n"      )
    doxyfile.write("# value. If set to NO, doxygen will only warn about wrong or incomplete\n"         )
    doxyfile.write("# parameter documentation, but not about the absence of documentation.\n"          )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("WARN_NO_PARAMDOC = NO\n\n"                                                         )

    doxyfile.write("# If the WARN_AS_ERROR tag is set to YES then doxygen will immediately stop when\n")
    doxyfile.write("# a warning is encountered.\n"                                                     )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("WARN_AS_ERROR = NO\n\n"                                                            )

    doxyfile.write("# The WARN_FORMAT tag determines the format of the warning messages that doxygen\n")
    doxyfile.write("# can produce. The string should contain the $file, $line, and $text tags, which\n")
    doxyfile.write("# will be replaced by the file and line number from which the warning originated\n")
    doxyfile.write("# and the warning text. Optionally the format may contain $version, which will\n"  )
    doxyfile.write("# be replaced by the version of the file (if it could be obtained via\n"           )
    doxyfile.write("# FILE_VERSION_FILTER)\n"                                                          )
    doxyfile.write("# The default value is: $file:$line: $text.\n\n"                                   )

    doxyfile.write("WARN_FORMAT = \"$file:$line: $text\"\n\n"                                            )

    doxyfile.write("# The WARN_LOGFILE tag can be used to specify a file to which warning and error\n" )
    doxyfile.write("# messages should be written. If left blank the output is written to standard\n"   )
    doxyfile.write("# error (stderr).\n\n"                                                             )

    doxyfile.write("WARN_LOGFILE = \n\n"                                                               )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the input files\n"                              )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# The INPUT tag is used to specify the files and/or directories that contain\n"    )
    doxyfile.write("# documented source files. You may enter file names like myfile.cpp or\n"          )
    doxyfile.write("# directories like /usr/src/myproject. Separate the files or directories with\n"   )
    doxyfile.write("# spaces. See also FILE_PATTERNS and EXTENSION_MAPPING\n"                          )
    doxyfile.write("# Note: If this tag is empty the current directory is searched.\n\n"               )

    doxyfile.write("INPUT = ../include ../src ./doxygen/mainpage.dox\n\n"                                                   )

    doxyfile.write("# This tag can be used to specify the character encoding of the source files\n"    )
    doxyfile.write("# that doxygen parses. Internally doxygen uses the UTF-8 encoding. Doxygen uses\n" )
    doxyfile.write("# libiconv (or the iconv built into libc) for the transcoding. See the libiconv\n" )
    doxyfile.write("# documentation (see: http://www.gnu.org/software/libiconv) for the list of\n"     )
    doxyfile.write("# possible encodings.\n"                                                           )
    doxyfile.write("# The default value is: UTF-8.\n\n"                                                )

    doxyfile.write("INPUT_ENCODING = UTF-8\n\n"                                                        )

    doxyfile.write("# If the value of the INPUT tag contains directories, you can use the\n"           )
    doxyfile.write("# FILE_PATTERNS tag to specify one or more wildcard patterns (like *.cpp and\n"    )
    doxyfile.write("# *.h) to filter out the source-files in the directories.\n"                       )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that for custom extensions or not directly supported extensions you also\n" )
    doxyfile.write("# need to set EXTENSION_MAPPING for the extension otherwise the files are not\n"   )
    doxyfile.write("# read by doxygen.\n"                                                              )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# If left blank the following patterns are tested:*.c, *.cc, *.cxx, *.cpp,\n"      )
    doxyfile.write("# *.c++, *.java, *.ii, *.ixx, *.ipp, *.i++, *.inl, *.idl, *.ddl, *.odl, *.h,\n"    )
    doxyfile.write("# *.hh, *.hxx, *.hpp, *.h++, *.cs, *.d, *.php, *.php4, *.php5, *.phtml, *.inc,\n"  )
    doxyfile.write("# *.m, *.markdown, *.md, *.mm, *.dox, *.py, *.pyw, *.f90, *.f, *.for, *.tcl,\n"    )
    doxyfile.write("# *.vhd, *.vhdl, *.ucf, *.qsf, *.as and *.js.\n\n"                                 )

    doxyfile.write("FILE_PATTERNS = \n\n"                                                              )

    doxyfile.write("# The RECURSIVE tag can be used to specify whether or not subdirectories should\n" )
    doxyfile.write("# be searched for input files as well.\n"                                          )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("RECURSIVE = NO\n\n"                                                                )

    doxyfile.write("# The EXCLUDE tag can be used to specify files and/or directories that should be\n")
    doxyfile.write("# excluded from the INPUT source files. This way you can easily exclude a\n"       )
    doxyfile.write("# subdirectory from a directory tree whose root is specified with the INPUT tag.\n")
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that relative paths are relative to the directory from which doxygen is\n"  )
    doxyfile.write("# run.\n\n"                                                                        )

    doxyfile.write("EXCLUDE = \n\n"                                                                    )

    doxyfile.write("# The EXCLUDE_SYMLINKS tag can be used to select whether or not files or\n"        )
    doxyfile.write("# directories that are symbolic links (a Unix file system feature) are excluded\n" )
    doxyfile.write("# from the input.\n"                                                               )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXCLUDE_SYMLINKS = NO\n\n"                                                         )

    doxyfile.write("# If the value of the INPUT tag contains directories, you can use the\n"           )
    doxyfile.write("# EXCLUDE_PATTERNS tag to specify one or more wildcard patterns to exclude\n"      )
    doxyfile.write("# certain files from those directories.\n"                                         )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that the wildcards are matched against the file with absolute path, so to\n")
    doxyfile.write("# exclude all test directories for example use the pattern */test/*\n\n"           )

    doxyfile.write("EXCLUDE_PATTERNS = \n\n"                                                           )

    doxyfile.write("# The EXCLUDE_SYMBOLS tag can be used to specify one or more symbol names\n"       )
    doxyfile.write("# (namespaces, classes, functions, etc.) that should be excluded from the\n"       )
    doxyfile.write("# output. The symbol name can be a fully qualified name, a word, or if the\n"      )
    doxyfile.write("# wildcard * is used, a substring. Examples: ANamespace, AClass,\n"                )
    doxyfile.write("# AClass::ANamespace, ANamespace::*Test\n"                                         )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that the wildcards are matched against the file with absolute path, so to\n")
    doxyfile.write("# exclude all test directories use the pattern */test/*\n\n"                       )

    doxyfile.write("EXCLUDE_SYMBOLS = \n\n"                                                            )

    doxyfile.write("# The EXAMPLE_PATH tag can be used to specify one or more files or directories\n"  )
    doxyfile.write("# that contain example code fragments that are included (see the \include\n"       )
    doxyfile.write("# command).\n\n"                                                                   )

    doxyfile.write("EXAMPLE_PATH = ./doxygen/examples/\n\n"                                            )

    doxyfile.write("# If the value of the EXAMPLE_PATH tag contains directories, you can use the\n"    )
    doxyfile.write("# EXAMPLE_PATTERNS tag to specify one or more wildcard pattern (like *.cpp and\n"  )
    doxyfile.write("# *.h) to filter out the source-files in the directories. If left blank all\n"     )
    doxyfile.write("# files are included.\n\n"                                                         )

    doxyfile.write("EXAMPLE_PATTERNS = \n\n"                                                           )

    doxyfile.write("# If the EXAMPLE_RECURSIVE tag is set to YES then subdirectories will be\n"        )
    doxyfile.write("# searched for input files to be used with the \include or \dontinclude commands\n")
    doxyfile.write("# irrespective of the value of the RECURSIVE tag.\n"                               )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("EXAMPLE_RECURSIVE = NO\n\n"                                                        )

    doxyfile.write("# The IMAGE_PATH tag can be used to specify one or more files or directories\n"    )
    doxyfile.write("# that contain images that are to be included in the documentation (see the\n"     )
    doxyfile.write("# \image command).\n\n"                                                            )

    doxyfile.write("IMAGE_PATH = ./doxygen/uml/ \n\n"                                                  )

    doxyfile.write("# The INPUT_FILTER tag can be used to specify a program that doxygen should\n"     )
    doxyfile.write("# invoke to filter for each input file. Doxygen will invoke the filter program\n"  )
    doxyfile.write("# by executing (via popen()) the command:\n"                                       )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# <filter> <input-file>\n"                                                         )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# where <filter> is the value of the INPUT_FILTER tag, and <input-file> is the\n"  )
    doxyfile.write("# name of an input file. Doxygen will then use the output that the filter\n"       )
    doxyfile.write("# program writes to standard output. If FILTER_PATTERNS is specified, this tag\n"  )
    doxyfile.write("# will be ignored.\n"                                                              )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that the filter must not add or remove lines; it is applied before the\n"   )
    doxyfile.write("# code is scanned, but not when the output code is generated. If lines are added\n")
    doxyfile.write("# or removed, the anchors will not be placed correctly.\n"                         )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that for custom extensions or not directly supported extensions you also\n" )
    doxyfile.write("# need to set EXTENSION_MAPPING for the extension otherwise the files are not\n"   )
    doxyfile.write("# properly processed by doxygen.\n\n"                                              )

    doxyfile.write("INPUT_FILTER = \n\n"                                                               )

    doxyfile.write("# The FILTER_PATTERNS tag can be used to specify filters on a per file pattern\n"  )
    doxyfile.write("# basis. Doxygen will compare the file name with each pattern and apply the\n"     )
    doxyfile.write("# filter if there is a match. The filters are a list of the form: pattern=filter\n")
    doxyfile.write("# (like *.cpp=my_cpp_filter). See INPUT_FILTER for further information on how\n"   )
    doxyfile.write("# filters are used. If the FILTER_PATTERNS tag is empty or if none of the\n"       )
    doxyfile.write("# patterns match the file name, INPUT_FILTER is applied.\n"                        )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that for custom extensions or not directly supported extensions you also\n" )
    doxyfile.write("# need to set EXTENSION_MAPPING for the extension otherwise the files are not\n"   )
    doxyfile.write("# properly processed by doxygen.\n\n"                                              )

    doxyfile.write("FILTER_PATTERNS = \n\n"                                                            )

    doxyfile.write("# If the FILTER_SOURCE_FILES tag is set to YES, the input filter (if set using\n"  )
    doxyfile.write("# INPUT_FILTER) will also be used to filter the input files that are used for\n"   )
    doxyfile.write("# producing the source files to browse (i.e. when SOURCE_BROWSER is set to YES).\n")
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("FILTER_SOURCE_FILES = NO\n\n"                                                      )

    doxyfile.write("# The FILTER_SOURCE_PATTERNS tag can be used to specify source filters per file\n" )
    doxyfile.write("# pattern. A pattern will override the setting for FILTER_PATTERN (if any) and\n"  )
    doxyfile.write("# it is also possible to disable source filtering for a specific pattern using\n"  )
    doxyfile.write("# *.ext= (so without naming a filter).\n"                                          )
    doxyfile.write("# This tag requires that the tag FILTER_SOURCE_FILES is set to YES.\n\n"           )

    doxyfile.write("FILTER_SOURCE_PATTERNS = \n\n"                                                     )

    doxyfile.write("# If the USE_MDFILE_AS_MAINPAGE tag refers to the name of a markdown file that\n"  )
    doxyfile.write("# is part of the input, its contents will be placed on the main page\n"            )
    doxyfile.write("# (index.html). This can be useful if you have a project on for instance GitHub\n" )
    doxyfile.write("# and want to reuse the introduction page also for the doxygen output.\n\n"        )

    doxyfile.write("USE_MDFILE_AS_MAINPAGE = \n\n"                                                     )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to source browsing\n"                              )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the SOURCE_BROWSER tag is set to YES then a list of source files will be\n"   )
    doxyfile.write("# generated. Documented entities will be cross-referenced with these sources.\n"   )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note: To get rid of all source code in the generated output, make sure that\n"   )
    doxyfile.write("# also VERBATIM_HEADERS is set to NO.\n"                                           )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("SOURCE_BROWSER = NO\n\n"                                                           )

    doxyfile.write("# Setting the INLINE_SOURCES tag to YES will include the body of functions,\n"     )
    doxyfile.write("# classes and enums directly into the documentation.\n"                            )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("INLINE_SOURCES = NO\n\n"                                                           )

    doxyfile.write("# Setting the STRIP_CODE_COMMENTS tag to YES will instruct doxygen to hide any\n"  )
    doxyfile.write("# special comment blocks from generated source code fragments. Normal C, C++ and\n")
    doxyfile.write("# Fortran comments will always remain visible.\n"                                  )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("STRIP_CODE_COMMENTS = YES\n\n"                                                     )

    doxyfile.write("# If the REFERENCED_BY_RELATION tag is set to YES then for each documented\n"      )
    doxyfile.write("# function all documented functions referencing it will be listed.\n"              )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("REFERENCED_BY_RELATION = NO\n\n"                                                   )

    doxyfile.write("# If the REFERENCES_RELATION tag is set to YES then for each documented function\n")
    doxyfile.write("# all documented entities called/used by that function will be listed.\n"          )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("REFERENCES_RELATION = NO\n\n"                                                      )

    doxyfile.write("# If the REFERENCES_LINK_SOURCE tag is set to YES and SOURCE_BROWSER tag is set\n" )
    doxyfile.write("# to YES then the hyperlinks from functions in REFERENCES_RELATION and\n"          )
    doxyfile.write("# REFERENCED_BY_RELATION lists will link to the source code. Otherwise they will\n")
    doxyfile.write("# link to the documentation.\n"                                                    )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("REFERENCES_LINK_SOURCE = YES\n\n"                                                  )

    doxyfile.write("# If SOURCE_TOOLTIPS is enabled (the default) then hovering a hyperlink in the\n"  )
    doxyfile.write("# source code will show a tooltip with additional information such as prototype,\n")
    doxyfile.write("# brief description and links to the definition and documentation. Since this\n"   )
    doxyfile.write("# will make the HTML file larger and loading of large files a bit slower, you\n"   )
    doxyfile.write("# can opt to disable this feature.\n"                                              )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag SOURCE_BROWSER is set to YES.\n\n"                )

    doxyfile.write("SOURCE_TOOLTIPS = YES\n\n"                                                         )

    doxyfile.write("# If the USE_HTAGS tag is set to YES then the references to source code will\n"    )
    doxyfile.write("# point to the HTML generated by the htags(1) tool instead of doxygen built-in\n"  )
    doxyfile.write("# source browser. The htags tool is part of GNU's global source tagging system\n"  )
    doxyfile.write("# (see http://www.gnu.org/software/global/global.html). You will need version\n"   )
    doxyfile.write("# 4.8.6 or higher.\n"                                                              )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# To use it do the following:\n"                                                   )
    doxyfile.write("# - Install the latest version of global\n"                                        )
    doxyfile.write("# - Enable SOURCE_BROWSER and USE_HTAGS in the config file\n"                      )
    doxyfile.write("# - Make sure the INPUT points to the root of the source tree\n"                   )
    doxyfile.write("# - Run doxygen as normal\n"                                                       )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Doxygen will invoke htags (and that will in turn invoke gtags), so these\n"      )
    doxyfile.write("# tools must be available from the command line (i.e. in the search path).\n"      )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# The result: instead of the source browser generated by doxygen, the links to\n"  )
    doxyfile.write("# source code will now point to the output of htags.\n"                            )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag SOURCE_BROWSER is set to YES.\n\n"                )

    doxyfile.write("USE_HTAGS = NO\n\n"                                                                )

    doxyfile.write("# If the VERBATIM_HEADERS tag is set the YES then doxygen will generate a\n"       )
    doxyfile.write("# verbatim copy of the header file for each class for which an include is\n"       )
    doxyfile.write("# specified. Set to NO to disable this.\n"                                         )
    doxyfile.write("# See also: Section \class.\n"                                                     )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("VERBATIM_HEADERS = YES\n\n"                                                        )

    doxyfile.write("# If the CLANG_ASSISTED_PARSING tag is set to YES then doxygen will use the\n"     )
    doxyfile.write("# clang parser (see: http://clang.llvm.org/) for more accurate parsing at the\n"   )
    doxyfile.write("# cost of reduced performance. This can be particularly helpful with template\n"   )
    doxyfile.write("# rich C++ code for which doxygen's built-in parser lacks the necessary type\n"    )
    doxyfile.write("# information.\n"                                                                  )
    doxyfile.write("# Note: The availability of this option depends on whether or not doxygen was\n"   )
    doxyfile.write("# generated with the -Duse-libclang=ON option for CMake.\n"                        )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("CLANG_ASSISTED_PARSING = NO\n\n"                                                   )

    doxyfile.write("# If clang assisted parsing is enabled you can provide the compiler with command\n")
    doxyfile.write("# line options that you would normally use when invoking the compiler. Note that\n")
    doxyfile.write("# the include paths will already be set by doxygen for the files and directories\n")
    doxyfile.write("# specified with INPUT and INCLUDE_PATH.\n"                                        )
    doxyfile.write("# This tag requires that the tag CLANG_ASSISTED_PARSING is set to YES.\n\n"        )

    doxyfile.write("CLANG_OPTIONS = \n\n"                                                              )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the alphabetical class index\n"                 )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the ALPHABETICAL_INDEX tag is set to YES, an alphabetical index of all\n"     )
    doxyfile.write("# compounds will be generated. Enable this if the project contains a lot of\n"     )
    doxyfile.write("# classes, structs, unions or interfaces.\n"                                       )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("ALPHABETICAL_INDEX = YES\n\n"                                                      )

    doxyfile.write("# The COLS_IN_ALPHA_INDEX tag can be used to specify the number of columns in\n"   )
    doxyfile.write("# which the alphabetical index list will be split.\n"                              )
    doxyfile.write("# Minimum value: 1, maximum value: 20, default value: 5.\n"                        )
    doxyfile.write("# This tag requires that the tag ALPHABETICAL_INDEX is set to YES.\n\n"            )

    doxyfile.write("COLS_IN_ALPHA_INDEX = 5\n\n"                                                       )

    doxyfile.write("# In case all classes in a project start with a common prefix, all classes will\n" )
    doxyfile.write("# be put under the same header in the alphabetical index. The IGNORE_PREFIX tag\n" )
    doxyfile.write("# can be used to specify a prefix (or a list of prefixes) that should be ignored\n")
    doxyfile.write("# while generating the index headers.\n"                                           )
    doxyfile.write("# This tag requires that the tag ALPHABETICAL_INDEX is set to YES.\n\n"            )

    doxyfile.write("IGNORE_PREFIX = \n\n"                                                              )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the HTML output\n"                              )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_HTML tag is set to YES, doxygen will generate HTML output\n"     )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("GENERATE_HTML = YES\n\n"                                                           )

    doxyfile.write("# The HTML_OUTPUT tag is used to specify where the HTML docs will be put. If a\n"  )
    doxyfile.write("# relative path is entered the value of OUTPUT_DIRECTORY will be put in front of\n")
    doxyfile.write("# it.\n"                                                                           )
    doxyfile.write("# The default directory is: html.\n"                                               )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_OUTPUT = html\n\n"                                                            )

    doxyfile.write("# The HTML_FILE_EXTENSION tag can be used to specify the file extension for each\n")
    doxyfile.write("# generated HTML page (for example: .htm, .php, .asp).\n"                          )
    doxyfile.write("# The default value is: .html.\n"                                                  )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_FILE_EXTENSION = .html\n\n"                                                   )

    doxyfile.write("# The HTML_HEADER tag can be used to specify a user-defined HTML header file for\n")
    doxyfile.write("# each generated HTML page. If the tag is left blank doxygen will generate a\n"    )
    doxyfile.write("# standard header.\n"                                                              )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# To get valid HTML the header file that includes any scripts and style sheets\n"  )
    doxyfile.write("# that doxygen needs, which is dependent on the configuration options used (e.g.\n")
    doxyfile.write("# the setting GENERATE_TREEVIEW). It is highly recommended to start with a\n"      )
    doxyfile.write("# default header using\n"                                                          )
    doxyfile.write("# doxygen -w html new_header.html new_footer.html new_stylesheet.css\n"            )
    doxyfile.write("# YourConfigFile\n"                                                                )
    doxyfile.write("# and then modify the file new_header.html. See also section \"Doxygen usage\"\n"  )
    doxyfile.write("# for information on how to generate the default header that doxygen normally\n"   )
    doxyfile.write("# uses.\n"                                                                         )
    doxyfile.write("# Note: The header is subject to change so you typically have to regenerate the\n" )
    doxyfile.write("# default header when upgrading to a newer version of doxygen. For a description\n")
    doxyfile.write("# of the possible markers and block names see the documentation.\n"                )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_HEADER = \n\n"                                                                )

    doxyfile.write("# The HTML_FOOTER tag can be used to specify a user-defined HTML footer for each\n")
    doxyfile.write("# generated HTML page. If the tag is left blank doxygen will generate a standard\n")
    doxyfile.write("# footer. See HTML_HEADER for more information on how to generate a default\n"     )
    doxyfile.write("# footer and what special commands can be used inside the footer. See also\n"      )
    doxyfile.write("# section \"Doxygen usage\" for information on how to generate the default footer\n")
    doxyfile.write("# that doxygen normally uses.\n"                                                   )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_FOOTER = \n\n"                                                                )

    doxyfile.write("# The HTML_STYLESHEET tag can be used to specify a user-defined cascading style\n" )
    doxyfile.write("# sheet that is used by each HTML page. It can be used to fine-tune the look of\n" )
    doxyfile.write("# the HTML output. If left blank doxygen will generate a default style sheet.\n"   )
    doxyfile.write("# See also section \"Doxygen usage\" for information on how to generate the style\n")
    doxyfile.write("# sheet that doxygen normally uses.\n"                                             )
    doxyfile.write("# Note: It is recommended to use HTML_EXTRA_STYLESHEET instead of this tag, as\n"  )
    doxyfile.write("# it is more robust and this tag (HTML_STYLESHEET) will in the future become\n"    )
    doxyfile.write("# obsolete.\n"                                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_STYLESHEET = \n\n"                                                            )

    doxyfile.write("# The HTML_EXTRA_STYLESHEET tag can be used to specify additional user-defined\n"  )
    doxyfile.write("# cascading style sheets that are included after the standard style sheets\n"      )
    doxyfile.write("# created by doxygen. Using this option one can overrule certain style aspects.\n" )
    doxyfile.write("# This is preferred over using HTML_STYLESHEET since it does not replace the\n"    )
    doxyfile.write("# standard style sheet and is therefore more robust against future updates.\n"     )
    doxyfile.write("# Doxygen will copy the style sheet files to the output directory.\n"              )
    doxyfile.write("# Note: The order of the extra style sheet files is of importance (e.g. the last\n")
    doxyfile.write("# style sheet in the list overrules the setting of the previous ones in the\n"     )
    doxyfile.write("# list). For an example see the documentation.\n"                                  )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_EXTRA_STYLESHEET = \n\n"                                                      )

    doxyfile.write("# The HTML_EXTRA_FILES tag can be used to specify one or more extra images or\n"   )
    doxyfile.write("# other source files which should be copied to the HTML output directory. Note\n"  )
    doxyfile.write("# that these files will be copied to the base HTML output directory. Use the\n"    )
    doxyfile.write("# $relpath^ marker in the HTML_HEADER and/or HTML_FOOTER files to load these\n"    )
    doxyfile.write("# files. In the HTML_STYLESHEET file, use the file name only. Also note that the\n")
    doxyfile.write("# files will be copied as-is; there are no commands or markers available.\n"       )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_EXTRA_FILES = \n\n"                                                           )

    doxyfile.write("# The HTML_COLORSTYLE_HUE tag controls the color of the HTML output. Doxygen\n"    )
    doxyfile.write("# will adjust the colors in the style sheet and background images according to\n"  )
    doxyfile.write("# this color. Hue is specified as an angle on a colorwheel, see\n"                 )
    doxyfile.write("# http://en.wikipedia.org/wiki/Hue for more information. For instance the value\n" )
    doxyfile.write("# 0 represents red, 60 is yellow, 120 is green, 180 is cyan, 240 is blue, 300\n"   )
    doxyfile.write("# purple, and 360 is red again.\n"                                                 )
    doxyfile.write("# Minimum value: 0, maximum value: 359, default value: 220.\n"                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_COLORSTYLE_HUE = 220\n\n"                                                     )

    doxyfile.write("# The HTML_COLORSTYLE_SAT tag controls the purity (or saturation) of the colors\n" )
    doxyfile.write("# in the HTML output. For a value of 0 the output will use grayscales only. A\n"   )
    doxyfile.write("# value of 255 will produce the most vivid colors.\n"                              )
    doxyfile.write("# Minimum value: 0, maximum value: 255, default value: 100.\n"                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_COLORSTYLE_SAT = 100\n\n"                                                     )

    doxyfile.write("# The HTML_COLORSTYLE_GAMMA tag controls the gamma correction applied to the\n"    )
    doxyfile.write("# luminance component of the colors in the HTML output. Values below 100\n"        )
    doxyfile.write("# gradually make the output lighter, whereas values above 100 make the output\n"   )
    doxyfile.write("# darker. The value divided by 100 is the actual gamma applied, so 80 represents\n")
    doxyfile.write("# a gamma of 0.8, The value 220 represents a gamma of 2.2, and 100 does not\n"     )
    doxyfile.write("# change the gamma.\n"                                                             )
    doxyfile.write("# Minimum value: 40, maximum value: 240, default value: 80.\n"                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_COLORSTYLE_GAMMA = 80\n\n"                                                    )

    doxyfile.write("# If the HTML_TIMESTAMP tag is set to YES then the footer of each generated HTML\n")
    doxyfile.write("# page will contain the date and time when the page was generated. Setting this\n" )
    doxyfile.write("# to YES can help to show when doxygen was last run and thus if the\n"             )
    doxyfile.write("# documentation is up to date.\n"                                                  )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_TIMESTAMP = NO\n\n"                                                           )

    doxyfile.write("# If the HTML_DYNAMIC_SECTIONS tag is set to YES then the generated HTML\n"        )
    doxyfile.write("# documentation will contain sections that can be hidden and shown after the\n"    )
    doxyfile.write("# page has loaded.\n"                                                              )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_DYNAMIC_SECTIONS = NO\n\n"                                                    )

    doxyfile.write("# With HTML_INDEX_NUM_ENTRIES one can control the preferred number of entries\n"   )
    doxyfile.write("# shown in the various tree structured indices initially; the user can expand\n"   )
    doxyfile.write("# and collapse entries dynamically later on. Doxygen will expand the tree to\n"    )
    doxyfile.write("# such a level that at most the specified number of entries are visible (unless\n" )
    doxyfile.write("# a fully collapsed tree already exceeds this amount). So setting the number of\n" )
    doxyfile.write("# entries 1 will produce a full collapsed tree by default. 0 is a special value\n" )
    doxyfile.write("# representing an infinite number of entries and will result in a full expanded\n" )
    doxyfile.write("# tree by default.\n"                                                              )
    doxyfile.write("# Minimum value: 0, maximum value: 9999, default value: 100.\n"                    )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("HTML_INDEX_NUM_ENTRIES = 100\n\n"                                                  )

    doxyfile.write("# If the GENERATE_DOCSET tag is set to YES, additional index files will be\n"      )
    doxyfile.write("# generated that can be used as input for Apple's Xcode 3 integrated development\n")
    doxyfile.write("# environment (see: http://developer.apple.com/tools/xcode/), introduced with\n"   )
    doxyfile.write("# OSX 10.5 (Leopard). To create a documentation set, doxygen will generate a\n"    )
    doxyfile.write("# Makefile in the HTML output directory. Running make will produce the docset in\n")
    doxyfile.write("# that directory and running make install will install the docset in\n"            )
    doxyfile.write("# ~/Library/Developer/Shared/Documentation/DocSets so that Xcode will find it at\n")
    doxyfile.write("# startup. See http://developer.apple.com/tools/creatingdocsetswithdoxygen.html\n" )
    doxyfile.write("# for more information.\n"                                                         )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("GENERATE_DOCSET = NO\n\n"                                                          )

    doxyfile.write("# This tag determines the name of the docset feed. A documentation feed provides\n")
    doxyfile.write("# an umbrella under which multiple documentation sets from a single provider\n"    )
    doxyfile.write("# (such as a company or product suite) can be grouped.\n"                          )
    doxyfile.write("# The default value is: Doxygen generated docs.\n"                                 )
    doxyfile.write("# This tag requires that the tag GENERATE_DOCSET is set to YES.\n\n"               )

    doxyfile.write("DOCSET_FEEDNAME = \"Doxygen generated docs\"\n\n"                                  )

    doxyfile.write("# This tag specifies a string that should uniquely identify the documentation\n"   )
    doxyfile.write("# set bundle. This should be a reverse domain-name style string, e.g.\n"           )
    doxyfile.write("# com.mycompany.MyDocSet. Doxygen will append .docset to the name.\n"              )
    doxyfile.write("# The default value is: org.doxygen.Project.\n"                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_DOCSET is set to YES.\n\n"               )

    doxyfile.write("DOCSET_BUNDLE_ID = org.doxygen.Project\n\n"                                        )

    doxyfile.write("# The DOCSET_PUBLISHER_ID tag specifies a string that should uniquely identify\n"  )
    doxyfile.write("# the documentation publisher. This should be a reverse domain-name style\n"       )
    doxyfile.write("# string, e.g. com.mycompany.MyDocSet.documentation.\n"                            )
    doxyfile.write("# The default value is: org.doxygen.Publisher.\n"                                  )
    doxyfile.write("# This tag requires that the tag GENERATE_DOCSET is set to YES.\n\n"               )

    doxyfile.write("DOCSET_PUBLISHER_ID = org.doxygen.Publisher\n\n"                                   )

    doxyfile.write("# The DOCSET_PUBLISHER_NAME tag identifies the documentation publisher.\n"         )
    doxyfile.write("# The default value is: Publisher.\n"                                              )
    doxyfile.write("# This tag requires that the tag GENERATE_DOCSET is set to YES.\n\n"               )

    doxyfile.write("DOCSET_PUBLISHER_NAME = Publisher\n\n"                                             )

    doxyfile.write("# If the GENERATE_HTMLHELP tag is set to YES then doxygen generates three\n"       )
    doxyfile.write("# additional HTML index files: index.hhp, index.hhc, and index.hhk. The\n"         )
    doxyfile.write("# index.hhp is a project file that can be read by Microsoft's HTML Help Workshop\n")
    doxyfile.write("# (see: http://www.microsoft.com/en-us/download/details.aspx?id=21138) on\n"       )
    doxyfile.write("# Windows.\n"                                                                      )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# The HTML Help Workshop contains a compiler that can convert all HTML output\n"   )
    doxyfile.write("# generated by doxygen into a single compiled HTML file (.chm). Compiled HTML\n"   )
    doxyfile.write("# files are now used as the Windows 98 help format, and will replace the old\n"    )
    doxyfile.write("# Windows help format (.hlp) on all Windows platforms in the future. Compressed\n" )
    doxyfile.write("# HTML files also contain an index, a table of contents, and you can search for\n" )
    doxyfile.write("# words in the documentation. The HTML workshop also contains a viewer for\n"      )
    doxyfile.write("# compressed HTML files.\n"                                                        )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("GENERATE_HTMLHELP = NO\n\n"                                                        )

    doxyfile.write("# The CHM_FILE tag can be used to specify the file name of the resulting .chm\n"   )
    doxyfile.write("# file. You can add a path in front of the file if the result should not be\n"     )
    doxyfile.write("# written to the html output directory.\n"                                         )
    doxyfile.write("# This tag requires that the tag GENERATE_HTMLHELP is set to YES.\n\n"             )

    doxyfile.write("CHM_FILE = \n\n"                                                                   )

    doxyfile.write("# The HHC_LOCATION tag can be used to specify the location (absolute path\n"       )
    doxyfile.write("# including file name) of the HTML help compiler (hhc.exe). If non-empty,\n"       )
    doxyfile.write("# doxygen will try to run the HTML help compiler on the generated index.hhp.\n"    )
    doxyfile.write("# The file has to be specified with full path.\n"                                  )
    doxyfile.write("# This tag requires that the tag GENERATE_HTMLHELP is set to YES.\n\n"             )

    doxyfile.write("HHC_LOCATION = \n\n"                                                               )

    doxyfile.write("# The GENERATE_CHI flag controls if a separate .chi index file is generated\n"     )
    doxyfile.write("# (YES) or that it should be included in the master .chm file (NO).\n"             )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTMLHELP is set to YES.\n\n"             )

    doxyfile.write("GENERATE_CHI = NO\n\n"                                                             )

    doxyfile.write("# The CHM_INDEX_ENCODING is used to encode HtmlHelp index (hhk), content (hhc)\n"  )
    doxyfile.write("# and project file content.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTMLHELP is set to YES.\n\n"             )

    doxyfile.write("CHM_INDEX_ENCODING = \n\n"                                                         )

    doxyfile.write("# The BINARY_TOC flag controls whether a binary table of contents is generated\n"  )
    doxyfile.write("# (YES) or a normal table of contents (NO) in the .chm file. Furthermore it\n"     )
    doxyfile.write("# enables the Previous and Next buttons.\n"                                        )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTMLHELP is set to YES.\n\n"             )

    doxyfile.write("BINARY_TOC = NO\n\n"                                                               )

    doxyfile.write("# The TOC_EXPAND flag can be set to YES to add extra items for group members to\n" )
    doxyfile.write("# the table of contents of the HTML help documentation and to the tree view.\n"    )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTMLHELP is set to YES.\n\n"             )

    doxyfile.write("TOC_EXPAND = NO\n\n"                                                               )

    doxyfile.write("# If the GENERATE_QHP tag is set to YES and both QHP_NAMESPACE and\n"              )
    doxyfile.write("# QHP_VIRTUAL_FOLDER are set, an additional index file will be generated that\n"   )
    doxyfile.write("# can be used as input for Qt's qhelpgenerator to generate a Qt Compressed Help\n" )
    doxyfile.write("# (.qch) of the generated HTML documentation.\n"                                   )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("GENERATE_QHP = NO\n\n"                                                             )

    doxyfile.write("# If the QHG_LOCATION tag is specified, the QCH_FILE tag can be used to specify\n" )
    doxyfile.write("# the file name of the resulting .qch file. The path specified is relative to\n"   )
    doxyfile.write("# the HTML output folder.\n"                                                       )
    doxyfile.write("# This tag requires that the tag GENERATE_QHP is set to YES.\n\n"                  )

    doxyfile.write("QCH_FILE = \n\n"                                                                   )

    doxyfile.write("# The QHP_NAMESPACE tag specifies the namespace to use when generating Qt Help\n"  )
    doxyfile.write("# Project output. For more information please see Qt Help Project / Namespace\n"   )
    doxyfile.write("# (see: http://qt-project.org/doc/qt-4.8/qthelpproject.html#namespace).\n"         )
    doxyfile.write("# The default value is: org.doxygen.Project.\n"                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_QHP is set to YES.\n\n"                  )

    doxyfile.write("QHP_NAMESPACE = org.doxygen.Project\n\n"                                           )

    doxyfile.write("# The QHP_VIRTUAL_FOLDER tag specifies the namespace to use when generating Qt\n"  )
    doxyfile.write("# Help Project output. For more information please see Qt Help Project / Virtual\n")
    doxyfile.write("# Folders (see: http://qt-project.org/doc/qt-4.8/qthelpproject.html#virtual-\n"    )
    doxyfile.write("# folders).\n"                                                                     )
    doxyfile.write("# The default value is: doc.\n"                                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_QHP is set to YES.\n\n"                  )

    doxyfile.write("QHP_VIRTUAL_FOLDER = doc\n\n"                                                      )

    doxyfile.write("# If the QHP_CUST_FILTER_NAME tag is set, it specifies the name of a custom\n"     )
    doxyfile.write("# filter to add. For more information please see Qt Help Project / Custom\n"       )
    doxyfile.write("# Filters (see: http://qt-project.org/doc/qt-4.8/qthelpproject.html#custom-\n"     )
    doxyfile.write("# filters).\n"                                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_QHP is set to YES.\n\n"                  )

    doxyfile.write("QHP_CUST_FILTER_NAME = \n\n"                                                       )

    doxyfile.write("# The QHP_CUST_FILTER_ATTRS tag specifies the list of the attributes of the\n"     )
    doxyfile.write("# custom filter to add. For more information please see Qt Help Project / Custom\n")
    doxyfile.write("# Filters (see: http://qt-project.org/doc/qt-4.8/qthelpproject.html#custom-\n"     )
    doxyfile.write("# filters).\n"                                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_QHP is set to YES.\n\n"                  )

    doxyfile.write("QHP_CUST_FILTER_ATTRS = \n\n"                                                      )

    doxyfile.write("# The QHP_SECT_FILTER_ATTRS tag specifies the list of the attributes this\n"       )
    doxyfile.write("# project's filter section matches. Qt Help Project / Filter Attributes (see:\n"   )
    doxyfile.write("# http://qt-project.org/doc/qt-4.8/qthelpproject.html#filter-attributes).\n"       )
    doxyfile.write("# This tag requires that the tag GENERATE_QHP is set to YES.\n\n"                  )

    doxyfile.write("QHP_SECT_FILTER_ATTRS = \n\n"                                                      )

    doxyfile.write("# The QHG_LOCATION tag can be used to specify the location of Qt's\n"              )
    doxyfile.write("# qhelpgenerator. If non-empty doxygen will try to run qhelpgenerator on the\n"    )
    doxyfile.write("# generated .qhp file.\n"                                                          )
    doxyfile.write("# This tag requires that the tag GENERATE_QHP is set to YES.\n\n"                  )

    doxyfile.write("QHG_LOCATION = \n\n"                                                               )

    doxyfile.write("# If the GENERATE_ECLIPSEHELP tag is set to YES, additional index files will be\n" )
    doxyfile.write("# generated, together with the HTML files, they form an Eclipse help plugin. To\n" )
    doxyfile.write("# install this plugin and make it available under the help contents menu in\n"     )
    doxyfile.write("# Eclipse, the contents of the directory containing the HTML and XML files needs\n")
    doxyfile.write("# to be copied into the plugins directory of eclipse. The name of the directory\n" )
    doxyfile.write("# within the plugins directory should be the same as the ECLIPSE_DOC_ID value.\n"  )
    doxyfile.write("# After copying Eclipse needs to be restarted before the help appears.\n"          )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("GENERATE_ECLIPSEHELP = NO\n\n"                                                     )

    doxyfile.write("# A unique identifier for the Eclipse help plugin. When installing the plugin\n"   )
    doxyfile.write("# the directory name containing the HTML and XML files should also have this\n"    )
    doxyfile.write("# name. Each documentation set should have its own identifier.\n"                  )
    doxyfile.write("# The default value is: org.doxygen.Project.\n"                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_ECLIPSEHELP is set to YES.\n\n"          )

    doxyfile.write("ECLIPSE_DOC_ID = org.doxygen.Project\n\n"                                          )

    doxyfile.write("# If you want full control over the layout of the generated HTML pages it might\n" )
    doxyfile.write("# be necessary to disable the index and replace it with your own. The\n"           )
    doxyfile.write("# DISABLE_INDEX tag can be used to turn on/off the condensed index (tabs) at top\n")
    doxyfile.write("# of each HTML page. A value of NO enables the index and the value YES disables\n" )
    doxyfile.write("# it. Since the tabs in the index contain the same information as the navigation\n")
    doxyfile.write("# tree, you can set this option to YES if you also set GENERATE_TREEVIEW to YES.\n")
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("DISABLE_INDEX = NO\n\n"                                                            )

    doxyfile.write("# The GENERATE_TREEVIEW tag is used to specify whether a tree-like index\n"        )
    doxyfile.write("# structure should be generated to display hierarchical information. If the tag\n" )
    doxyfile.write("# value is set to YES, a side panel will be generated containing a tree-like\n"    )
    doxyfile.write("# index structure (just like the one that is generated for HTML Help). For this\n" )
    doxyfile.write("# to work a browser that supports JavaScript, DHTML, CSS and frames is required\n" )
    doxyfile.write("# (i.e. any modern browser). Windows users are probably better off using the\n"    )
    doxyfile.write("# HTML help feature. Via custom style sheets (see HTML_EXTRA_STYLESHEET) one can\n")
    doxyfile.write("# further fine-tune the look of the index. As an example, the default style\n"     )
    doxyfile.write("# sheet generated by doxygen has an example that shows how to put an image at\n"   )
    doxyfile.write("# the root of the tree instead of the PROJECT_NAME. Since the tree basically has\n")
    doxyfile.write("# the same information as the tab index, you could consider setting\n"             )
    doxyfile.write("# DISABLE_INDEX to YES when enabling this option.\n"                               )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("GENERATE_TREEVIEW = YES\n\n"                                                       )

    doxyfile.write("# The ENUM_VALUES_PER_LINE tag can be used to set the number of enum values that\n")
    doxyfile.write("# doxygen will group on one line in the generated HTML documentation.\n"           )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that a value of 0 will completely suppress the enum values from appearing\n")
    doxyfile.write("# in the overview section.\n"                                                      )
    doxyfile.write("# Minimum value: 0, maximum value: 20, default value: 4.\n"                        )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("ENUM_VALUES_PER_LINE = 4\n\n"                                                      )

    doxyfile.write("# If the treeview is enabled (see GENERATE_TREEVIEW) then this tag can be used\n"  )
    doxyfile.write("# to set the initial width (in pixels) of the frame in which the tree is shown.\n" )
    doxyfile.write("# Minimum value: 0, maximum value: 1500, default value: 250.\n"                    )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("TREEVIEW_WIDTH = 250\n\n"                                                          )

    doxyfile.write("# If the EXT_LINKS_IN_WINDOW option is set to YES, doxygen will open links to\n"   )
    doxyfile.write("# external symbols imported via tag files in a separate window.\n"                 )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("EXT_LINKS_IN_WINDOW = NO\n\n"                                                      )

    doxyfile.write("# Use this tag to change the font size of LaTeX formulas included as images in\n"  )
    doxyfile.write("# the HTML documentation. When you change the font size after a successful\n"      )
    doxyfile.write("# doxygen run you need to manually remove any form_*.png images from the HTML\n"   )
    doxyfile.write("# output directory to force them to be regenerated.\n"                             )
    doxyfile.write("# Minimum value: 8, maximum value: 50, default value: 10.\n"                       )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("FORMULA_FONTSIZE = 10\n\n"                                                         )

    doxyfile.write("# Use the FORMULA_TRANPARENT tag to determine whether or not the images\n"         )
    doxyfile.write("# generated for formulas are transparent PNGs. Transparent PNGs are not\n"         )
    doxyfile.write("# supported properly for IE 6.0, but are supported on all modern browsers.\n"      )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that when changing this option you need to delete any form_*.png files in\n")
    doxyfile.write("# the HTML output directory before the changes have effect.\n"                     )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("FORMULA_TRANSPARENT = YES\n\n"                                                     )

    doxyfile.write("# Enable the USE_MATHJAX option to render LaTeX formulas using MathJax (see\n"     )
    doxyfile.write("# http://www.mathjax.org) which uses client side Javascript for the rendering\n"   )
    doxyfile.write("# instead of using pre-rendered bitmaps. Use this if you do not have LaTeX\n"      )
    doxyfile.write("# installed or if you want to formulas look prettier in the HTML output. When\n"   )
    doxyfile.write("# enabled you may also need to install MathJax separately and configure the path\n")
    doxyfile.write("# to it using the MATHJAX_RELPATH option.\n"                                       )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("USE_MATHJAX = NO\n\n"                                                              )

    doxyfile.write("# When MathJax is enabled you can set the default output format to be used for\n"  )
    doxyfile.write("# the MathJax output. See the MathJax site (see:\n"                                )
    doxyfile.write("# http://docs.mathjax.org/en/latest/output.html) for more details.\n"              )
    doxyfile.write("# Possible values are: HTML-CSS (which is slower, but has the best\n"              )
    doxyfile.write("# compatibility), NativeMML (i.e. MathML) and SVG.\n"                              )
    doxyfile.write("# The default value is: HTML-CSS.\n"                                               )
    doxyfile.write("# This tag requires that the tag USE_MATHJAX is set to YES.\n\n"                   )

    doxyfile.write("MATHJAX_FORMAT = HTML-CSS\n\n"                                                     )

    doxyfile.write("# When MathJax is enabled you need to specify the location relative to the HTML\n" )
    doxyfile.write("# output directory using the MATHJAX_RELPATH option. The destination directory\n"  )
    doxyfile.write("# should contain the MathJax.js script. For instance, if the mathjax directory\n"  )
    doxyfile.write("# is located at the same level as the HTML output directory, then\n"               )
    doxyfile.write("# MATHJAX_RELPATH should be ../mathjax. The default value points to the MathJax\n" )
    doxyfile.write("# Content Delivery Network so you can quickly see the result without installing\n" )
    doxyfile.write("# MathJax. However, it is strongly recommended to install a local copy of\n"       )
    doxyfile.write("# MathJax from http://www.mathjax.org before deployment.\n"                        )
    doxyfile.write("# The default value is: http://cdn.mathjax.org/mathjax/latest.\n"                  )
    doxyfile.write("# This tag requires that the tag USE_MATHJAX is set to YES.\n\n"                   )

    doxyfile.write("MATHJAX_RELPATH = http://cdn.mathjax.org/mathjax/latest\n\n"                       )

    doxyfile.write("# The MATHJAX_EXTENSIONS tag can be used to specify one or more MathJax\n"         )
    doxyfile.write("# extension names that should be enabled during MathJax rendering. For example\n"  )
    doxyfile.write("# MATHJAX_EXTENSIONS = TeX/AMSmath TeX/AMSsymbols\n"                               )
    doxyfile.write("# This tag requires that the tag USE_MATHJAX is set to YES.\n\n"                   )

    doxyfile.write("MATHJAX_EXTENSIONS = \n\n"                                                         )

    doxyfile.write("# The MATHJAX_CODEFILE tag can be used to specify a file with javascript pieces\n" )
    doxyfile.write("# of code that will be used on startup of the MathJax code. See the MathJax site\n")
    doxyfile.write("# (see: http://docs.mathjax.org/en/latest/output.html) for more details. For an\n" )
    doxyfile.write("# example see the documentation.\n"                                                )
    doxyfile.write("# This tag requires that the tag USE_MATHJAX is set to YES.\n\n"                   )

    doxyfile.write("MATHJAX_CODEFILE = \n\n"                                                           )

    doxyfile.write("# When the SEARCHENGINE tag is enabled doxygen will generate a search box for\n"   )
    doxyfile.write("# the HTML output. The underlying search engine uses javascript and DHTML and\n"   )
    doxyfile.write("# should work on any modern browser. Note that when using HTML help\n"             )
    doxyfile.write("# (GENERATE_HTMLHELP), Qt help (GENERATE_QHP), or docsets (GENERATE_DOCSET)\n"     )
    doxyfile.write("# there is already a search function so this one should typically be disabled.\n"  )
    doxyfile.write("# For large projects the javascript based search engine can be slow, then\n"       )
    doxyfile.write("# enabling SERVER_BASED_SEARCH may provide a better solution. It is possible to\n" )
    doxyfile.write("# search using the keyboard; to jump to the search box use <access key> + S\n"     )
    doxyfile.write("# (what the <access key> is depends on the OS and browser, but it is typically\n"  )
    doxyfile.write("# <CTRL>, <ALT>/<option>, or both). Inside the search box use the <cursor down\n"  )
    doxyfile.write("# key> to jump into the search results window, the results can be navigated\n"     )
    doxyfile.write("# using the <cursor keys>. Press <Enter> to select an item or <escape> to cancel\n")
    doxyfile.write("# the search. The filter options can be selected when the cursor is inside the\n"  )
    doxyfile.write("# search box by pressing <Shift>+<cursor down>. Also here use the <cursor keys>\n" )
    doxyfile.write("# to select a filter and <Enter> or <escape> to activate or cancel the filter\n"   )
    doxyfile.write("# option.\n"                                                                       )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_HTML is set to YES.\n\n"                 )

    doxyfile.write("SEARCHENGINE = YES\n\n"                                                            )

    doxyfile.write("# When the SERVER_BASED_SEARCH tag is enabled the search engine will be\n"         )
    doxyfile.write("# implemented using a web server instead of a web client using Javascript. There\n")
    doxyfile.write("# are two flavors of web server based searching depending on the EXTERNAL_SEARCH\n")
    doxyfile.write("# setting. When disabled, doxygen will generate a PHP script for searching and\n"  )
    doxyfile.write("# an index file used by the script. When EXTERNAL_SEARCH is enabled the indexing\n")
    doxyfile.write("# and searching needs to be provided by external tools. See the section\n"         )
    doxyfile.write("# \"External Indexing and Searching\" for details.\n"                              )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag SEARCHENGINE is set to YES.\n\n"                  )

    doxyfile.write("SERVER_BASED_SEARCH = NO\n\n"                                                      )

    doxyfile.write("# When EXTERNAL_SEARCH tag is enabled doxygen will no longer generate the PHP\n"   )
    doxyfile.write("# script for searching. Instead the search results are written to an XML file\n"   )
    doxyfile.write("# which needs to be processed by an external indexer. Doxygen will invoke an\n"    )
    doxyfile.write("# external search engine pointed to by the SEARCHENGINE_URL option to obtain the\n")
    doxyfile.write("# search results.\n"                                                               )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Doxygen ships with an example indexer (doxyindexer) and search engine\n"         )
    doxyfile.write("# (doxysearch.cgi) which are based on the open source search engine library\n"     )
    doxyfile.write("# Xapian (see: http://xapian.org/).\n"                                             )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# See the section \"External Indexing and Searching\" for details.\n"              )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag SEARCHENGINE is set to YES.\n\n"                  )

    doxyfile.write("EXTERNAL_SEARCH = NO\n\n"                                                          )

    doxyfile.write("# The SEARCHENGINE_URL should point to a search engine hosted by a web server\n"   )
    doxyfile.write("# which will return the search results when EXTERNAL_SEARCH is enabled.\n"         )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Doxygen ships with an example indexer (doxyindexer) and search engine\n"         )
    doxyfile.write("# (doxysearch.cgi) which are based on the open source search engine library\n"     )
    doxyfile.write("# Xapian (see: http://xapian.org/). See the section \"External Indexing and\n"     )
    doxyfile.write("# Searching\" for details.\n"                                                      )
    doxyfile.write("# This tag requires that the tag SEARCHENGINE is set to YES.\n\n"                  )

    doxyfile.write("SEARCHENGINE_URL = \n\n"                                                           )

    doxyfile.write("# When SERVER_BASED_SEARCH and EXTERNAL_SEARCH are both enabled the unindexed\n"   )
    doxyfile.write("# search data is written to a file for indexing by an external tool. With the\n"   )
    doxyfile.write("# SEARCHDATA_FILE tag the name of this file can be specified.\n"                   )
    doxyfile.write("# The default file is: searchdata.xml.\n"                                          )
    doxyfile.write("# This tag requires that the tag SEARCHENGINE is set to YES.\n\n"                  )

    doxyfile.write("SEARCHDATA_FILE = searchdata.xml\n\n"                                              )

    doxyfile.write("# When SERVER_BASED_SEARCH and EXTERNAL_SEARCH are both enabled the\n"             )
    doxyfile.write("# EXTERNAL_SEARCH_ID tag can be used as an identifier for the project. This is\n"  )
    doxyfile.write("# useful in combination with EXTRA_SEARCH_MAPPINGS to search through multiple\n"   )
    doxyfile.write("# projects and redirect the results back to the right project.\n"                  )
    doxyfile.write("# This tag requires that the tag SEARCHENGINE is set to YES.\n\n"                  )

    doxyfile.write("EXTERNAL_SEARCH_ID = \n\n"                                                         )

    doxyfile.write("# The EXTRA_SEARCH_MAPPINGS tag can be used to enable searching through doxygen\n" )
    doxyfile.write("# projects other than the one defined by this configuration file, but that are\n"  )
    doxyfile.write("# all added to the same external search index. Each project needs to have a\n"     )
    doxyfile.write("# unique id set via EXTERNAL_SEARCH_ID. The search mapping then maps the id of\n"  )
    doxyfile.write("# to a relative location where the documentation can be found. The format is:\n"   )
    doxyfile.write("# EXTRA_SEARCH_MAPPINGS = tagname1=loc1 tagname2=loc2 ...\n"                       )
    doxyfile.write("# This tag requires that the tag SEARCHENGINE is set to YES.\n\n"                  )

    doxyfile.write("EXTRA_SEARCH_MAPPINGS = \n\n"                                                      )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the LaTeX output\n"                             )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_LATEX tag is set to YES, doxygen will generate LaTeX output.\n"  )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("GENERATE_LATEX = NO\n\n"                                                           )

    doxyfile.write("# The LATEX_OUTPUT tag is used to specify where the LaTeX docs will be put. If a\n")
    doxyfile.write("# relative path is entered the value of OUTPUT_DIRECTORY will be put in front of\n")
    doxyfile.write("# it.\n"                                                                           )
    doxyfile.write("# The default directory is: latex.\n"                                              )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_OUTPUT = latex\n\n"                                                          )

    doxyfile.write("# The LATEX_CMD_NAME tag can be used to specify the LaTeX command name to be\n"    )
    doxyfile.write("# invoked.\n"                                                                      )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that when enabling USE_PDFLATEX this option is only used for generating\n"  )
    doxyfile.write("# bitmaps for formulas in the HTML output, but not in the Makefile that is\n"      )
    doxyfile.write("# written to the output directory.\n"                                              )
    doxyfile.write("# The default file is: latex.\n"                                                   )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_CMD_NAME = latex\n\n"                                                        )

    doxyfile.write("# The MAKEINDEX_CMD_NAME tag can be used to specify the command name to generate\n")
    doxyfile.write("# index for LaTeX.\n"                                                              )
    doxyfile.write("# The default file is: makeindex.\n"                                               )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("MAKEINDEX_CMD_NAME = makeindex\n\n"                                                )

    doxyfile.write("# If the COMPACT_LATEX tag is set to YES, doxygen generates more compact LaTeX\n"  )
    doxyfile.write("# documents. This may be useful for small projects and may help to save some\n"    )
    doxyfile.write("# trees in general.\n"                                                             )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("COMPACT_LATEX = NO\n\n"                                                            )

    doxyfile.write("# The PAPER_TYPE tag can be used to set the paper type that is used by the\n"      )
    doxyfile.write("# printer.\n"                                                                      )
    doxyfile.write("# Possible values are: a4 (210 x 297 mm), letter (8.5 x 11 inches), legal (8.5 x\n")
    doxyfile.write("# 14 inches) and executive (7.25 x 10.5 inches).\n"                                )
    doxyfile.write("# The default value is: a4.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("PAPER_TYPE = a4\n\n"                                                               )

    doxyfile.write("# The EXTRA_PACKAGES tag can be used to specify one or more LaTeX package names\n" )
    doxyfile.write("# that should be included in the LaTeX output. The package can be specified just\n")
    doxyfile.write("# by its name or with the correct syntax as to be used with the LaTeX\n"           )
    doxyfile.write("# \usepackage command. To get the times font for instance you can specify :\n"     )
    doxyfile.write("# EXTRA_PACKAGES=times or EXTRA_PACKAGES={times}\n"                                )
    doxyfile.write("# To use the option intlimits with the amsmath package you can specify:\n"         )
    doxyfile.write("# EXTRA_PACKAGES=[intlimits]{amsmath}\n"                                           )
    doxyfile.write("# If left blank no extra packages will be included.\n"                             )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("EXTRA_PACKAGES = \n\n"                                                             )

    doxyfile.write("# The LATEX_HEADER tag can be used to specify a personal LaTeX header for the\n"   )
    doxyfile.write("# generated LaTeX document. The header should contain everything until the first\n")
    doxyfile.write("# chapter. If it is left blank doxygen will generate a standard header. See\n"     )
    doxyfile.write("# section \"Doxygen usage\" for information on how to let doxygen write the\n"     )
    doxyfile.write("# default header to a separate file.\n"                                            )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note: Only use a user-defined header if you know what you are doing! The\n"      )
    doxyfile.write("# following commands have a special meaning inside the header: $title,\n"          )
    doxyfile.write("# $datetime, $date, $doxygenversion, $projectname, $projectnumber,\n"              )
    doxyfile.write("# $projectbrief, $projectlogo. Doxygen will replace $title with the empty\n"       )
    doxyfile.write("# string, for the replacement values of the other commands the user is referred\n" )
    doxyfile.write("# to HTML_HEADER.\n"                                                               )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_HEADER = \n\n"                                                               )

    doxyfile.write("# The LATEX_FOOTER tag can be used to specify a personal LaTeX footer for the\n"   )
    doxyfile.write("# generated LaTeX document. The footer should contain everything after the last\n" )
    doxyfile.write("# chapter. If it is left blank doxygen will generate a standard footer. See\n"     )
    doxyfile.write("# LATEX_HEADER for more information on how to generate a default footer and what\n")
    doxyfile.write("# special commands can be used inside the footer.\n"                               )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note: Only use a user-defined footer if you know what you are doing!\n"          )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_FOOTER = \n\n"                                                               )

    doxyfile.write("# The LATEX_EXTRA_STYLESHEET tag can be used to specify additional user-defined\n" )
    doxyfile.write("# LaTeX style sheets that are included after the standard style sheets created\n"  )
    doxyfile.write("# by doxygen. Using this option one can overrule certain style aspects. Doxygen\n" )
    doxyfile.write("# will copy the style sheet files to the output directory.\n"                      )
    doxyfile.write("# Note: The order of the extra style sheet files is of importance (e.g. the last\n")
    doxyfile.write("# style sheet in the list overrules the setting of the previous ones in the\n"     )
    doxyfile.write("# list).\n"                                                                        )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_EXTRA_STYLESHEET = \n\n"                                                     )

    doxyfile.write("# The LATEX_EXTRA_FILES tag can be used to specify one or more extra images or\n"  )
    doxyfile.write("# other source files which should be copied to the LATEX_OUTPUT output\n"          )
    doxyfile.write("# directory. Note that the files will be copied as-is; there are no commands or\n" )
    doxyfile.write("# markers available.\n"                                                            )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_EXTRA_FILES = \n\n"                                                          )

    doxyfile.write("# If the PDF_HYPERLINKS tag is set to YES, the LaTeX that is generated is\n"       )
    doxyfile.write("# prepared for conversion to PDF (using ps2pdf or pdflatex). The PDF file will\n"  )
    doxyfile.write("# contain links (just like the HTML output) instead of page references. This\n"    )
    doxyfile.write("# makes the output suitable for online browsing using a PDF viewer.\n"             )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("PDF_HYPERLINKS = YES\n\n"                                                          )

    doxyfile.write("# If the USE_PDFLATEX tag is set to YES, doxygen will use pdflatex to generate\n"  )
    doxyfile.write("# the PDF file directly from the LaTeX files. Set this option to YES, to get a\n"  )
    doxyfile.write("# higher quality PDF documentation.\n"                                             )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("USE_PDFLATEX = YES\n\n"                                                            )

    doxyfile.write("# If the LATEX_BATCHMODE tag is set to YES, doxygen will add the \batchmode\n"     )
    doxyfile.write("# command to the generated LaTeX files. This will instruct LaTeX to keep running\n")
    doxyfile.write("# if errors occur, instead of asking the user for help. This option is also used\n")
    doxyfile.write("# when generating formulas in HTML.\n"                                             )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_BATCHMODE = NO\n\n"                                                          )

    doxyfile.write("# If the LATEX_HIDE_INDICES tag is set to YES then doxygen will not include the\n" )
    doxyfile.write("# index chapters (such as File Index, Compound Index, etc.) in the output.\n"      )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_HIDE_INDICES = NO\n\n"                                                       )

    doxyfile.write("# If the LATEX_SOURCE_CODE tag is set to YES then doxygen will include source\n"   )
    doxyfile.write("# code with syntax highlighting in the LaTeX output.\n"                            )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that which sources are shown also depends on other settings such as\n"      )
    doxyfile.write("# SOURCE_BROWSER.\n"                                                               )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_SOURCE_CODE = NO\n\n"                                                        )

    doxyfile.write("# The LATEX_BIB_STYLE tag can be used to specify the style to use for the\n"       )
    doxyfile.write("# bibliography, e.g. plainnat, or ieeetr. See\n"                                   )
    doxyfile.write("# http://en.wikipedia.org/wiki/BibTeX and \cite for more info.\n"                  )
    doxyfile.write("# The default value is: plain.\n"                                                  )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_BIB_STYLE = plain\n\n"                                                       )

    doxyfile.write("# If the LATEX_TIMESTAMP tag is set to YES then the footer of each generated\n"    )
    doxyfile.write("# page will contain the date and time when the page was generated. Setting this\n" )
    doxyfile.write("# to NO can help when comparing the output of multiple runs.\n"                    )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_LATEX is set to YES.\n\n"                )

    doxyfile.write("LATEX_TIMESTAMP = NO\n\n"                                                          )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the RTF output\n"                               )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_RTF tag is set to YES, doxygen will generate RTF output. The\n"  )
    doxyfile.write("# RTF output is optimized for Word 97 and may not look too pretty with other RTF\n")
    doxyfile.write("# readers/editors.\n"                                                              )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("GENERATE_RTF = NO\n\n"                                                             )

    doxyfile.write("# The RTF_OUTPUT tag is used to specify where the RTF docs will be put. If a\n"    )
    doxyfile.write("# relative path is entered the value of OUTPUT_DIRECTORY will be put in front of\n")
    doxyfile.write("# it.\n"                                                                           )
    doxyfile.write("# The default directory is: rtf.\n"                                                )
    doxyfile.write("# This tag requires that the tag GENERATE_RTF is set to YES.\n\n"                  )

    doxyfile.write("RTF_OUTPUT = rtf\n\n"                                                              )

    doxyfile.write("# If the COMPACT_RTF tag is set to YES, doxygen generates more compact RTF\n"      )
    doxyfile.write("# documents. This may be useful for small projects and may help to save some\n"    )
    doxyfile.write("# trees in general.\n"                                                             )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_RTF is set to YES.\n\n"                  )

    doxyfile.write("COMPACT_RTF = NO\n\n"                                                              )

    doxyfile.write("# If the RTF_HYPERLINKS tag is set to YES, the RTF that is generated will\n"       )
    doxyfile.write("# contain hyperlink fields. The RTF file will contain links (just like the HTML\n" )
    doxyfile.write("# output) instead of page references. This makes the output suitable for online\n" )
    doxyfile.write("# browsing using Word or some other Word compatible readers that support those\n"  )
    doxyfile.write("# fields.\n"                                                                       )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note: WordPad (write) and others do not support links.\n"                        )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_RTF is set to YES.\n\n"                  )

    doxyfile.write("RTF_HYPERLINKS = NO\n\n"                                                           )

    doxyfile.write("# Load stylesheet definitions from file. Syntax is similar to doxygen's config\n"  )
    doxyfile.write("# file, i.e. a series of assignments. You only have to provide replacements,\n"    )
    doxyfile.write("# missing definitions are set to their default value.\n"                           )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# See also section \"Doxygen usage\" for information on how to generate the\n"     )
    doxyfile.write("# default style sheet that doxygen normally uses.\n"                               )
    doxyfile.write("# This tag requires that the tag GENERATE_RTF is set to YES.\n\n"                  )

    doxyfile.write("RTF_STYLESHEET_FILE = \n\n"                                                        )

    doxyfile.write("# Set optional variables used in the generation of an RTF document. Syntax is\n"   )
    doxyfile.write("# similar to doxygen's config file. A template extensions file can be generated\n" )
    doxyfile.write("# using doxygen -e rtf extensionFile.\n"                                           )
    doxyfile.write("# This tag requires that the tag GENERATE_RTF is set to YES.\n\n"                  )

    doxyfile.write("RTF_EXTENSIONS_FILE = \n\n"                                                        )

    doxyfile.write("# If the RTF_SOURCE_CODE tag is set to YES then doxygen will include source code\n")
    doxyfile.write("# with syntax highlighting in the RTF output.\n"                                   )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that which sources are shown also depends on other settings such as\n"      )
    doxyfile.write("# SOURCE_BROWSER.\n"                                                               )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_RTF is set to YES.\n\n"                  )

    doxyfile.write("RTF_SOURCE_CODE = NO\n\n"                                                          )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the man page output\n"                          )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_MAN tag is set to YES, doxygen will generate man pages for\n"    )
    doxyfile.write("# classes and files.\n"                                                            )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("GENERATE_MAN = NO\n\n"                                                             )

    doxyfile.write("# The MAN_OUTPUT tag is used to specify where the man pages will be put. If a\n"   )
    doxyfile.write("# relative path is entered the value of OUTPUT_DIRECTORY will be put in front of\n")
    doxyfile.write("# it. A directory man3 will be created inside the directory specified by\n"        )
    doxyfile.write("# MAN_OUTPUT.\n"                                                                   )
    doxyfile.write("# The default directory is: man.\n"                                                )
    doxyfile.write("# This tag requires that the tag GENERATE_MAN is set to YES.\n\n"                  )

    doxyfile.write("MAN_OUTPUT = man\n\n"                                                              )

    doxyfile.write("# The MAN_EXTENSION tag determines the extension that is added to the generated\n" )
    doxyfile.write("# man pages. In case the manual section does not start with a number, the number\n")
    doxyfile.write("# 3 is prepended. The dot (.) at the beginning of the MAN_EXTENSION tag is\n"      )
    doxyfile.write("# optional.\n"                                                                     )
    doxyfile.write("# The default value is: .3.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_MAN is set to YES.\n\n"                  )

    doxyfile.write("MAN_EXTENSION = .3\n\n"                                                            )

    doxyfile.write("# The MAN_SUBDIR tag determines the name of the directory created within\n"        )
    doxyfile.write("# MAN_OUTPUT in which the man pages are placed. If defaults to man followed by\n"  )
    doxyfile.write("# MAN_EXTENSION with the initial . removed.\n"                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_MAN is set to YES.\n\n"                  )

    doxyfile.write("MAN_SUBDIR = \n\n"                                                                 )

    doxyfile.write("# If the MAN_LINKS tag is set to YES and doxygen generates man output, then it\n"  )
    doxyfile.write("# will generate one additional man file for each entity documented in the real\n"  )
    doxyfile.write("# man page(s). These additional files only source the real man page, but without\n")
    doxyfile.write("# them the man command would be unable to find the correct page.\n"                )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_MAN is set to YES.\n\n"                  )

    doxyfile.write("MAN_LINKS = NO\n\n"                                                                )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the XML output\n"                               )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_XML tag is set to YES, doxygen will generate an XML file that\n" )
    doxyfile.write("# captures the structure of the code including all documentation.\n"               )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("GENERATE_XML = NO\n\n"                                                             )

    doxyfile.write("# The XML_OUTPUT tag is used to specify where the XML pages will be put. If a\n"   )
    doxyfile.write("# relative path is entered the value of OUTPUT_DIRECTORY will be put in front of\n")
    doxyfile.write("# it.\n"                                                                           )
    doxyfile.write("# The default directory is: xml.\n"                                                )
    doxyfile.write("# This tag requires that the tag GENERATE_XML is set to YES.\n\n"                  )

    doxyfile.write("XML_OUTPUT = xml\n\n"                                                              )

    doxyfile.write("# If the XML_PROGRAMLISTING tag is set to YES, doxygen will dump the program\n"    )
    doxyfile.write("# listings (including syntax highlighting and cross-referencing information) to\n" )
    doxyfile.write("# the XML output. Note that enabling this will significantly increase the size\n"  )
    doxyfile.write("# of the XML output.\n"                                                            )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_XML is set to YES.\n\n"                  )

    doxyfile.write("XML_PROGRAMLISTING = YES\n\n"                                                      )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the DOCBOOK output\n"                           )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_DOCBOOK tag is set to YES, doxygen will generate Docbook files\n")
    doxyfile.write("# that can be used to generate PDF.\n"                                             )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("GENERATE_DOCBOOK = NO\n\n"                                                         )

    doxyfile.write("# The DOCBOOK_OUTPUT tag is used to specify where the Docbook pages will be put.\n")
    doxyfile.write("# If a relative path is entered the value of OUTPUT_DIRECTORY will be put in\n"    )
    doxyfile.write("# front of it.\n"                                                                  )
    doxyfile.write("# The default directory is: docbook.\n"                                            )
    doxyfile.write("# This tag requires that the tag GENERATE_DOCBOOK is set to YES.\n\n"              )

    doxyfile.write("DOCBOOK_OUTPUT = docbook\n\n"                                                      )

    doxyfile.write("# If the DOCBOOK_PROGRAMLISTING tag is set to YES, doxygen will include the\n"     )
    doxyfile.write("# program listings (including syntax highlighting and cross-referencing\n"         )
    doxyfile.write("# information) to the DOCBOOK output. Note that enabling this will significantly\n")
    doxyfile.write("# increase the size of the DOCBOOK output.\n"                                      )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_DOCBOOK is set to YES.\n\n"              )

    doxyfile.write("DOCBOOK_PROGRAMLISTING = NO\n\n"                                                   )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options for the AutoGen Definitions output\n"                      )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_AUTOGEN_DEF tag is set to YES, doxygen will generate an\n"       )
    doxyfile.write("# AutoGen Definitions (see http://autogen.sf.net) file that captures the\n"        )
    doxyfile.write("# structure of the code including all documentation. Note that this feature is\n"  )
    doxyfile.write("# still experimental and incomplete at the moment.\n"                              )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("GENERATE_AUTOGEN_DEF = NO\n\n"                                                     )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the Perl module output\n"                       )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the GENERATE_PERLMOD tag is set to YES, doxygen will generate a Perl module\n")
    doxyfile.write("# file that captures the structure of the code including all documentation.\n"     )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that this feature is still experimental and incomplete at the moment.\n"    )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("GENERATE_PERLMOD = NO\n\n"                                                         )

    doxyfile.write("# If the PERLMOD_LATEX tag is set to YES, doxygen will generate the necessary\n"   )
    doxyfile.write("# Makefile rules, Perl scripts and LaTeX code to be able to generate PDF and DVI\n")
    doxyfile.write("# output from the Perl module output.\n"                                           )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag GENERATE_PERLMOD is set to YES.\n\n"              )

    doxyfile.write("PERLMOD_LATEX = NO\n\n"                                                            )

    doxyfile.write("# If the PERLMOD_PRETTY tag is set to YES, the Perl module output will be nicely\n")
    doxyfile.write("# formatted so it can be parsed by a human reader. This is useful if you want to\n")
    doxyfile.write("# understand what is going on. On the other hand, if this tag is set to NO, the\n" )
    doxyfile.write("# size of the Perl module output will be much smaller and Perl will parse it\n"    )
    doxyfile.write("# just the same.\n"                                                                )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag GENERATE_PERLMOD is set to YES.\n\n"              )

    doxyfile.write("PERLMOD_PRETTY = YES\n\n"                                                          )

    doxyfile.write("# The names of the make variables in the generated doxyrules.make file are\n"      )
    doxyfile.write("# prefixed with the string contained in PERLMOD_MAKEVAR_PREFIX. This is useful\n"  )
    doxyfile.write("# so different doxyrules.make files included by the same Makefile don't\n"         )
    doxyfile.write("# overwrite each other's variables.\n"                                             )
    doxyfile.write("# This tag requires that the tag GENERATE_PERLMOD is set to YES.\n\n"              )

    doxyfile.write("PERLMOD_MAKEVAR_PREFIX = \n\n"                                                     )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the preprocessor\n"                             )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the ENABLE_PREPROCESSING tag is set to YES, doxygen will evaluate all\n"      )
    doxyfile.write("# C-preprocessor directives found in the sources and include files.\n"             )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("ENABLE_PREPROCESSING = YES\n\n"                                                    )

    doxyfile.write("# If the MACRO_EXPANSION tag is set to YES, doxygen will expand all macro names\n" )
    doxyfile.write("# in the source code. If set to NO, only conditional compilation will be\n"        )
    doxyfile.write("# performed. Macro expansion can be done in a controlled way by setting\n"         )
    doxyfile.write("# EXPAND_ONLY_PREDEF to YES.\n"                                                    )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.\n\n"          )

    doxyfile.write("MACRO_EXPANSION = NO\n\n"                                                          )

    doxyfile.write("# If the EXPAND_ONLY_PREDEF and MACRO_EXPANSION tags are both set to YES then\n"   )
    doxyfile.write("# the macro expansion is limited to the macros specified with the PREDEFINED and\n")
    doxyfile.write("# EXPAND_AS_DEFINED tags.\n"                                                       )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.\n\n"          )

    doxyfile.write("EXPAND_ONLY_PREDEF = NO\n\n"                                                       )

    doxyfile.write("# If the SEARCH_INCLUDES tag is set to YES, the include files in the\n"            )
    doxyfile.write("# INCLUDE_PATH will be searched if a #include is found.\n"                         )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.\n\n"          )

    doxyfile.write("SEARCH_INCLUDES = YES\n\n"                                                         )

    doxyfile.write("# The INCLUDE_PATH tag can be used to specify one or more directories that\n"      )
    doxyfile.write("# contain include files that are not input files but should be processed by the\n" )
    doxyfile.write("# preprocessor.\n"                                                                 )
    doxyfile.write("# This tag requires that the tag SEARCH_INCLUDES is set to YES.\n\n"               )

    doxyfile.write("INCLUDE_PATH = \n\n"                                                               )

    doxyfile.write("# You can use the INCLUDE_FILE_PATTERNS tag to specify one or more wildcard\n"     )
    doxyfile.write("# patterns (like *.h and *.hpp) to filter out the header-files in the\n"           )
    doxyfile.write("# directories. If left blank, the patterns specified with FILE_PATTERNS will be\n" )
    doxyfile.write("# used.\n"                                                                         )
    doxyfile.write("# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.\n\n"          )

    doxyfile.write("INCLUDE_FILE_PATTERNS = \n\n"                                                      )

    doxyfile.write("# The PREDEFINED tag can be used to specify one or more macro names that are\n"    )
    doxyfile.write("# defined before the preprocessor is started (similar to the -D option of e.g.\n"  )
    doxyfile.write("# gcc). The argument of the tag is a list of macros of the form: name or\n"        )
    doxyfile.write("# name=definition (no spaces). If the definition and the \"=\" are omitted, \"=1\"\n")
    doxyfile.write("# is assumed. To prevent a macro definition from being undefined via #undef or\n"  )
    doxyfile.write("# recursively expanded use the := operator instead of the = operator.\n"           )
    doxyfile.write("# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.\n\n"          )

    doxyfile.write("PREDEFINED = \n\n"                                                                 )

    doxyfile.write("# If the MACRO_EXPANSION and EXPAND_ONLY_PREDEF tags are set to YES then this\n"   )
    doxyfile.write("# tag can be used to specify a list of macro names that should be expanded. The\n" )
    doxyfile.write("# macro definition that is found in the sources will be used. Use the PREDEFINED\n")
    doxyfile.write("# tag if you want to use a different macro definition that overrules the\n"        )
    doxyfile.write("# definition found in the source code.\n"                                          )
    doxyfile.write("# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.\n\n"          )

    doxyfile.write("EXPAND_AS_DEFINED = \n\n"                                                          )

    doxyfile.write("# If the SKIP_FUNCTION_MACROS tag is set to YES then doxygen's preprocessor will\n")
    doxyfile.write("# remove all references to function-like macros that are alone on a line, have\n"  )
    doxyfile.write("# an all uppercase name, and do not end with a semicolon. Such function macros\n"  )
    doxyfile.write("# are typically used for boiler-plate code, and will confuse the parser if not\n"  )
    doxyfile.write("# removed.\n"                                                                      )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag ENABLE_PREPROCESSING is set to YES.\n\n"          )

    doxyfile.write("SKIP_FUNCTION_MACROS = YES\n\n"                                                    )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to external references\n"                          )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# The TAGFILES tag can be used to specify one or more tag files. For each tag\n"   )
    doxyfile.write("# file the location of the external documentation should be added. The format of\n")
    doxyfile.write("# a tag file without this location is as follows:\n"                               )
    doxyfile.write("# TAGFILES = file1 file2 ...\n"                                                    )
    doxyfile.write("# Adding location for the tag files is done as follows:\n"                         )
    doxyfile.write("# TAGFILES = file1=loc1 \"file2 = loc2\" ...\n"                                    )
    doxyfile.write("# where loc1 and loc2 can be relative or absolute paths or URLs. See the\n"        )
    doxyfile.write("# section \"Linking to external documentation\" for more information about the use\n")
    doxyfile.write("# of tag files.\n"                                                                 )
    doxyfile.write("# Note: Each tag file must have a unique name (where the name does NOT include\n"  )
    doxyfile.write("# the path). If a tag file is not located in the directory in which doxygen is\n"  )
    doxyfile.write("# run, you must also specify the path to the tagfile here.\n\n"                    )

    doxyfile.write("TAGFILES = \n\n"                                                                   )

    doxyfile.write("# When a file name is specified after GENERATE_TAGFILE, doxygen will create a\n"   )
    doxyfile.write("# tag file that is based on the input files it reads. See section \"Linking to\n"  )
    doxyfile.write("# external documentation\" for more information about the usage of tag files.\n\n" )

    doxyfile.write("GENERATE_TAGFILE = \n\n"                                                           )

    doxyfile.write("# If the ALLEXTERNALS tag is set to YES, all external class will be listed in\n"   )
    doxyfile.write("# the class index. If set to NO, only the inherited external classes will be\n"    )
    doxyfile.write("# listed.\n"                                                                       )
    doxyfile.write("# The default value is: NO.\n\n"                                                   )

    doxyfile.write("ALLEXTERNALS = NO\n\n"                                                             )

    doxyfile.write("# If the EXTERNAL_GROUPS tag is set to YES, all external groups will be listed\n"  )
    doxyfile.write("# in the modules index. If set to NO, only the current project's groups will be\n" )
    doxyfile.write("# listed.\n"                                                                       )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("EXTERNAL_GROUPS = YES\n\n"                                                         )

    doxyfile.write("# If the EXTERNAL_PAGES tag is set to YES, all external pages will be listed in\n" )
    doxyfile.write("# the related pages index. If set to NO, only the current project's pages will\n"  )
    doxyfile.write("# be listed.\n"                                                                    )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("EXTERNAL_PAGES = YES\n\n"                                                          )

    doxyfile.write("# The PERL_PATH should be the absolute path and name of the perl script\n"         )
    doxyfile.write("# interpreter (i.e. the result of 'which perl').\n"                                )
    doxyfile.write("# The default file (with absolute path) is: /usr/bin/perl.\n\n"                    )

    doxyfile.write("PERL_PATH = /usr/bin/perl\n\n"                                                     )

    doxyfile.write("#---------------------------------------------------------------------------\n"    )
    doxyfile.write("# Configuration options related to the dot tool\n"                                 )
    doxyfile.write("#---------------------------------------------------------------------------\n\n"  )

    doxyfile.write("# If the CLASS_DIAGRAMS tag is set to YES, doxygen will generate a class diagram\n")
    doxyfile.write("# (in HTML and LaTeX) for classes with base or super classes. Setting the tag to\n")
    doxyfile.write("# NO turns the diagrams off. Note that this option also works with HAVE_DOT\n"     )
    doxyfile.write("# disabled, but it is recommended to install and use dot, since it yields more\n"  )
    doxyfile.write("# powerful graphs.\n"                                                              )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("CLASS_DIAGRAMS = YES\n\n"                                                          )

    doxyfile.write("# You can define message sequence charts within doxygen comments using the \msc\n" )
    doxyfile.write("# command. Doxygen will then run the mscgen tool (see:\n"                          )
    doxyfile.write("# http://www.mcternan.me.uk/mscgen/)) to produce the chart and insert it in the\n" )
    doxyfile.write("# documentation. The MSCGEN_PATH tag allows you to specify the directory where\n"  )
    doxyfile.write("# the mscgen tool resides. If left empty the tool is assumed to be found in the\n" )
    doxyfile.write("# default search path.\n\n"                                                        )

    doxyfile.write("MSCGEN_PATH = \n\n"                                                                )

    doxyfile.write("# You can include diagrams made with dia in doxygen documentation. Doxygen will\n" )
    doxyfile.write("# then run dia to produce the diagram and insert it in the documentation. The\n"   )
    doxyfile.write("# DIA_PATH tag allows you to specify the directory where the dia binary resides.\n")
    doxyfile.write("# If left empty dia is assumed to be found in the default search path.\n\n"        )

    doxyfile.write("DIA_PATH = \n\n"                                                                   )

    doxyfile.write("# If set to YES the inheritance and collaboration graphs will hide inheritance\n"  )
    doxyfile.write("# and usage relations if the target is undocumented or is not a class.\n"          )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("HIDE_UNDOC_RELATIONS = YES\n\n"                                                    )

    doxyfile.write("# If you set the HAVE_DOT tag to YES then doxygen will assume the dot tool is\n"   )
    doxyfile.write("# available from the path. This tool is part of Graphviz (see:\n"                  )
    doxyfile.write("# http://www.graphviz.org/), a graph visualization toolkit from AT&T and Lucent\n" )
    doxyfile.write("# Bell Labs. The other options in this section have no effect if this option is\n" )
    doxyfile.write("# set to NO\n"                                                                     )
    doxyfile.write("# The default value is: YES.\n\n"                                                  )

    doxyfile.write("HAVE_DOT = YES\n\n"                                                                )

    doxyfile.write("# The DOT_NUM_THREADS specifies the number of dot invocations doxygen is allowed\n")
    doxyfile.write("# to run in parallel. When set to 0 doxygen will base this on the number of\n"     )
    doxyfile.write("# processors available in the system. You can set it explicitly to a value\n"      )
    doxyfile.write("# larger than 0 to get control over the balance between CPU load and processing\n" )
    doxyfile.write("# speed.\n"                                                                        )
    doxyfile.write("# Minimum value: 0, maximum value: 32, default value: 0.\n"                        )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_NUM_THREADS = 0\n\n"                                                           )

    doxyfile.write("# When you want a differently looking font in the dot files that doxygen\n"        )
    doxyfile.write("# generates you can specify the font name using DOT_FONTNAME. You need to make\n"  )
    doxyfile.write("# sure dot is able to find the font, which can be done by putting it in a\n"       )
    doxyfile.write("# standard location or by setting the DOTFONTPATH environment variable or by\n"    )
    doxyfile.write("# setting DOT_FONTPATH to the directory containing the font.\n"                    )
    doxyfile.write("# The default value is: Helvetica.\n"                                              )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_FONTNAME = Helvetica\n\n"                                                      )

    doxyfile.write("# The DOT_FONTSIZE tag can be used to set the size (in points) of the font of\n"   )
    doxyfile.write("# dot graphs.\n"                                                                   )
    doxyfile.write("# Minimum value: 4, maximum value: 24, default value: 10.\n"                       )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_FONTSIZE = 10\n\n"                                                             )

    doxyfile.write("# By default doxygen will tell dot to use the default font as specified with\n"    )
    doxyfile.write("# DOT_FONTNAME. If you specify a different font using DOT_FONTNAME you can set\n"  )
    doxyfile.write("# the path where dot can find it using this tag.\n"                                )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_FONTPATH = \n\n"                                                               )

    doxyfile.write("# If the CLASS_GRAPH tag is set to YES then doxygen will generate a graph for\n"   )
    doxyfile.write("# each documented class showing the direct and indirect inheritance relations.\n"  )
    doxyfile.write("# Setting this tag to YES will force the CLASS_DIAGRAMS tag to NO.\n"              )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("CLASS_GRAPH = YES\n\n"                                                             )

    doxyfile.write("# If the COLLABORATION_GRAPH tag is set to YES then doxygen will generate a\n"     )
    doxyfile.write("# graph for each documented class showing the direct and indirect implementation\n")
    doxyfile.write("# dependencies (inheritance, containment, and class references variables) of the\n")
    doxyfile.write("# class with other documented classes.\n"                                          )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("COLLABORATION_GRAPH = YES\n\n"                                                     )

    doxyfile.write("# If the GROUP_GRAPHS tag is set to YES then doxygen will generate a graph for\n"  )
    doxyfile.write("# groups, showing the direct groups dependencies.\n"                               )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("GROUP_GRAPHS = YES\n\n"                                                            )

    doxyfile.write("# If the UML_LOOK tag is set to YES, doxygen will generate inheritance and\n"      )
    doxyfile.write("# collaboration diagrams in a style similar to the OMG's Unified Modeling\n"       )
    doxyfile.write("# Language.\n"                                                                     )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("UML_LOOK = NO\n\n"                                                                 )

    doxyfile.write("# If the UML_LOOK tag is enabled, the fields and methods are shown inside the\n"   )
    doxyfile.write("# class node. If there are many fields or methods and many nodes the graph may\n"  )
    doxyfile.write("# become too big to be useful. The UML_LIMIT_NUM_FIELDS threshold limits the\n"    )
    doxyfile.write("# number of items for each type to make the size more manageable. Set this to 0\n" )
    doxyfile.write("# for no limit. Note that the threshold may be exceeded by 50% before the limit\n" )
    doxyfile.write("# is enforced. So when you set the threshold to 10, up to 15 fields may appear,\n" )
    doxyfile.write("# but if the number exceeds 15, the total amount of fields shown is limited to\n"  )
    doxyfile.write("# 10.\n"                                                                           )
    doxyfile.write("# Minimum value: 0, maximum value: 100, default value: 10.\n"                      )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("UML_LIMIT_NUM_FIELDS = 10\n\n"                                                     )

    doxyfile.write("# If the TEMPLATE_RELATIONS tag is set to YES then the inheritance and\n"          )
    doxyfile.write("# collaboration graphs will show the relations between templates and their\n"      )
    doxyfile.write("# instances.\n"                                                                    )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("TEMPLATE_RELATIONS = NO\n\n"                                                       )

    doxyfile.write("# If the INCLUDE_GRAPH, ENABLE_PREPROCESSING and SEARCH_INCLUDES tags are set to\n")
    doxyfile.write("# YES then doxygen will generate a graph for each documented file showing the\n"   )
    doxyfile.write("# direct and indirect include dependencies of the file with other documented\n"    )
    doxyfile.write("# files.\n"                                                                        )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("INCLUDE_GRAPH = YES\n\n"                                                           )

    doxyfile.write("# If the INCLUDED_BY_GRAPH, ENABLE_PREPROCESSING and SEARCH_INCLUDES tags are\n"   )
    doxyfile.write("# set to YES then doxygen will generate a graph for each documented file showing\n")
    doxyfile.write("# the direct and indirect include dependencies of the file with other documented\n")
    doxyfile.write("# files.\n"                                                                        )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("INCLUDED_BY_GRAPH = YES\n\n"                                                       )

    doxyfile.write("# If the CALL_GRAPH tag is set to YES then doxygen will generate a call\n"         )
    doxyfile.write("# dependency graph for every global function or class method.\n"                   )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that enabling this option will significantly increase the time of a run.\n" )
    doxyfile.write("# So in most cases it will be better to enable call graphs for selected\n"         )
    doxyfile.write("# functions only using the \callgraph command. Disabling a call graph can be\n"    )
    doxyfile.write("# accomplished by means of the command \hidecallgraph.\n"                          )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("CALL_GRAPH = NO\n\n"                                                               )

    doxyfile.write("# If the CALLER_GRAPH tag is set to YES then doxygen will generate a caller\n"     )
    doxyfile.write("# dependency graph for every global function or class method.\n"                   )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that enabling this option will significantly increase the time of a run.\n" )
    doxyfile.write("# So in most cases it will be better to enable caller graphs for selected\n"       )
    doxyfile.write("# functions only using the \callergraph command. Disabling a caller graph can be\n")
    doxyfile.write("# accomplished by means of the command \hidecallergraph.\n"                        )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("CALLER_GRAPH = NO\n\n"                                                             )

    doxyfile.write("# If the GRAPHICAL_HIERARCHY tag is set to YES then doxygen will graphical\n"      )
    doxyfile.write("# hierarchy of all classes instead of a textual one.\n"                            )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("GRAPHICAL_HIERARCHY = YES\n\n"                                                     )

    doxyfile.write("# If the DIRECTORY_GRAPH tag is set to YES then doxygen will show the\n"           )
    doxyfile.write("# dependencies a directory has on other directories in a graphical way. The\n"     )
    doxyfile.write("# dependency relations are determined by the #include relations between the\n"     )
    doxyfile.write("# files in the directories.\n"                                                     )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DIRECTORY_GRAPH = YES\n\n"                                                         )

    doxyfile.write("# The DOT_IMAGE_FORMAT tag can be used to set the image format of the images\n"    )
    doxyfile.write("# generated by dot. For an explanation of the image formats see the section\n"     )
    doxyfile.write("# output formats in the documentation of the dot tool (Graphviz (see:\n"           )
    doxyfile.write("# http://www.graphviz.org/)).\n"                                                   )
    doxyfile.write("# Note: If you choose svg you need to set HTML_FILE_EXTENSION to xhtml in order\n" )
    doxyfile.write("# to make the SVG files visible in IE 9+ (other browsers do not have this\n"       )
    doxyfile.write("# requirement).\n"                                                                 )
    doxyfile.write("# Possible values are: png, png:cairo, png:cairo:cairo, png:cairo:gd, png:gd,\n"   )
    doxyfile.write("# png:gd:gd, jpg, jpg:cairo, jpg:cairo:gd, jpg:gd, jpg:gd:gd, gif, gif:cairo,\n"   )
    doxyfile.write("# gif:cairo:gd, gif:gd, gif:gd:gd, svg, png:gd, png:gd:gd, png:cairo,\n"           )
    doxyfile.write("# png:cairo:gd, png:cairo:cairo, png:cairo:gdiplus, png:gdiplus and\n"             )
    doxyfile.write("# png:gdiplus:gdiplus.\n"                                                          )
    doxyfile.write("# The default value is: png.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_IMAGE_FORMAT = png\n\n"                                                        )

    doxyfile.write("# If DOT_IMAGE_FORMAT is set to svg, then this option can be set to YES to\n"      )
    doxyfile.write("# enable generation of interactive SVG images that allow zooming and panning.\n"   )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Note that this requires a modern browser other than Internet Explorer. Tested\n" )
    doxyfile.write("# and working are Firefox, Chrome, Safari, and Opera.\n"                           )
    doxyfile.write("# Note: For IE 9+ you need to set HTML_FILE_EXTENSION to xhtml in order to make\n" )
    doxyfile.write("# the SVG files visible. Older versions of IE do not have SVG support.\n"          )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("INTERACTIVE_SVG = NO\n\n"                                                          )

    doxyfile.write("# The DOT_PATH tag can be used to specify the path where the dot tool can be\n"    )
    doxyfile.write("# found. If left blank, it is assumed the dot tool can be found in the path.\n"    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_PATH = \n\n"                                                                   )

    doxyfile.write("# The DOTFILE_DIRS tag can be used to specify one or more directories that\n"      )
    doxyfile.write("# contain dot files that are included in the documentation (see the \dotfile\n"    )
    doxyfile.write("# command).\n"                                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOTFILE_DIRS = \n\n"                                                               )

    doxyfile.write("# The MSCFILE_DIRS tag can be used to specify one or more directories that\n"      )
    doxyfile.write("# contain msc files that are included in the documentation (see the \mscfile\n"    )
    doxyfile.write("# command).\n\n"                                                                   )

    doxyfile.write("MSCFILE_DIRS = \n\n"                                                               )

    doxyfile.write("# The DIAFILE_DIRS tag can be used to specify one or more directories that\n"      )
    doxyfile.write("# contain dia files that are included in the documentation (see the \diafile\n"    )
    doxyfile.write("# command).\n\n"                                                                   )

    doxyfile.write("DIAFILE_DIRS = \n\n"                                                               )

    doxyfile.write("# When using plantuml, the PLANTUML_JAR_PATH tag should be used to specify the\n"  )
    doxyfile.write("# path where java can find the plantuml.jar file. If left blank, it is assumed\n"  )
    doxyfile.write("# PlantUML is not used or called during a preprocessing step. Doxygen will\n"      )
    doxyfile.write("# generate a warning when it encounters a \startuml command in this case and\n"    )
    doxyfile.write("# will not generate output for the diagram.\n\n"                                   )

    doxyfile.write("PLANTUML_JAR_PATH = \n\n"                                                          )

    doxyfile.write("# When using plantuml, the specified paths are searched for files specified by\n"  )
    doxyfile.write("# the !include statement in a plantuml block.\n\n"                                 )

    doxyfile.write("PLANTUML_INCLUDE_PATH = \n\n"                                                      )

    doxyfile.write("# The DOT_GRAPH_MAX_NODES tag can be used to set the maximum number of nodes\n"    )
    doxyfile.write("# that will be shown in the graph. If the number of nodes in a graph becomes\n"    )
    doxyfile.write("# larger than this value, doxygen will truncate the graph, which is visualized\n"  )
    doxyfile.write("# by representing a node as a red box. Note that doxygen if the number of direct\n")
    doxyfile.write("# children of the root node in a graph is already larger than\n"                   )
    doxyfile.write("# DOT_GRAPH_MAX_NODES then the graph will not be shown at all. Also note that\n"   )
    doxyfile.write("# the size of a graph can be further restricted by MAX_DOT_GRAPH_DEPTH.\n"         )
    doxyfile.write("# Minimum value: 0, maximum value: 10000, default value: 50.\n"                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_GRAPH_MAX_NODES = 50\n\n"                                                      )

    doxyfile.write("# The MAX_DOT_GRAPH_DEPTH tag can be used to set the maximum depth of the graphs\n")
    doxyfile.write("# generated by dot. A depth value of 3 means that only nodes reachable from the\n" )
    doxyfile.write("# root by following a path via at most 3 edges will be shown. Nodes that lay\n"    )
    doxyfile.write("# further from the root node will be omitted. Note that setting this option to 1\n")
    doxyfile.write("# or 2 may greatly reduce the computation time needed for large code bases. Also\n")
    doxyfile.write("# note that the size of a graph can be further restricted by\n"                    )
    doxyfile.write("# DOT_GRAPH_MAX_NODES. Using a depth of 0 means no depth restriction.\n"           )
    doxyfile.write("# Minimum value: 0, maximum value: 1000, default value: 0.\n"                      )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("MAX_DOT_GRAPH_DEPTH = 0\n\n"                                                       )

    doxyfile.write("# Set the DOT_TRANSPARENT tag to YES to generate images with a transparent\n"      )
    doxyfile.write("# background. This is disabled by default, because dot on Windows does not seem\n" )
    doxyfile.write("# to support this out of the box.\n"                                               )
    doxyfile.write("#\n"                                                                               )
    doxyfile.write("# Warning: Depending on the platform used, enabling this option may lead to\n"     )
    doxyfile.write("# badly anti-aliased labels on the edges of a graph (i.e. they become hard to\n"   )
    doxyfile.write("# read).\n"                                                                        )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_TRANSPARENT = NO\n\n"                                                          )

    doxyfile.write("# Set the DOT_MULTI_TARGETS tag to YES to allow dot to generate multiple output\n" )
    doxyfile.write("# files in one run (i.e. multiple -o and -T options on the command line). This\n"  )
    doxyfile.write("# makes dot run faster, but since only newer versions of dot (>1.8.10) support\n"  )
    doxyfile.write("# this, this feature is disabled by default.\n"                                    )
    doxyfile.write("# The default value is: NO.\n"                                                     )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_MULTI_TARGETS = NO\n\n"                                                        )

    doxyfile.write("# If the GENERATE_LEGEND tag is set to YES doxygen will generate a legend page\n"  )
    doxyfile.write("# explaining the meaning of the various boxes and arrows in the dot generated\n"   )
    doxyfile.write("# graphs.\n"                                                                       )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("GENERATE_LEGEND = YES\n\n"                                                         )

    doxyfile.write("# If the DOT_CLEANUP tag is set to YES, doxygen will remove the intermediate dot\n")
    doxyfile.write("# files that are used to generate the various graphs.\n"                           )
    doxyfile.write("# The default value is: YES.\n"                                                    )
    doxyfile.write("# This tag requires that the tag HAVE_DOT is set to YES.\n\n"                      )

    doxyfile.write("DOT_CLEANUP = YES\n"                                                               )

    doxyfile.close()

    if not os.path.exists(doxyfilePath):
        print("Error: The test main file was not created!")
        sys.exit(ERROR_DOXYFILE_NOT_CREATED)



def generateDoxygenIntroFile(p_path, p_libName):
    """
    Generates a Doxygen mainfile (*.dox) with an introduction section.
    
    Args:
        p_path:    The path on disc where to create the library structure.
        p_libName: The name of the library (in lowercase).
    """

    doxyIntroPath = p_path + p_libName + "/doc/doxygen/mainpage.dox"
    
    doxyIntro = open(doxyIntroPath, "w+")
    
    doxyIntro.write("/***********************************************************************************************//**\n"  )
    doxyIntro.write(" * @mainpage " + p_libName + "\n"                                                                        )
    doxyIntro.write(" *\n"                                                                                                    )
    doxyIntro.write(" * @section intro Introduction\n"                                                                        )
    doxyIntro.write(" *\n"                                                                                                    )
    doxyIntro.write(" * @section licence Licence\n"                                                                           )
    doxyIntro.write(" *\n"                                                                                                    )
    doxyIntro.write(" **************************************************************************************************/\n\n")
    
    doxyIntro.close()

    if not os.path.exists(doxyIntroPath):
        print("Error: The Doxygen intro file was not created!")
        sys.exit(ERROR_DOXYINTRO_NOT_CREATED)



def generateDoxygenFiles(p_path, p_libName):
    """
    Generates the minimal required Doxygen files to document a 
    library.
    
    Args:
        p_path:    The path on disc where to create the library structure.
        p_libName: The name of the library (in lowercase).
    """
    generateDoxyfile         (p_path, p_libName)
    generateDoxygenIntroFile (p_path, p_libName)



def main(argv):
    """
    Runs the script.
    
    Args:
        argv    A list containing all the arguments.
    """

    nbArguments = len(argv)

    if nbArguments != 1 and nbArguments != NB_ARGUMENTS:
        print("Error: number of arguments.")
        sys.exit(ERROR_NB_ARGUMENTS)

    if (len(argv) == 1) and (argv[0] in ("-h", "--help")):
        printHelp()
        sys.exit()
    
    path    = fixPath(argv[0])
    libName = libNameToLowerCase(argv[1])

    if not os.path.exists(path):
        print("Error: path \"" + path + "\" does not exist!\n")
        sys.exit(ERROR_PATH_DOES_NOT_EXIST)

    if not libName.isalnum():
        print("Error: library name \"" + libName + "\" is invalid!\n")
        sys.exit(ERROR_LIB_NAME_INVALID)

    headerInfo = HeaderInformation()
    
    generateDirectoryStructure (path, libName)
    generateUnitTestMain       (path, libName)
    generateDoxygenFiles       (path, libName)
    generateMakefiles          (path, libName, headerInfo)
    
    sys.exit(EXEC_OK)

if __name__ == "__main__":
    main(sys.argv[1:])

