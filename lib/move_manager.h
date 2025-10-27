#ifndef MOVE_MANAGER_H
#define MOVE_MANAGER_H

#include "board.h"
#include "ij.h"
#include "piece.h"
#include <vector>

namespace chess {

class MoveManager {
public:
  bool KingInCheck();

  std::vector<ij> GetLegalMoves(Board &board, Piece piece, ij location);
};
} // namespace chess
#endif