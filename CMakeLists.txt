###############################################################################
# Copyright (C) 2010-2012 Nikita Manovich <nikita.manovich@gmail.com>
# 
# This file is part of C++ PGN parser, http://code.google.com/p/pgnlib-cpp
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.
###############################################################################

cmake_minimum_required(VERSION 2.6)
project(PGN_LIB)
set(CMAKE_BUILD_TYPE debug)

set(PGN_LIB_VERSION_MAJOR 0)
set(PGN_LIB_VERSION_MINOR 1)
set(PGN_LIB_VERSION_PATCH 0)

# Find and extend boost library. At the present moment there is no logging
# library inside boost. Thus I included a version which probably will be
# accepted soon.
find_package(Boost COMPONENTS thread iostreams REQUIRED)

# Build necessary 3-rd party software
add_subdirectory(3rd_parties)

# Build PGN parser library
add_subdirectory(pgnparser)

# Build additional tools
add_subdirectory(tools)

# Build tests for PGN library
add_subdirectory(tests)
