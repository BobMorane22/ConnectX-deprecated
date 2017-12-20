#!/bin/bash

#---------------------------------------------------------------------------------------------------
#
# This script helps switch between installed GCC versions. GCC versions need to be registered with
# the update-alternative tools. See this link for more information: 
# 
#                   http://charette.no-ip.com:81/programming/2011-12-24_GCCv47/
#
# Also, the two commented lines at the beginning of the script were used sucessfully to register
# GCCv5 and GCCv7 on my debian machine.
#
# Note: Run this script in sudo mode.
#
# @file     switchGcc.sh
# @author   Éric Poirier
# @version  1.0
# @date     August, 2017
#
#---------------------------------------------------------------------------------------------------

#
# sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 40 --slave /usr/bin/g++ g++ /usr/bin/g++-7
# sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 --slave /usr/bin/g++ g++ /usr/bin/g++-5

update-alternatives --config gcc
