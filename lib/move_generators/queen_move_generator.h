#ifndef QUEEN_MOVE_GENERATOR_H
#define QUEEN_MOVE_GENERATOR_H

#include "lib/board.h"
#include "lib/ij.h"
#include "lib/piece.h"
#include "move_generator.h"
#include <vector>

namespace chess {

class QueenMoveGenerator : public MoveGenerator {
public:
  std::vector<ij> GetPossibleMoves(const Board &board, const Piece piece,
                                   const ij piece_location) override;
};

} // namespace chess

#endif