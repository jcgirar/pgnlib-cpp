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
    seIllegalToken,
    seIllegalTagValue,
    seIllegalTagName,
    seIllegalMove,
    seIllegalTerminationMarker,
    seUndefinedErrorCode
} syntax_error_t;

/**
 * Get notification about syntax errors in pgn-file. User can implement the
 * interface and register it using IParser::setErrorHandler(...) method. */
class PGN_PARSER_API IErrorHandlerCallback : public IRefObject
{
public:
    /** 
     * Notify about a syntax error in pgn-file.
     * @param [in] isCritical   true in case the error is fatal. In this case
     *                          pgn-file is corrupted and can be read.
     * @param [in] code         error code of the syntax error.
     * @param [in] description  string with description of the syntax error.
     * @param [in] line         number of line where the syntax error is
     *                          occurred.
     * @param [in] column       number of column where the syntax error is
     *                          occurred.
     * @return If user want to stop processing of pgn-file false should be
     * returned. Otherwise the method has to return true. If isCritical is
     * true than returned value of the method is ignored. */
    virtual bool operator()(bool isCritical, syntax_error_t code,
        wchar_t const* description, unsigned long long line,
        unsigned column) = 0;
};

/**
 * The main interface for parsing PGN files.
 *
 * @code Example of using pgn::IParser interface:
 * boost::intrusive_ptr<pgn::IParser> pgnparser;
 * pgnparser = pgn::IParser::create("/path/to/pgnfile");
 *
 * if ( pgnparser )
 * {
 *     pgnparser->setErrorHandler(...);
 *
 *     boost::intrusive_ptr<IGame> game;
 *     while ( (game = pgnparser->read()) != NULL )
 *     {
 *         if ( pgn::IParser::isGameValid(game) != pgn::seValid )
 *         {
 *             break;
 *         }
 *
 *         ...
 *     }
 * }
 * @endcode */
class PGN_PARSER_API IParser : public IRefObject
{
public:
    /** Next game constant. It is used in read(...) method. */
    static const unsigned NEXT_GAME;

    /**
     * Create an instance of IParser (factory method).
     * @param pgnfile       name of pgn file in utf8 encoding.
     * @return On success it returns an instance of IParser. Otherwise it
     * returns NULL. */
    static IParser* create(char const* pgnfile);

    /**
     * Create an instance of IParser (factory method).
     * @param pgnfile       name of pgn file.
     * @return On success it returns an instance of IParser. Otherwise it
     * returns NULL. */
    static IParser* create(wchar_t const* pgnfile);

    /**
     * Validate a game. Usually the method should be called after read() method.
     * You should always check that parsing is successful and returned game is
     * valid.
     *
     * @param [in] game     game which was returned by read() method.
     * @param [in] deep     mode of game validation. Deep validation requires
     *                      much time (try to find illegal moves and other
     *                      critical errors in movetext section of the game).
     *                      By default, only trivial checks are done.
     *
     * @return The method return seValid in case the game is valid. Otherwise
     * it returns syntax error. In case of deep check the method can call
     * IErrorHandlerCallback. */
    static syntax_error_t isGameValid(IGame const* game, bool deep = false);

    /**
     * Set an error handler for getting information about syntax errors and
     * warnings. If you want to reset callback just call setErrorHandler(NULL).
     * @param [in] callback is error handler callback.
     * @param [in] strict   use false value if you want to skip well-known
     *                      standard violations which can be easily fixed by
     *                      the parser. Another scenario is to get notification
     *                      about such problems (strict == true) but returns
     *                      true from IErrorHandlerCallback::operator(...). In
     *                      this case parser will fix the problem and continue
     *                      parsing.
     */
    virtual void setErrorHandler(IErrorHandlerCallback* callback,
        bool strict = false) = 0;

    /**
     * Read N-th game from pgnfile. There is no method which can return number
     * of games due to performance reason. The method will parse the file on
     * demand.
     *
     * @param [in] gameN    number of game (from 1 to N). If the parameter is
     *                      zero it means to read next game. For first call of
     *                      the method it means to read first game. For second
     *                      call of the method it means to read second game and
     *                      so on. If user has called read(N) (with parameter)
     *                      then next call without a parameter will be equal to
     *                      read(N+1).
     *
     * @return On success the method returns an instance of IGame which
     * represents gameN. If there is no game with given number the method
     * returns NULL.
     *
     * Note: On syntax error IErrorHandlerCallback is called and
     * dummy instance of IGame is returned. Use isGameValid() method for
     * checking return value. */
    virtual IGame const* read(unsigned gameN = NEXT_GAME) = 0;
};

} /* namespace pgn */

#endif /* #ifndef PGN_PARSER_HPP */

