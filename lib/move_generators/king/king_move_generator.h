#ifndef KING_MOVE_GENERATOR_H
#define KING_MOVE_GENERATOR_H
#include "lib/board.h"
#include "lib/ij.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator.h"
#include "lib/piece.h"
#include <vector>

namespace chess {

class KingMoveGenerator : public MoveGenerator {
public:
  std::vector<move> GetPossibleMoves(const Board &board, const Piece piece,
                                     const ij piece_location) override;
};

} // namespace chess
#endif