#include "bishop_move_generator.h"

namespace chess {

std::vector<ij> BishopMoveGenerator::GetPossibleMoves(const Board &board,
                                                      const Piece piece,
                                                      const ij piece_location) {
  std::vector<ij> possible_moves;

  std::vector<ij> to_top_left = ExtendUsingDelta(
      board, piece.color(), piece_location, {.i = -1, .j = -1});
  possible_moves.insert(possible_moves.end(), to_top_left.begin(),
                        to_top_left.end());
  std::vector<ij> to_top_right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 1});
  possible_moves.insert(possible_moves.end(), to_top_right.begin(),
                        to_top_right.end());
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

std::vector<ij>
BishopMoveGenerator::GetAttackingSquares(const Board &board, const Piece piece,
                                         const ij piece_location) {
  return GetPossibleMoves(board, piece, piece_location);
}

} // namespace chess