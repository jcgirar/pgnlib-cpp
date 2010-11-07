/**
 * Copyright (C) 2010 Nikita Manovich <nikita.manovich@gmail.com>
 * 
 * This file is part of C++ PGN parser, http://code.google.com/p/pgnparser-cpp
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PGN_COMMON_DECL_HPP
#define PGN_COMMON_DECL_HPP

#include "export_decl.hpp"

namespace pgn
{

/** The type describes an idetifier of variation. */
typedef unsigned variation_t;
extern const variation_t MAIN_LINE; /**< main line variation */
extern const variation_t NULL_VARIATION;
extern const unsigned NEXT_ITEM;

/**
 * Set of possible syntax errors which can be recognized by pgn::IParser. In
 * case of a syntax error can not be described using any meaningful error
 * code than seUndefinedErrorCode will be used. */
typedef enum
{
    seValid,
    seIllegalToken,
    seIllegalTagValue,
    seIllegalTagName,
    seIllegalMove,
    seIllegalTerminationMarker,
    seUndefinedErrorCode
} syntax_error_t;

class IMove;                                    /**< forward declaration */
class IGame;                                    /**< forward declaration */
class IParser;                                  /**< forward declaration */

} /* namespace pgn */

#endif /* #ifndef PGN_COMMON_DECL_HPP */

