###############################################################################
# Copyright (C) 2010 Nikita Manovich <nikita.manovich@gmail.com>
# 
# This file is part of C++ PGN parser, http://code.google.com/p/pgnparser-cpp
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

cmake_minimum_required(VERSION 2.8)
project(PGN_LIB)

set(PGN_LIB_VERSION_MAJOR 0)
set(PGN_LIB_VERSION_MINOR 1)
set(PGN_LIB_VERSION_PATCH 0)

set(CMAKE_INCLUDE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/include)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Find and extend boost library. At the present moment there is no logging
# library inside boost. Thus I included a version which probably will be
# accepted soon.
find_package(Boost 1.44 COMPONENTS thread REQUIRED)
set(Boost_logging_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/3rd_parties/logging)
set(Boost_INCLUDE_DIRS "${Boost_INCLUDE_DIRS} ${Boost_logging_INCLUDE_DIRS}")

# Build PGN parser library
add_subdirectory(pgnparser)

# Common definitions for any executable which will be linked with PGN library
include_directories(${CMAKE_INCLUDE_OUTPUT_DIRECTORY})
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

# Build additional tools
add_subdirectory(tools)

# Build tests for PGN library
# add_subdirectory(tests)

