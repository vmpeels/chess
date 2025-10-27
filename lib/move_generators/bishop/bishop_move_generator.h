#ifndef BISHOP_MOVE_GENERATOR_H
#define BISHOP_MOVE_GENERATOR_H

#include "lib/board.h"
#include "lib/ij.h"
#include "lib/move_generators/move_generator.h"
#include "lib/piece.h"
#include <vector>

namespace chess {

class BishopMoveGenerator : public MoveGenerator {
public:
  std::vector<ij> GetPossibleMoves(const Board &board, const Piece piece,
                                   const ij piece_location) override;
  std::vector<ij> GetAttackingSquares(const Board &board, const Piece piece,
                                      const ij piece_location) override;
};

} // namespace chess

#endif