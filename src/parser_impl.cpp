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

#include "game.hpp"
#warning "TODO: replace game.hpp on game_impl.hpp"
#include "parser_impl.hpp"

#include <cstdlib>

namespace pgn
{

const variation_t MAIN_LINE = 0;
const variation_t NULL_VARIATION = 0;
const tag_pair_t  NULL_TAG_PAIR = { NULL, NULL };
const unsigned NEXT_ITEM = 0;

template <typename T> void Parser::initialize(T const* pgnfile, bool isStrict)
{
    m_isStrict = isStrict;
}

/* The method will parse till gameN game and more (by performance reason). */
void Parser::doLightWeightParsing(unsigned gameN)
{
    if ( getGameInFileCacheSize() > gameN )
    {
        return ;
    }

    boost::unique_lock<boost::shared_mutex> lock(m_gameInFileCacheLock);

    bool isLightWeightParsingDone = false;

    /* TODO: implement the method (parse all games in buffer) */

    m_isLightweightParsingDone = isLightWeightParsingDone;
}

IGame const* Parser::readGame(unsigned gameN)
{
    return 0;
}

IParser* IParser::create(char const* pgnfile, bool isStrict)
{
    return new Parser(pgnfile, isStrict);
}

IParser* IParser::create(wchar_t const* pgnfile, bool isStrict)
{
    return new Parser(pgnfile, isStrict);
}

} /* namespace pgn */

