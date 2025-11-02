#ifndef MOVE_GENERATOR_H
#define MOVE_GENERATOR_H

#include "lib/board.h"
#include "lib/ij.h"
#include "lib/piece.h"
#include <vector>

namespace chess {

using delta = ij;

class MoveGenerator {
public:
  // TODO(ryanm): I think that GetPossibleMoves should use GetAttackingSquares
  // instead of GetAttackingSquares using GetPossibleMoves.
  virtual std::vector<ij> GetPossibleMoves(const Board &board, Piece piece,
                                           ij piece_location) = 0;

  virtual std::vector<ij> GetAttackingSquares(const Board &board, Piece piece,
                                              ij piece_location);
  virtual ~MoveGenerator() = default;

protected:
  std::vector<ij> ExtendUsingDelta(const Board &board, PieceColor piece_color,
                                   ij piece_location, delta delta);
};

} // namespace chess

#endif