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

/**
 * Numeric Annotation Glyphs.
 * NAG zero is used for a null annotation; it is provided for the convenience
 * of software designers as a placeholder value and should probably not be
 * used in external PGN data.
 * NAGs with values from 1 to 9 annotate the move just played.
 * NAGs with values from 10 to 135 modify the current position.  
 * NAGs with values from 136 to 139 describe time pressure.  
 * Other NAG values are reserved for future definition. */
typedef enum
{
    /** null annotation */
    nagNull,
    /** good move (traditional "!") */
    nagGoodMove,
    /** poor move (traditional "?") */
    nagPoorMove,
    /** very good move (traditional "!!") */
    nagVeryGoodMove,
    /** very poor move (traditional "??") */
    nagVeryPoorMove,
    /** speculative move (traditional "!?") */
    nagSpeculativeMove,
    /** questionable move (traditional "?!") */
    nagQuestionableMove,
    /** forced move (all others lose quickly) */
    nagForcedMove,
    /** singular move (no reasonable alternatives) */
    nagSingularMove,
    /** worst move */
    nagWorstMove,
    /** drawish position */
    nagDrawishPosition,
    /** equal chances, quiet position */
    nagEqualChancesQuietPosition,
    /** equal chances, active position */
    nagEqualChancesActivePosition,
    /** unclear position */
    nagUnclearPosition,
    /** White has a slight advantage */
    nagWhiteSlightAdvantage,
    /** Black has a slight advantage */
    nagBlackSlightAdvantage,
    /** White has a moderate advantage */
    nagWhiteModerateAdvantage,
    /** Black has a moderate advantage */
    nagBlackModerateAdvantage,
    /** White has a decisive advantage */
    nagWriteDecisiveAdvantage,
    /** Black has a decisive advantage */
    nagBlackDecisiveAdvantage,
    /** White has a crushing advantage (Black should resign) */
    nagWhiteCrushingAdvantage,
    /** Black has a crushing advantage (White should resign) */
    nagBlackCrushingAdvantage,
    /** White is in zugzwang */
    nagWhiteInZugzwang,
    /** Black is in zugzwang */
    nagBlackInZugzwang,
    /** White has a slight space advantage */
    nagWhiteSlightSpaceAdvantage,
    /** Black has a slight space advantage */
    nagBlackSlightSpaceAdvantage,
    /** White has a moderate space advantage */
    nagWhiteModerateSpaceAdvantage,
    /** Black has a moderate space advantage */
    nagBlackModerateSpaceAdvantage,
    /** White has a decisive space advantage */
    nagWhiteDecisiveSpaceAdvantage,
    /** Black has a decisive space advantage */
    nagBlackDecisiveSpaceAdvantage,
    /** White has a slight time (development) advantage */
    nagWhiteSlightDevelopmentAdvantage,
    /** Black has a slight time (development) advantage */
    nagBlackSlightDevelopmentAdvantage,
    /** White has a moderate time (development) advantage */
    nagWhiteModerateDevelopmentAdvantage,
    /** Black has a moderate time (development) advantage */
    nagBlackModerateDevelopmentAdvantage,
    /** White has a decisive time (development) advantage */
    nagWhiteDecisiveDevelopmentAdvantage,
    /** Black has a decisive time (development) advantage */
    nagBlackDecisiveDevelopmentAdvantage,
    /** White has the initiative */
    nagWhiteInitiative,
    /** Black has the initiative */
    nagBlackInitiative,
    /** White has a lasting initiative */
    nagWhiteLastingInitiative,
    /** Black has a lasting initiative */
    nagBlackLastingInitiative,
    /** White has the attack */
    nagWhiteAttack,
    /** Black has the attack */
    nagBlackAttack,
    /** White has insufficient compensation for material deficit */
    nagWhiteInsufficientCompensation,
    /** Black has insufficient compensation for material deficit */
    nagBlackInsufficientCompensation,
    /** White has sufficient compensation for material deficit */
    nagWhiteSufficientCompensation,
    /** Black has sufficient compensation for material deficit */
    nagBlackSufficientCompensation,
    /** White has more than adequate compensation for material deficit */
    nagWhiteMoreThanAdequateCompensation,
    /** Black has more than adequate compensation for material deficit */
    nagBlackMoreThanAdequateCompensation,
    /** White has a slight center control advantage */
    nagWhiteSlightCenterControlAdvantage,
    /** Black has a slight center control advantage */
    nagBlackSlightCenterControlAdvantage,
    /** White has a moderate center control advantage */
    nagWhiteModerateCenterControlAdvantage,
    /** Black has a moderate center control advantage */
    nagBlackModerateCenterControlAdvantage,
    /** White has a decisive center control advantage */
    nagWhiteDecisiveCenterControlAdvantage,
    /** Black has a decisive center control advantage */
    nagBlackDecisiveCenterControlAdvantage,
    /** White has a slight kingside control advantage */
    nagWhiteSlightKingsideControlAdvantage,
    /** Black has a slight kingside control advantage */
    nagBlackSlightKingsideControlAdvantage,
    /** White has a moderate kingside control advantage */
    nagWhiteModerateKingsideControlAdvantage,
    /** Black has a moderate kingside control advantage */
    nagBlackModerateKingsideControlAdvantage,
    /** White has a decisive kingside control advantage */
    nagWhiteDecisiveKingsideControlAdvantage,
    /** Black has a decisive kingside control advantage */
    nagBlackDecisiveKingsideControlAdvantage,
    /** White has a slight queenside control advantage */
    nagWhiteSlightQeensideControlAdvantage,
    /** Black has a slight queenside control advantage */
    nagBlackSlightQeensideControlAdvantage,
    /** White has a moderate queenside control advantage */
    nagWhiteModerateQeensideControlAdvantage,
    /** Black has a moderate queenside control advantage */
    nagBlackModerateQeensideControlAdvantage,
    /** White has a decisive queenside control advantage */
    nagWhiteDecisiveQeensideControlAdvantage,
    /** Black has a decisive queenside control advantage */
    nagBlackDecisiveQeensideControlAdvantage,
    /** White has a vulnerable first rank */
    nagWhiteVulnerableFirstRank,
    /** Black has a vulnerable first rank */
    nagBlackVulnerableFirstRank,
    /** White has a well protected first rank */
    nagWhiteWellProtectedFirstRank,
    /** Black has a well protected first rank */
    nagBlackWellProtectedFirstRank,
    /** White has a poorly protected king */
    nagWhitePoorlyProtectedKing,
    /** Black has a poorly protected king */
    nagBlackPoorlyProtectedKing,
    /** White has a well protected king */
    nagWhiteWellProtectedKing,
    /** Black has a well protected king */
    nagBlackWellProtectedKing,
    /** White has a poorly placed king */
    nagWhitePoorlyPlacedKing,
    /** Black has a poorly placed king */
    nagBlackPoorlyPlacedKing,
    /** White has a well placed king */
    nagWhiteWellPlacedKing,
    /** Black has a well placed king */
    nagBlackWellPlacedKing,
    /** White has a very weak pawn structure */
    nagWhiteVeryWeakPawnStructure,
    /** Black has a very weak pawn structure */
    nagBlackVeryWeakPawnStructure,
    /** White has a moderately weak pawn structure */
    nagWhiteModeratelyWeakPawnStructure,
    /** Black has a moderately weak pawn structure */
    nagBlackModeratelyWeakPawnStructure,
    /** White has a moderately strong pawn structure */
    nagWhiteModeratelyStrongPawnStructure,
    /** Black has a moderately strong pawn structure */
    nagBlackModeratelyStrongPawnStructure,
    /** White has a very strong pawn structure */
    nagWhiteVeryStrongPawnStructure,
    /** Black has a very strong pawn structure */
    nagBlackVeryStrongPawnStructure,
    /** White has poor knight placement */
    nagWhitePoorKnightPlacement,
    /** Black has poor knight placement */
    nagBlackPoorKnightPlacement,
    /** White has good knight placement */
    nagWhiteGoodKnightPlacement,
    /** Black has good knight placement */
    nagBlackGoodKnightPlacement,
    /** White has poor bishop placement */
    nagWhitePoorBishopPlacement,
    /** Black has poor bishop placement */
    nagBlackPoorBishopPlacement,
    /** White has good bishop placement */
    nagWhiteGoodBishopPlacement,
    /** Black has good bishop placement */
    nagBlackGoodBishopPlacement,
    /** White has poor rook placement */
    nagWhitePoorRookPlacement,
    /** Black has poor rook placement */
    nagBlackPoorRookPlacement,
    /** White has good rook placement */
    nagWhiteGoodRookPlacement,
    /** Black has good rook placement */
    nagBlackGoodRookPlacement,
    /** White has poor queen placement */
    nagWhitePoorQueenPlacement,
    /** Black has poor queen placement */
    nagBlackPoorQueenPlacement,
    /** White has good queen placement */
    nagWhiteGoodQueenPlacement,
    /** Black has good queen placement */
    nagBlackGoodQueenPlacement,
    /** White has poor piece coordination */
    nagWhitePoorPieceCoordination,
    /** Black has poor piece coordination */
    nagBlackPoorPieceCoordination,
    /** White has good piece coordination */
    nagWhiteGoodPieceCoordination,
    /** Black has good piece coordination */
    nagBlackGoodPieceCoordination,
    /** White has played the opening very poorly */
    nagWhiteOpeningVeryPoorly,
    /** Black has played the opening very poorly */
    nagBlackOpeningVeryPoorly,
    /** White has played the opening poorly */
    nagWhiteOpeningPoorly,
    /** Black has played the opening poorly */
    nagBlackOpeningPoorly,
    /** White has played the opening well */
    nagWhiteOpeningWell,
    /** Black has played the opening well */
    nagBlackOpeningWell,
    /** White has played the opening very well */
    nagWhiteOpeningVeryWell,
    /** Black has played the opening very well */
    nagBlackOpeningVeryWell,
    /** White has played the middlegame very poorly */
    nagWhiteMiddlegameVeryPoorly,
    /** Black has played the middlegame very poorly */
    nagBlackMiddlegameVeryPoorly,
    /** White has played the middlegame poorly */
    nagWhiteMiddlegamePoorly,
    /** Black has played the middlegame poorly */
    nagBlackMiddlegamePoorly,
    /** White has played the middlegame well */
    nagWhiteMiddlegameWell,
    /** Black has played the middlegame well */
    nagBlackMiddlegameWell,
    /** White has played the middlegame very well */
    nagWhiteMiddlegameVeryWell,
    /** Black has played the middlegame very well */
    nagBlackMiddlegameVeryWell,
    /** White has played the ending very poorly */
    nagWhiteEndingVeryPoorly,
    /** Black has played the ending very poorly */
    nagBlackEndingVeryPoorly,
    /** White has played the ending poorly */
    nagWhiteEndingPoorly,
    /** Black has played the ending poorly */
    nagBlackEndingPoorly,
    /** White has played the ending well */
    nagWhiteEndingWell,
    /** Black has played the ending well */
    nagBlackEndingWell,
    /** White has played the ending very well */
    nagWhiteEndingVeryWell,
    /** Black has played the ending very well */
    nagBlackEndingVeryWell,
    /** White has slight counterplay */
    nagWhiteSlightCounterplay,
    /** Black has slight counterplay */
    nagBlackSlightCounterplay,
    /** White has moderate counterplay */
    nagWhiteModerateCounterplay,
    /** Black has moderate counterplay */
    nagBlackModerateCounterplay,
    /** White has decisive counterplay */
    nagWhiteDecisiveCounterplay,
    /** Black has decisive counterplay */
    nagBlackDecisiveCounterplay,
    /** White has moderate time control pressure */
    nagWriteModerateTimeControlPressure,
    /** Black has moderate time control pressure */
    nagBlackModereteTimeControlPressure,
    /** White has severe time control pressure */
    nagWriteSevereTimeControlPressure,
    /** Black has severe time control pressure */
    nagBlackSevereTimeControlPressure,
    /** It is last numeric annotation glyph */
    nagLastNumericAnnotationGlyph
} NAG_t;

/** Different formats of NAG representation. */
typedef enum
{
    nfNumeric,  /**< $1, $2 and so on. */
    nfBrief,    /**< ?, !!, and so on. In case brief description is absent
                     nfDetailed is used. */
    nfDetailed  /**< Detailed description for given NAG. */
} NAG_format_t;

/** The type describes an idetifier of variation. */
typedef unsigned variation_t;
extern const variation_t MAIN_LINE; /**< main line variation */
extern const variation_t NULL_VARIATION;
extern const unsigned NEXT_ITEM;

class PGN_PARSER_API IMove
{
public:
    /**
     * Convert NAG value to string.
     * @param [in] nag      numeric annotation glyph.
     * @param [in] fmt      format of string for NAG representation.
     * @return The method always returns null-terminated utf8 string which
     * represents given NAG value. */
    static char const* toString(NAG_t nag, NAG_format_t fmt = nfBrief);

    /**
     * Get standard algebraic notation for given move.
     * @return If the move is valid it is valid null-terminated string with
     * SAN of the move. Otherwise NULL is returned. */
    virtual char const* getSAN() const = 0;

    /** Get set of NAGs for the move.
     * @param [in] n        number of NAG from 1 till N. Special NEXT_ITEM can
     *                      be used for easy naviation.
     *
     * @return List of NAGs. Last elemement of the list is nagNull. If first
     * element is nagNull also it means the move doesn't contain NAGs. */
    virtual NAG_t getNAG(unsigned n = NEXT_ITEM) const = 0;

    /**
     * Get comment for the move.
     * @return If the move contains a comment the method returns it. Otherwise
     * NULL is returned. */
    virtual char const* getComment() const = 0;

    /**
     * Get number of the move.
     * @return If the move is valid the method returns its number. Otherwise
     * invalid number (zero) is returned. */
    virtual unsigned getMoveNumber() const = 0;

    /**
     * Get variation of the move (MAIN_LINE and so on).
     * @return If the move is valid the method returns variation number.
     * Otherwise invalid number (zero) is returned. */
    virtual variation_t getVariation() const = 0;

protected:
    virtual ~IMove() {}
};

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
    virtual unsigned getMoveNumber(variation_t v) const = 0;

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
class PGN_PARSER_API IParser : public IRefObject
{
public:
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

#endif /* #ifndef PGN_PARSER_HPP */

