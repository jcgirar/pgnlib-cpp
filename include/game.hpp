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

#ifndef PGN_GAME_HPP
#define PGN_GAME_HPP

#include "common_decl.hpp"

namespace pgn
{

/**
 * Set of possible game results. Basically game result is determined based on
 * termination marker. In case it doesn't present or wrong result tag will be
 * used for the purpose. */
typedef enum
{
    grWhiteWin,                                 /**< 1-0 */
    grBlackWin,                                 /**< 0-1 */
    grDraw,                                     /**< 1/2-1/2 */
    grUndefined                                 /**< * */
} game_result_t;

/**
 * A tag pair is composed of four consecutive tokens: a left bracket token,
 * a symbol token, a string token, and a right bracket token. The symbol token
 * is the tag name and the string token is the tag value associated with the
 * tag name. (There is a standard set of tag names and semantics described
 * below.) The same tag name should not appear more than once in a tag pair
 * section. */
typedef struct
{
    char const* name;                           /**< name of the tag */
    char const* value;                          /**< value of the tag */
} tag_pair_t;

/** Invalid value of tag_pair_t. */
extern const tag_pair_t NULL_TAG_PAIR;

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
class PGN_PARSER_API IGame
{
public:
    /**
     * Validate the move. Usually the method should be called after getMove()
     * method. You should always check that parsing is successful and returned
     * move is valid.
     *
     * @param [in] move     move which was returned by getMove() method.
     *
     * @return The method return seValid in case the move is valid. Otherwise
     * it returns syntax error. */
    static syntax_error_t isMoveValid(IMove const* move);

    /**
     * Get number of the game. Using the number you can get the game again
     * with help of readGame() method.
     * @return Sequence number of the game. */
    virtual unsigned getSequenceNumber() const = 0;

    /**
     * Get the name of the tournament or match event.
     * @return Null-terminated string which contains value of "Event" tag. */
    virtual char const* getTagEvent() const = 0;

    /**
     * Get the location of the event.
     * @return Null-terminated string which contains value of "Site" tag. */
    virtual char const* getTagSite() const = 0;

    /**
     * Get the starting date of the game.
     * @return Null-terminated string which contains value of "Date" tag. */
    virtual char const* getTagDate() const = 0;

    /**
     * Get the playing round ordinal of the game.
     * @return Null-terminated string which contains value of "Round" tag. */
    virtual char const* getTagRound() const = 0;

    /**
     * Get the player of the white pieces.
     * @return Null-terminated string which contains value of "White" tag. */
    virtual char const* getTagWhite() const = 0;

    /**
     * Get the player of the black pieces.
     * @return Null-terminated string which contains value of "Black" tag. */
    virtual char const* getTagBlack() const = 0;

    /**
     * Get the result of the game.
     * @return Null-terminated string which contains value of "Result" tag. */
    virtual char const* getTagResult() const = 0;

    /**
     * Get an arbitrary value of tag pair section by tag's name. At the
     * present moment only string values are supported (any non-string value
     * will be returned as string).
     * @return Null-terminated string which contains tag value. */
    virtual char const* getTagValue(char const* name) const = 0;

    /**
     * Get number of tag pairs in tag pair section.
     * @return Number of tag pairs. */
    virtual unsigned getTagPairCount() const = 0;

    /**
     * Iterate through tag pairs.
     * @param [in] n    number of a tag pair. You can use special NEXT_ITEM
     *                  value for getting tag pair one by one.
     *
     * @return On success a tag pair is returned. Otherwise NULL_TAG_PAIR
     * is returned. */
    virtual tag_pair_t getTagPair(unsigned n = NEXT_ITEM) const = 0;

    /**
     * Get the result of the game. Each chess game can have one of the
     * following results: "1-0" (White wins), "0-1" (Black wins), "1/2-1/2"
     * (drawn game), and "*" (game in progress, result unknown, or game
     * abandoned).
     * @return Result of the game. */
    virtual game_result_t getResult() const = 0;

    /**
     * Get movetext section without termination marker.
     * @return Null-terminated string which contains movetext section. */
    virtual char const* getMoveText() const = 0;

    /**
     * Naviate by movetext section.
     * @param [in] n    number of move from 1 till N.
     * @param [in] v    identifier of variation from MAIN_LINE till
     *                  MAIN_LINE + L. What is L here? You can think that a
     *                  game with RAV (Recursive Annotation Variation) is a
     *                  complex tree. Number of all leaves is L. You can get
     *                  the number using getVariationCount() method.
     *
     * @return On success the method returns an instance of IMove which
     * represents n-th move. If there is no move or variation with given
     * number the method returns NULL. Returned object is valid till next
     * call of the method in the same thread. It means that IGame is owner
     * of the object.
     *
     * Note: On syntax error IErrorHandlerCallback is called and
     * dummy instance of IMove is returned. Use isMoveValid() method for
     * checking return value. */
    virtual IMove const* getMove(unsigned n,
        variation_t v = MAIN_LINE) const = 0;

    /**
     * Get number of moves for given variation. Calling the method will
     * lead to parsing movetext section (if it has not been parsed yet).
     * @param [in] v    identifier of a variation.
     *
     * @return Number of moves for given variation. */
    virtual unsigned getMoveCount(variation_t v) const = 0;

    /**
     * Get number of variation in the game (number of leaves in game tree).
     * Calling the method will lead to parsing movetext section (if it has
     * not been parsed yet) fully.
     * @return Number of variation in the game.*/
    virtual unsigned getVariationCount() const = 0;

    /**
     * Get number of variations for given move. In game tree these will be child
     * variations (IMove::getVariation() is parent variation). Calling the
     * method will lead to parsing movetext section (if it has not been parsed
     * yet).
     * @param [in] move     a move in a variation of the game.
     *
     * @return Number of variations for given move. */
    virtual unsigned getVariationCount(IMove const* move) const = 0;

    /**
     * Get all variations which are connected with given move.
     * Each move can contain several alternative variations. Using the method
     * you can get all identifiers. It isn't efficient to use only getMove
     * method for building game tree. You can think that using the method
     * you get all child variations for give move.
     *
     * @param [in] move     move which was get from getMove method.
     * @param [in] n        number of variation for given move from 1 till
     *                      N where N is number of variations.
     * @return On success it returns an idetifier of a variant. Otherwise
     * NULL_VARIATION is returned. */
    virtual variation_t getVariation(IMove const* move,
        unsigned n = NEXT_ITEM) const = 0;

protected:
    virtual ~IGame() {}
};

} /* namespace pgn */

#endif /* #ifndef PGN_GAME_HPP */

