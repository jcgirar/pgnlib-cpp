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

#include <string>
#include <cstdlib>

namespace pgn
{

const variation_t MAIN_LINE = 0;
const variation_t NULL_VARIATION = 0;
const tag_pair_t  NULL_TAG_PAIR = { NULL, NULL };
const unsigned NEXT_ITEM = 0;

void LightWeightSkipper::initialize()
{
    using qi::iso8859_1::char_;

    /* There is a special escape mechanism for PGN data. This mechanism is
     * triggered by a percent sign character ("%") appearing in the first
     * column of a line; the data on the rest of the line is ignored. */
    m_ignoredLine = (qi::eol >> char_('%') >> *(char_ - qi::eol));
    m_ignoredLine.name("ignored line");

    /* There are two kinds of comments. The first comment type starts with
     * a semicolon character and continues to the end of the line. The
     * second kind starts with a left brace character and continues to the next
     * right brace character. Comments cannot appear inside any token. Comments
     * do not nest. */
    m_comment = (
        (char_(';') >> *(char_ - qi::eol)) |
        (char_('{') >> *(char_ - char_('}')) >> char_('}'))
    );
    m_comment.name("comment");

    entryPoint = m_ignoredLine | m_comment | qi::iso8859_1::space;
    entryPoint.name("light-weight skipper");
}

void LightWeightGrammar::initialize()
{
    using qi::iso8859_1::char_;

    /* Tag names is that they are composed exclusively of letters, digits, and
     * the underscore character. */
    m_tagName = +(qi::iso8859_1::alnum | char_('_'));
    m_tagName.name("tag name");

    /* Tag value is a string token. The string token is a sequence of zero or
     * more printing characters delimited by a pair of quote characters. An
     * empty string is represented by two adjacent quotes. A quote inside a
     * string is represented by the backslash immediately followed by a quote.
     * A backslash inside a string is represented by two adjacent backslashes.
     * Non-printing characters like newline and tab are not permitted inside
     * of strings. A string token is terminated by its closing quote. */
    m_tagValue = (
        char_('"') >>
        *qi::no_skip[
            char_('\\') >> char_('\\') |
            char_('\\') >> char_('"')  | /* why does char_("\\\"") not work? */
            qi::iso8859_1::graph - char_('"') |
            char_(' ')
        ] >> 
        char_('"')
    );
    m_tagValue.name("tag value");

    /* A tag pair is composed of four consecutive tokens: a left bracket token,
     * a symbol token, a string token, and a right bracket token. */
    m_tagPair = (
        char_('[') >> m_tagName >> m_tagValue >> char_(']')
    );
    m_tagPair.name("tag pair");

    /* The tag pair section is composed of a series of zero or more tag
     * pairs. */
    m_tagPairSection = +m_tagPair;
    m_tagPairSection.name("tag pair section");

    /* A PGN database file is a sequential collection of zero or more PGN
     * games. An empty file is a valid. A PGN game is composed of two sections.
     * The first is the tag pair section and the second is the movetext
     * section. */
    entryPoint = m_tagPairSection >> *(char_ >> !m_tagPair);
    entryPoint.name("light-weight grammar");
    qi::debug(entryPoint);
}

template <typename T> void Parser::initialize(T const* pgnfile, bool isStrict)
{
    m_isStrict = isStrict;
    m_mappedFile.open(std::basic_string<T>(pgnfile), 0, 10000);
    doLightWeightParsing(1000);
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

    /* TODO: Get position after last parsing game */
    char const* beginIt = m_mappedFile.getData();
    char const* endIt = beginIt + m_mappedFile.getMappedSize();

    bool isOk = qi::phrase_parse(beginIt, endIt, LightWeightGrammar(),
        LightWeightSkipper());

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

