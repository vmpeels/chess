#include "move_generator.h"
#include <cassert>

namespace chess {

std::vector<ij> MoveGenerator::ExtendUsingDelta(const Board &board,
                                                PieceColor piece_color,
                                                ij piece_location,
                                                delta delta) {
  // Go until we reach the end of the board or until we hit a piece. Pieces with
  // opposite color are added to the moves;
  std::vector<ij> moves;
  ij cur_pos = ij(piece_location) + delta;
  bool hit_piece = false;
  while (inb(cur_pos) && !hit_piece) {
    Piece piece = board.GetPiece(cur_pos);
    hit_piece = !piece.empty();
    if (piece.empty()) {
      moves.push_back(cur_pos);
    } else if (piece.color() != piece_color &&
               piece.type() != PieceType::KING) {
      moves.push_back(cur_pos);
    }
    cur_pos = cur_pos + delta;
  }
  return moves;
}

std::vector<ij> MoveGenerator::GetAttackingSquares(const Board &board,
                                                   Piece piece,
                                                   ij piece_location) {
  return GetPossibleMoves(board, piece, piece_location);
}

} // namespace chess