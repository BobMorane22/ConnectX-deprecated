#!/bin/bash

#-----------------------------------------------------------------------------------#
# Build initial setup.
#
# Before building Connect X on a machine, you can make sure all the necessary tools
# to build the software (i.e. to run make) are installed on the system. The tool
# works with Ubuntu (and all close derivatives, such as Xubuntu, for example). You
# can run it by:
#
#   1. Opening a terminal.
#
#   2. Moving to the directory containing the script 'software.sh'.
#
#   3. Giving execution rights to the file (requires root privileges):
#
#        >> sudo chmod +x softwares.sh
#
#   4. Running the script:
#
#        >> sudo ./software.sh
#
#
# @author   Eric Poirier
# @date     December, 2017
# @version  1.0
#
#-----------------------------------------------------------------------------------#


# SYSTEM UPDATE
# ----------------------------------------------------------------------------------#
sudo apt-get update
sudo apt-get upgrade


# REQUIRED PACKAGES
# ----------------------------------------------------------------------------------#
build=(
    build-essentials  # gcc/g++, make
    cmake             # cmake (necessary to buils libgtest)
)

tools=(
    git               # Git
    python            # Python
)

tests=(
    libgtest-dev      # Google Tests (unit testing)
)

doc=(
    doxygen           # Doxygen
    doxygen-gui       # Doxygen gui-wizzard
    dia               # Dia (UML)
    texlive-full      # LaTeX
)


# INSTALL
# ----------------------------------------------------------------------------------#
sudo apt-get -y install ${build[@]} ${tools[@]} ${doc[@]}

# Some additionnal steps for Google Tests:
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
