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
  if (pawn.color() == PieceColor::WHITE) {
    if (pawn_location.i != FIFTH_RANK_I) {
      return false;
    }

    // The attacking_square is diagonally up from the pawn location, so the
    // square adjacent to the pawn moves down one square.
    ij adjacent_square = attacking_square + delta{.i = 1, .j = 0};
    return board.CanCaptureEnPassant(adjacent_square, pawn);
  } else {
    if (pawn_location.i != FOURTH_RANK_I) {
      return false;
    }

    // The attacking_square is diagonally down from the pawn location, so the
    // square adjacent to the pawn moves up one square.
    ij adjacent_square = attacking_square + delta{.i = -1, .j = 0};
    return board.CanCaptureEnPassant(adjacent_square, pawn);
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
  if (piece.color() == PieceColor::WHITE) {
    ij up = piece_location + delta{.i = -1, .j = 0};
    possible_moves.push_back(up);

    // En passant.
    if (piece_location.i == SECOND_RANK_I) {
      possible_moves.push_back(piece_location + delta{.i = -2, .j = 0});
    }

    std::vector<ij> attacking_squares =
        GetAttackingSquares(board, piece, piece_location);
    for (ij square : attacking_squares) {
      if (board.GetPiece(square).color() == PieceColor::BLACK) {
        possible_moves.push_back(square);
      } else if (CanCaptureEnPassant(board, piece, piece_location, square)) {
        possible_moves.push_back(square);
      }
    }
  } else {
    ij down = piece_location + delta{.i = 1, .j = 0};
    possible_moves.push_back(down);

    // En passant.
    if (piece_location.i == SEVENTH_RANK_I) {
      possible_moves.push_back(piece_location + delta{.i = 2, .j = 0});
    }

    std::vector<ij> attacking_squares =
        GetAttackingSquares(board, piece, piece_location);
    for (ij square : attacking_squares) {
      if (board.GetPiece(square).color() == PieceColor::WHITE) {
        possible_moves.push_back(square);
      } else if (CanCaptureEnPassant(board, piece, piece_location, square)) {
        possible_moves.push_back(square);
      }
    }
  }
  return possible_moves;
}

std::vector<ij>
PawnMoveGenerator::GetAttackingSquares(const Board &board, const Piece piece,
                                       const ij piece_location) {
  std::vector<ij> attacking_squares;
  if (piece.color() == PieceColor::WHITE) {
    ij up_to_left = piece_location + delta{.i = -1, .j = -1};
    if (inb(up_to_left)) {
      attacking_squares.push_back(up_to_left);
    }

    ij up_to_right = piece_location + delta{.i = -1, .j = 1};
    if (inb(up_to_right)) {
      attacking_squares.push_back(up_to_right);
    }
  } else if (piece.color() == PieceColor::BLACK) {
    ij down_to_left = piece_location + delta{.i = 1, .j = -1};
    if (inb(down_to_left)) {
      attacking_squares.push_back(down_to_left);
    }

    ij down_to_right = piece_location + delta{.i = 1, .j = 1};
    if (inb(down_to_right)) {
      attacking_squares.push_back(down_to_right);
    }
  }
  return attacking_squares;
}
} // namespace chess