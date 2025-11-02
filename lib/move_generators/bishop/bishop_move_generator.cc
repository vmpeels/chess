#include "bishop_move_generator.h"
#include "lib/board.h"
#include "lib/ij.h"
#include "lib/move.h"
#include "lib/piece.h"
#include <vector>

namespace chess {

std::vector<move>
BishopMoveGenerator::GetPossibleMoves(const Board &board, const Piece piece,
                                      const ij piece_location) {
  std::vector<move> possible_moves;

  std::vector<move> to_top_left = ExtendUsingDelta(
      board, piece.color(), piece_location, {.i = -1, .j = -1});
  possible_moves.insert(possible_moves.end(), to_top_left.begin(),
                        to_top_left.end());
  std::vector<move> to_top_right =
      ExtendUsingDelta(board, piece.color(), piece_location, {.i = -1, .j = 1});
  possible_moves.insert(possible_moves.end(), to_top_right.begin(),
                        to_top_right.end());
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

std::vector<move>
BishopMoveGenerator::GetAttackingSquares(const Board &board, const Piece piece,
                                         const ij piece_location) {
  return GetPossibleMoves(board, piece, piece_location);
}

} // namespace chess