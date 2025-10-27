#include "move_manager.h"
#include "ij.h"
#include "move_generators/bishop_move_generator.h"
#include "move_generators/king_move_generator.h"
#include "move_generators/knight_move_generator.h"
#include "move_generators/move_generator.h"
#include "move_generators/queen_move_generator.h"
#include "move_generators/rook_move_generator.h"
#include <memory>
#include <vector>

namespace chess {
namespace {
std::unique_ptr<MoveGenerator> GetMoveGenerator(PieceType piece_type) {
  switch (piece_type) {
  case PieceType::PAWN:
    std::cout << "pawn move generator unimplemented" << std::endl;
    assert(false);
    break;
  case PieceType::ROOK:
    return std::make_unique<RookMoveGenerator>();
  case PieceType::KNIGHT:
    return std::make_unique<KnightMoveGenerator>();
  case PieceType::BISHOP:
    return std::make_unique<BishopMoveGenerator>();
  case PieceType::QUEEN:
    return std::make_unique<QueenMoveGenerator>();
  case PieceType::KING:
    return std::make_unique<KingMoveGenerator>();
  default:
    std::cout << "got unhandleable piece type: " << piece_type << std::endl;
    assert(false);
  }
}
} // namespace

std::vector<ij> MoveManager::GetLegalMoves(Board &board, Piece piece,
                                           ij location) {
  std::vector<ij> possible_moves =
      GetMoveGenerator(piece.type())->GetPossibleMoves(board, piece, location);

  // For each move, check if making the move would put your king in check.
  std::vector<ij> legal_moves;
  for (const ij move : possible_moves) {
    Board::Undo undo = board.MakeMove(piece, location, move);
    if (!KingInCheck()) {
      legal_moves.push_back(move);
    }
    board.UndoMove(undo);
  }

  return legal_moves;
}

} // namespace chess