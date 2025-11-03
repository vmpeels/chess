#ifndef MOVE_MANAGER_H
#define MOVE_MANAGER_H

#include "board.h"
#include "ij.h"
#include "move.h"
#include "piece.h"
#include <vector>

namespace chess {

class MoveManager {
public:
  std::vector<move> GetLegalMoves(Board &board, Piece piece, ij location);
  bool KingInCheck(Board &board, PieceColor king_color);
};
} // namespace chess
#endif