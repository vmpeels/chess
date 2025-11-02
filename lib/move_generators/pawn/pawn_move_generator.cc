#include "pawn_move_generator.h"
#include "lib/board.h"
#include "lib/ij.h"
#include "lib/piece.h"

namespace chess {
namespace {
// std::vector<ij> GetEnPassantCaptures(const Board &board, const Piece piece,
//                                      const ij piece_location) {
//   std::vector<ij> en_passant_captures;
//   if (piece.color() == PieceColor::WHITE) {
//     if (piece_location.i == FIFTH_RANK) {
//       // left adjacent and right adjacent
//       ij left = piece_location + delta{.i = 0, .j = -1};
//       if (inb(left)) {
//         Piece adjacent_piece = board.GetPiece(left);
//         if (board.MovedEnPassantLastTurn(adjacent_piece, PieceColor::BLACK))
//         {
//           en_passant_captures.push_back(left);
//         }
//       }
//       ij right = piece_location + delta{.i = 0, .j = 1};
//       if (inb(right)) {
//         Piece adjacent_piece = board.GetPiece(right);
//         if (board.MovedEnPassantLastTurn(adjacent_piece, PieceColor::BLACK))
//         {
//           en_passant_captures.push_back(right);
//         }
//       }
//     }
//   } else if (piece.color() == PieceColor::BLACK) {
//     if (piece_location.i == FOURTH_RANK) {
//       // left adjacent and right adjacent
//       ij left = piece_location + delta{.i = 0, .j = -1};
//       if (inb(left)) {
//         Piece adjacent_piece = board.GetPiece(left);
//         if (board.MovedEnPassantLastTurn(adjacent_piece, PieceColor::WHITE))
//         {
//           en_passant_captures.push_back(left);
//         }
//       }
//       ij right = piece_location + delta{.i = 0, .j = 1};
//       if (inb(right)) {
//         Piece adjacent_piece = board.GetPiece(right);
//         if (board.MovedEnPassantLastTurn(adjacent_piece, PieceColor::WHITE))
//         {
//           en_passant_captures.push_back(right);
//         }
//       }
//     }
//   }
//   return en_passant_captures;
// }

// Assumes attacking_square is inb.
bool CanCaptureEnPassant(const Board &board, const Piece pawn, ij pawn_location,
                         ij attacking_square) {
  if (pawn.color() == PieceColor::UNKNOWN) {
    std::cout << "pawn has no color? here is the color: " << pawn.color()
              << std::endl;
    assert(false);
  }
  if (pawn.color() == PieceColor::WHITE && pawn_location.i != FIFTH_RANK_I) {
    return false;
  }

  if (pawn.color() == PieceColor::BLACK && pawn_location.i != FOURTH_RANK_I) {
    return false;
  }

  // You can capture en passant if there's a pawn horizontally adjacent to the
  // pawn.
  return board.CanCaptureEnPassant(
      pawn_location + delta{.i = 0, .j = attacking_square.j - pawn_location.j},
      pawn);
}

bool PawnOnStartingRank(const Piece piece, const ij piece_location) {
  if (piece.color() == PieceColor::WHITE) {
    return piece_location.i == SECOND_RANK_I;
  } else {
    return piece_location.i == SEVENTH_RANK_I;
  }
}

} // namespace
std::vector<ij> PawnMoveGenerator::GetPossibleMoves(const Board &board,
                                                    const Piece piece,
                                                    const ij piece_location) {
  // TODO(ryanm): Put assertion that pawn cannot be at the at first rank or the
  // eight rank.
  std::vector<ij> possible_moves;

  // TODO(vmpeels): There is a way to write this generically (if white,
  // multiplier = -1, else multiplier = 1).
  int multiplier = piece.color() == PieceColor::WHITE ? -1 : 1;
  ij one_square_forward = piece_location + delta{.i = 1 * multiplier, .j = 0};
  possible_moves.push_back(one_square_forward);

  // En passant.
  ij two_squares_forward = piece_location + delta{.i = 2 * multiplier, .j = 0};
  if (PawnOnStartingRank(piece, piece_location)) {
    possible_moves.push_back(two_squares_forward);
  }

  // Add piece if you can capture them.
  std::vector<ij> attacking_squares =
      GetAttackingSquares(board, piece, piece_location);
  for (ij attacking_square : attacking_squares) {
    if (board.GetPiece(attacking_square).color() == ~piece.color()) {
      possible_moves.push_back(attacking_square);
    } else if (CanCaptureEnPassant(board, piece, piece_location,
                                   attacking_square)) {
      possible_moves.push_back(attacking_square);
    }
  }
  return possible_moves;
}

std::vector<ij>
PawnMoveGenerator::GetAttackingSquares(const Board &board, const Piece piece,
                                       const ij piece_location) {
  std::vector<ij> attacking_squares;
  int multiplier = piece.color() == PieceColor::WHITE ? -1 : 1;
  ij to_left = piece_location + delta{.i = 1 * multiplier, .j = -1};
  ij to_right = piece_location + delta{.i = 1 * multiplier, .j = 1};
  if (inb(to_left)) {
    attacking_squares.push_back(to_left);
  }
  if (inb(to_right)) {
    attacking_squares.push_back(to_right);
  }
  return attacking_squares;
}
} // namespace chess