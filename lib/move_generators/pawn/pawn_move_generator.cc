#include "pawn_move_generator.h"
#include "lib/board.h"
#include "lib/ij.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator.h"
#include "lib/piece.h"

namespace chess {
namespace {

// Assumes attacking_square is inb.
bool CanCaptureEnPassant(const Board &board, const Piece pawn, ij pawn_location,
                         move attacking_square) {
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
      pawn_location +
          delta{.i = 0, .j = attacking_square.loc.j - pawn_location.j},
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
std::vector<move> PawnMoveGenerator::GetPossibleMoves(const Board &board,
                                                      const Piece piece,
                                                      const ij piece_location) {
  // TODO(vmpeels): Put assertion that pawn cannot be at the at first rank or
  // the eight rank.
  std::vector<move> possible_moves;

  int multiplier = piece.color() == PieceColor::WHITE ? -1 : 1;
  ij one_square_forward = piece_location + delta{.i = 1 * multiplier, .j = 0};
  possible_moves.push_back({.loc = one_square_forward, .capture = false});

  // En passant.
  ij two_squares_forward = piece_location + delta{.i = 2 * multiplier, .j = 0};
  if (PawnOnStartingRank(piece, piece_location)) {
    possible_moves.push_back({.loc = two_squares_forward, .capture = false});
  }

  // TODO(vmpeels): We are manually setting capture = true here. Determine if
  // this is actually good.
  // Add piece if you can capture them.
  std::vector<move> attacking_squares =
      GetAttackingSquares(board, piece, piece_location);
  for (move attacking_square : attacking_squares) {
    if (board.GetPiece(attacking_square.loc).color() == ~piece.color()) {
      possible_moves.push_back(attacking_square);
    } else if (CanCaptureEnPassant(board, piece, piece_location,
                                   attacking_square)) {
      // We have to manually set the capture field to true here since the
      // location on the board will be empty.
      possible_moves.push_back({.loc = attacking_square.loc, .capture = true});
    }
  }
  return possible_moves;
}

std::vector<move>
PawnMoveGenerator::GetAttackingSquares(const Board &board, const Piece piece,
                                       const ij piece_location) {
  std::vector<move> attacking_squares;
  int multiplier = piece.color() == PieceColor::WHITE ? -1 : 1;
  ij to_left = piece_location + delta{.i = 1 * multiplier, .j = -1};
  ij to_right = piece_location + delta{.i = 1 * multiplier, .j = 1};
  if (inb(to_left)) {
    attacking_squares.push_back(
        {.loc = to_left, .capture = !board.GetPiece(to_left).empty()});
  }
  if (inb(to_right)) {
    attacking_squares.push_back(
        {.loc = to_right, .capture = !board.GetPiece(to_right).empty()});
  }
  return attacking_squares;
}
} // namespace chess