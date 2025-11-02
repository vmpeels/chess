#include "queen_move_generator.h"

#include "lib/board.h"
#include "lib/ij.h"
#include "lib/move.h"
#include "lib/piece.h"
#include <vector>

namespace chess {

std::vector<move>
QueenMoveGenerator::GetPossibleMoves(const Board &board, const Piece piece,
                                     const ij piece_location) {
  std::vector<move> possible_moves;

  // Verticals.
  std::vector<move> up =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 0});
  possible_moves.insert(possible_moves.end(), up.begin(), up.end());

  std::vector<move> down =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = 0});
  possible_moves.insert(possible_moves.end(), down.begin(), down.end());

  // Horizontals.
  std::vector<move> left =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = -1});
  possible_moves.insert(possible_moves.end(), left.begin(), left.end());

  std::vector<move> right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = 1});
  possible_moves.insert(possible_moves.end(), right.begin(), right.end());

  // Diagonals up.
  std::vector<move> to_top_left = ExtendUsingDelta(
      board, piece.color(), piece_location, {.i = -1, .j = -1});
  possible_moves.insert(possible_moves.end(), to_top_left.begin(),
                        to_top_left.end());
  std::vector<move> to_top_right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 1});
  possible_moves.insert(possible_moves.end(), to_top_right.begin(),
                        to_top_right.end());

  // Diagonals down.
  std::vector<move> to_bot_left =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = -1});
  possible_moves.insert(possible_moves.end(), to_bot_left.begin(),
                        to_bot_left.end());
  std::vector<move> to_bot_right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = 1});
  possible_moves.insert(possible_moves.end(), to_bot_right.begin(),
                        to_bot_right.end());

  return possible_moves;
}

} // namespace chess