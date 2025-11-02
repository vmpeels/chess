#include "rook_move_generator.h"
#include "lib/board.h"
#include "lib/ij.h"
#include "lib/move.h"
#include "lib/piece.h"
#include <vector>

namespace chess {

std::vector<move> RookMoveGenerator::GetPossibleMoves(const Board &board,
                                                      const Piece piece,
                                                      const ij piece_location) {
  std::vector<move> possible_moves;

  std::vector<move> up =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 0});
  possible_moves.insert(possible_moves.end(), up.begin(), up.end());

  std::vector<move> down =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = 0});
  possible_moves.insert(possible_moves.end(), down.begin(), down.end());

  std::vector<move> left =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = -1});
  possible_moves.insert(possible_moves.end(), left.begin(), left.end());

  std::vector<move> right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = 1});
  possible_moves.insert(possible_moves.end(), right.begin(), right.end());
  return possible_moves;
}

} // namespace chess