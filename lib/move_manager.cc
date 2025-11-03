#include "move_manager.h"
#include "ij.h"
#include "move.h"
#include "move_generators/move_generator_dispatch.h"
#include <memory>
#include <vector>

namespace chess {

std::vector<move> MoveManager::GetLegalMoves(Board &board, Piece piece,
                                             ij location) {
  std::vector<move> possible_moves =
      GetMoveGenerator(piece.type())->GetPossibleMoves(board, piece, location);

  // For each move, check if making the move would put your king in check.
  std::vector<move> legal_moves;
  for (const move move : possible_moves) {
    Board::Undo undo = board.MakeMove(piece, location, move);
    if (!KingInCheck(board, piece.color())) {
      legal_moves.push_back(move);
    }
    board.UndoMove(undo);
  }

  return legal_moves;
}

bool MoveManager::KingInCheck(Board &board, PieceColor king_color) {
  ij king_location = board.GetKingLocation(king_color);
  std::vector<ij> opposite_color_piece_locations =
      board.GetPieceLocations(~king_color);
  for (ij opposite_color_piece_location : opposite_color_piece_locations) {
    Piece piece = board.GetPiece(opposite_color_piece_location);
    std::vector<move> attacking_squares =
        GetMoveGenerator(piece.type())
            ->GetAttackingSquares(board, piece, opposite_color_piece_location);
    for (move attacking_square : attacking_squares) {
      if (attacking_square.loc == king_location) {
        return true;
      }
    }
  }
  return false;
}
} // namespace chess