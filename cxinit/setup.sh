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


# REPOSITORY UPDATE
# ----------------------------------------------------------------------------------#
sudo apt-get update
sudo apt-get upgrade


# REQUIRED PACKAGES
# ----------------------------------------------------------------------------------#
build=(
    build-essential         # gcc/g++, make
    cmake                   # Build tool (Google Tests)
)

tools=(
    git                     # Version control
    python                  # Cross plateform scripting
)

tests=(
    libgtest-dev            # Google Tests (unit testing)
)

ui=(
    #libncurses5-dev         # Developer libraries for ncurses
    #libncursesw5-dev        # Developer libraries for ncursesw
    #libgtkmm-3.0-dev        # C++ wrapper for Gtk
    #libgstreamermm-1.0-dev  # C++ wrapper library for GStreamer
)

doc=(
    doxygen                 # Self-documenting tool for C/C++
    doxygen-gui             # GUI for Doxygen
    dia                     # Create schematic and UML
    texlive-full            # Write scientific documents
    #libgtkmm-3.0-doc
    #libgstreamermm-1.0-doc
    devhelp                 # Read documentation offline
)


# INSTALL
# ----------------------------------------------------------------------------------#
sudo apt-get -y install ${build[@]} ${tools[@]} ${tests[@]} ${ui[@]} ${doc[@]}

# Some additionnal steps for Google Tests:
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
