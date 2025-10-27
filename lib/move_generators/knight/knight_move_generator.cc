#include "knight_move_generator.h"

namespace chess {

std::vector<ij> KnightMoveGenerator::GetPossibleMoves(const Board &board,
                                                      const Piece piece,
                                                      const ij piece_location) {
  std::vector<ij> possible_moves;
  std::vector<delta> deltas = {
      {.i = -1, .j = -2}, {.i = -2, .j = -1}, {.i = -2, .j = 1},
      {.i = -1, .j = 2},  {.i = 1, .j = -2},  {.i = 2, .j = -1},
      {.i = 2, .j = 1},   {.i = 1, .j = 2},
  };

  for (auto d : deltas) {
    ij possible_move = piece_location + d;
    if (!inb(possible_move)) {
      continue;
    }
    Piece piece_at_loc = board.GetPiece(possible_move);
    if (piece_at_loc.empty()) {
      possible_moves.push_back(possible_move);
    } else if (piece.color() != piece_at_loc.color()) {
      possible_moves.push_back(possible_move);
    }
  }

  return possible_moves;
}
} // namespace chess