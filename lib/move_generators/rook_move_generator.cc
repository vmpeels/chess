#include "rook_move_generator.h"

namespace chess {

std::vector<ij> RookMoveGenerator::GetPossibleMoves(const Board &board,
                                                    const Piece piece,
                                                    const ij piece_location) {
  std::vector<ij> possible_moves;

  std::vector<ij> up =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 0});
  possible_moves.insert(possible_moves.end(), up.begin(), up.end());

  std::vector<ij> down =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 1, .j = 0});
  possible_moves.insert(possible_moves.end(), down.begin(), down.end());

  std::vector<ij> left =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = -1});
  possible_moves.insert(possible_moves.end(), left.begin(), left.end());

  std::vector<ij> right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = 0, .j = 1});
  possible_moves.insert(possible_moves.end(), right.begin(), right.end());
  return possible_moves;
}

} // namespace chess