#ifndef PAWN_MOVE_GENERATOR_H
#define PAWN_MOVE_GENERATOR_H

#include "lib/board.h"
#include "lib/ij.h"
#include "lib/piece.h"
#include "move_generator.h"

namespace chess {

class PawnMoveGenerator : public MoveGenerator {
public:
  std::vector<ij> GetPossibleMoves(const Board &board, const Piece piece,
                                   const ij piece_location) override;
  std::vector<ij> GetAttackingSquares(const Board &board, const Piece piece,
                                      const ij piece_location) override;
};
} // namespace chess
#endif