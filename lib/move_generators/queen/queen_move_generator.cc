#include "queen_move_generator.h"

namespace chess {

std::vector<ij> QueenMoveGenerator::GetPossibleMoves(const Board &board,
                                                     const Piece piece,
                                                     const ij piece_location) {
  std::vector<ij> possible_moves;

  // Verticals.
  std::vector<ij> up =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 0});
  possible_moves.insert(possible_moves.end(), up.begin(), up.end());

  std::vector<ij> down =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = 0});
  possible_moves.insert(possible_moves.end(), down.begin(), down.end());

  // Horizontals.
  std::vector<ij> left =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = -1});
  possible_moves.insert(possible_moves.end(), left.begin(), left.end());

  std::vector<ij> right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = 1});
  possible_moves.insert(possible_moves.end(), right.begin(), right.end());

  // Diagonals up.
  std::vector<ij> to_top_left = ExtendUsingDelta(
      board, piece.color(), piece_location, {.i = -1, .j = -1});
  possible_moves.insert(possible_moves.end(), to_top_left.begin(),
                        to_top_left.end());
  std::vector<ij> to_top_right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 1});
  possible_moves.insert(possible_moves.end(), to_top_right.begin(),
                        to_top_right.end());

  // Diagonals down.
  std::vector<ij> to_bot_left =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = -1});
  possible_moves.insert(possible_moves.end(), to_bot_left.begin(),
                        to_bot_left.end());
  std::vector<ij> to_bot_right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = 1});
  possible_moves.insert(possible_moves.end(), to_bot_right.begin(),
                        to_bot_right.end());

  return possible_moves;
}

} // namespace chess