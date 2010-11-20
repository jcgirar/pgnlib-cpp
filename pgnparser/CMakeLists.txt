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

# Export public header files into "include/pgn" directory
add_custom_target(export-public-headers ALL)
file(GLOB PGN_PARSER_headers include/*.hpp)
foreach (HEADER IN ITEMS ${PGN_PARSER_headers})
    get_filename_component(FILENAME "${HEADER}" NAME)
    add_custom_command(TARGET export-public-headers
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${HEADER}" "${CMAKE_INCLUDE_OUTPUT_DIRECTORY}/pgn/${FILENAME}")
    install(FILES "${HEADER}" DESTINATION "include/pgn")
endforeach()

set(PGN_PARSER_library_name pgnparser)

# The variables are exported. It is better to use <pgn/parser.hpp> style of
# include pragma in tools and tests from my point of view.
set(PGN_PARSER_LIBRARIES ${PGN_PARSER_library_name})

include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB SOURCES src/*.cpp)
add_library(${PGN_PARSER_library_name} SHARED ${SOURCES})
target_link_libraries(${PGN_PARSER_library_name} ${Boost_LIBRARIES})

