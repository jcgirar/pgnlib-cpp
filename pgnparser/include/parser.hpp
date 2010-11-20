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

#ifndef PGN_LIB_PARSER_HPP
#define PGN_LIB_PARSER_HPP

#include "ref_object.hpp"
#include "common_decl.hpp"

namespace pgn
{

/**
 * Get notification about syntax errors in pgn-file. User can implement the
 * interface and register it using IParser::setErrorHandler(...) method. */
class PGN_LIB_API IErrorHandlerCallback : public IRefObject
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
 *     IGame const* game;
 *     while ( (game = pgnparser->readGame()) != NULL )
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
class PGN_LIB_API IParser : public IRefObject
{
public:
    /**
     * Create an instance of IParser (factory method).
     * @param [in] pgnfile  name of pgn file in utf8 encoding.
     * @param [in] isStrict use false value if you want to skip well-known
     *                      standard violations which can be easily fixed by
     *                      the parser. Another scenario is to get notification
     *                      about such problems (strict == true) but returns
     *                      true from IErrorHandlerCallback::operator(...). In
     *                      this case parser will fix the problem and continue
     *                      parsing.
     * @return On success it returns an instance of IParser. Otherwise it
     * returns NULL. */
    static IParser* create(char const* pgnfile, bool isStrict = false);

    /**
     * Create an instance of IParser (factory method).
     * @param [in] pgnfile  name of pgn file.
     * @param [in] isStrict use false value if you want to skip well-known
     *                      standard violations which can be easily fixed by
     *                      the parser. Another scenario is to get notification
     *                      about such problems (strict == true) but returns
     *                      true from IErrorHandlerCallback::operator(...). In
     *                      this case parser will fix the problem and continue
     *                      parsing.
     * @return On success it returns an instance of IParser. Otherwise it
     * returns NULL. */
    static IParser* create(wchar_t const* pgnfile, bool isStrict = false);

    /**
     * Validate a game. Usually the method should be called after readGame()
     * method. You should always check that parsing is successful and returned
     * game is valid.
     *
     * @param [in] game     game which was returned by readGame() method.
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
     * @param [in] callback is error handler callback. */
    virtual void setErrorHandler(IErrorHandlerCallback* callback) = 0;

    /**
     * Get number of games. You should understand that whole PGN file will be
     * read on the call (if it has not read yet). If you need to iterate game
     * by game then avoid calling of the method. In any case only lightweight
     * parsing will be done.
     *
     * @return Number of games in the PGN file.
     *
     * Note: On syntax error IErrorHandlerCallback is called and number of
     * parsed games are returned. */
    virtual unsigned getGameCount() const = 0;

    /**
     * Read N-th game from pgnfile. There is no method which can return number
     * of games due to performance reason. The method will parse the file on
     * demand.
     *
     * @param [in] gameN    number of game (from 1 to N). If the parameter is
     *                      NEXT_ITEM then to read next game. For first call of
     *                      the method it means to read first game. For second
     *                      call of the method it means to read second game and
     *                      so on. If user has called readGame(N) (with
     *                      parameter) then next call without a parameter will
     *                      be equal to readGame(N+1).
     *
     * @return On success the method returns an instance of IGame which
     * represents gameN. If there is no game with given number the method
     * returns NULL. Returned object is valid till next call of the method
     * in the same thread. It means that IParser is owner of the object.
     *
     * Note: On syntax error IErrorHandlerCallback is called and
     * dummy instance of IGame is returned. Use isGameValid() method for
     * checking return value. */
    virtual IGame const* readGame(unsigned gameN = NEXT_ITEM) = 0;
};

} /* namespace pgn */

#endif /* #ifndef PGN_LIB_PARSER_HPP */

