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

/**
 * The class represents information about a game in pgn-file. A PGN game is
 * composed of two sections. The first is the tag pair section and the second
 * is the movetext section. The tag pair section provides information that
 * identifies the game by defining the values associated with a set of standard
 * parameters. The movetext section gives the usually enumerated and possibly
 * annotated moves of the game along with the concluding game termination
 * marker. The chess moves themselves are represented using SAN (Standard
 * Algebraic Notation)
 *
 * You can get STR (Seven Tag Roster) directly and value of any other tags
 * using the following methods:
 *
 * getTagEvent(), getTagSite(), getTagDate(), getTagRound(), getTagWhite(),
 * getTagBlack(), getTagResult(), getTagValue().
 *
 * The interpretation of STR tags is fixed as is the order in which
 * they appear. Although the definition and use of additional tag names
 * and semantics is permitted and encouraged when needed, the STR is
 * the common ground that all programs should follow for public data
 * interchange. */
class PGN_PARSER_API IGame : public IVariation
{
public:
    /** Get the name of the tournament or match event. */
    virtual char const* getTagEvent() const = 0;
    /** Get the location of the event. */
    virtual char const* getTagSite() const = 0;
    /** Get the starting date of the game. */
    virtual char const* getTagDate() const = 0;
    /** Get the playing round ordinal of the game. */
    virtual char const* getTagRound() const = 0;
    /** Get the player of the white pieces. */
    virtual char const* getTagWhite() const = 0;
    /** Get the player of the black pieces. */
    virtual char const* getTagBlack() const = 0;
    /** Get the result of the game. */
    virtual char const* getTagResult() const = 0;

    /**
     * Get an arbitrary value of tag pair section by tag's name. At the
     * present moment only string values are supported (any non-string value
     * will be returned as string). */
    virtual char const* getTagValue(char const* name) const = 0;

    /** Get the result of the game. */
    virtual game_result_t getResult() const = 0;
};

typedef enum
{
    seValid,
    seIllegalMove,
    seIllegalToken,
    seIllegalTagValue,
    seIllegalTagName,
    seIllegalTerminationMarker,
    seUndefinedErrorCode
} syntax_error_t;

class PGN_PARSER_API IErrorHandlerCallback : public IRefObject
{
public:
    virtual bool operator()(bool isCritical, syntax_error_t code,
        char const* description, unsigned long long line, unsigned column) = 0;
};

typedef enum
{ 
    cmSimple,
    cmComplete
} check_mode_t;

class PGN_PARSER_API IParser : public IRefObject
{
public:
    static IParser* create(char    const* pgnfile);
    static IParser* create(wchar_t const* pgnfile);

    /**
     * Validate a game.
     * @param [in] game     game which was returned by read() method.
     * @param [in] mode     mode of game validation.
     * @return The method return seValid in case the game is valid. Otherwise
     * it returns syntax error. In case of deep check the method can call
     * IErrorHandlerCallback. */
    static syntax_error_t isGameValid(IGame const* game,
        check_mode_t mode = cmSimple);

    /**
     * Set an error handler for getting information about parsing errors and
     * warnings. If you want to reset previous passed callback just call
     * setErrorHandler(NULL). */
    virtual void setErrorHandler(IErrorHandlerCallback* callback) = 0;

    /**
     * Read N-th game from pgnfile.
     * @param [in] gameN    number of game (from 1 to N).
     * @return On success the method returns an instance of IGame which
     * represents gameN. If there is no game with given number the method
     * returns NULL. On syntax error IErrorHandlerCallback is called and
     * dummy instance of IGame is returns. Please use isGameValid() method
     * for checking return value. */
    virtual IGame const* read(unsigned gameN) = 0;
};

} /* namespace pgn */

#endif /* #ifndef PGN_PARSER_HPP */

