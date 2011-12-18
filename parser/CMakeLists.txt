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

set(PGN_PARSER_library_name pgnparser)

include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB SOURCES src/*.cpp)
add_library(${PGN_PARSER_library_name} SHARED ${SOURCES})
target_link_libraries(${PGN_PARSER_library_name} ${Boost_LIBRARIES})
