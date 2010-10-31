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

#ifndef PGN_PARSER_HPP
#define PGN_PARSER_HPP

#include "ref_object.hpp"
#include "export_decl.hpp"

namespace pgn
{

class IMove;

class PGN_PARSER_API IVariation : public IRefObject
{
public:
    virtual char const* getMoveText() const = 0;

    virtual unsigned getMoveCount() const = 0;
    virtual IMove const* getMove(unsigned n) const = 0;
};

class PGN_PARSER_API IMove : public IRefObject
{
public:
    virtual char const* getSAN() const = 0;
    virtual char const* getComment() const = 0;
    virtual unsigned getMoveNumber() const = 0;

    virtual bool hasAlternativeVariation() const = 0;
    virtual unsigned getVariationCount() const = 0;
    virtual IVariation const* getVariation(unsigned n) const = 0;
};

typedef enum
{
    grWhiteWin,
    grBlackWin,
    grDraw,
    grUndefined
} game_result_t;

class PGN_PARSER_API IGame : public IVariation
{
public:
    /* This is the STR (Seven Tag Roster). The interpretation of these tags
     * is fixed as is the order in which they appear. Although the definition
     * and use of additional tag names and semantics is permitted and
     * encouraged when needed, the STR is the common ground that all programs
     * should follow for public data interchange. */
    virtual char const* getTagEvent() const = 0;
    virtual char const* getTagSite()  const = 0;
    virtual char const* getTagDate()  const = 0;
    virtual char const* getTagRound() const = 0;
    virtual char const* getTagWhite() const = 0;
    virtual char const* getTagBlack() const = 0;
    virtual game_result_t getTagResult() const = 0;

    virtual char const* getTagValue(char const* name) const = 0;
};

typedef enum
{
    seIllegalMove,
    seIllegalToken,
    seIllegalTagValue,
    seIllegalTagName,
    seIllegalTerminationMarker,
    seUndefinedErrorCode
} syntax_error_t;

class PGN_PARSER_API IErrorHandler : public IRefObject
{
public:
    virtual bool callback(syntax_error_t code, char const* description,
        unsigned long long line, unsigned long long column) = 0;
};

typedef enum
{
    rmDefault
} read_mode_t;

class PGN_PARSER_API IParser : public IRefObject
{
public:
    static IParser* create(char const* pgnfile);

    virtual void setErrorHandler(IErrorHandler* handler) = 0;
    virtual IGame const* readGame(read_mode_t mode = rmDefault) = 0;
};

} /* namespace pgn */

#endif /* #ifndef PGN_PARSER_HPP */

