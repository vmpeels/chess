#include "king_move_generator.h"
#include "lib/board.h"
#include "lib/ij.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator.h"
#include "lib/piece.h"
#include <vector>

namespace chess {

std::vector<move> KingMoveGenerator::GetPossibleMoves(const Board &board,
                                                      const Piece piece,
                                                      const ij piece_location) {
  std::vector<move> possible_moves;
  std::vector<delta> deltas = {{.i = -1, .j = -1}, {.i = -1, .j = 0},
                               {.i = -1, .j = 1},  {.i = 0, .j = -1},
                               {.i = 0, .j = 1},   {.i = 1, .j = -1},
                               {.i = 1, .j = 0},   {.i = 1, .j = 1}};

  for (auto d : deltas) {
    ij possible_move = piece_location + d;
    if (!inb(possible_move)) {
      continue;
    }

    // TODO(vmpeels): Do I need to check if the captured piece is a king?
    Piece piece_at_loc = board.GetPiece(possible_move);
    if (piece_at_loc.empty()) {
      possible_moves.push_back({.loc = possible_move, .capture = false});
    } else if (piece.color() != piece_at_loc.color()) {
      possible_moves.push_back({.loc = possible_move, .capture = true});
    }
  }

  return possible_moves;
}

} // namespace chess