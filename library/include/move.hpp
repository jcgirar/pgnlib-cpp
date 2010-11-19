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

#ifndef PGN_MOVE_HPP
#define PGN_MOVE_HPP

#include "common_decl.hpp"

namespace pgn
{

/** Numeric Annotation Glyphs. {{{
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
} NAG_t; /* }}} */

/** Different formats of NAG representation. */
typedef enum
{
    nfNumeric,  /**< $1, $2 and so on. */
    nfBrief,    /**< ?, !!, and so on. In case brief description is absent
                     nfDetailed is used. */
    nfDetailed  /**< Detailed description for given NAG. */
} NAG_format_t;

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

} /* namespace pgn */

#endif /* #ifndef PGN_MOVE_HPP */

