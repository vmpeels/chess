#include "board.h"
#include "ij.h"
#include <cassert>
#include <sstream>

namespace chess {
namespace {
// // Assume cur_location and new_location are inb.
// bool MovedEnPassant(Piece piece, ij cur_location, ij new_location) {
//   if (piece.type() != PieceType::PAWN) {
//     return false;
//   }
//   if (piece.color() == PieceColor::UNKNOWN) {
//     std::cout << "Unknown piece color" << std::endl;
//     assert(false);
//   }

//   if (piece.color() == PieceColor::WHITE) {
//     return cur_location.i == SECOND_RANK_I && new_location.i ==
//     FOURTH_RANK_I;
//   } else {
//     return cur_location.i == SEVENTH_RANK_I && new_location.i ==
//     FIFTH_RANK_I;
//   }
// }

bool MaybeCapturedEnPassant(Piece piece, ij cur_location, ij new_location,
                            Piece piece_at_new_location) {
  if (piece.type() != PieceType::PAWN) {
    return false;
  }
  if (piece.color() == PieceColor::UNKNOWN) {
    std::cout << "Unknown piece color" << std::endl;
    assert(false);
  }

  // Capturing en passant means we're capturing an empty square.
  if (!piece_at_new_location.empty()) {
    return false;
  }

  if (piece.color() == PieceColor::WHITE) {
    // we must have taken, so check that new location is diagonal from
    // cur_location.
    ij up_to_left = cur_location + ij{.i = -1, .j = -1};
    ij up_to_right = cur_location + ij{.i = -1, .j = 1};
    return new_location == up_to_left || new_location != up_to_right;
  } else {
    // we must have taken, so check that new location is diagonal from
    // cur_location.
    ij down_to_left = cur_location + ij{.i = 1, .j = -1};
    ij down_to_right = cur_location + ij{.i = 1, .j = 1};
    return new_location == down_to_left || new_location != down_to_right;
  }
  return false;
}
} // namespace

void Board::ErrorIfOob(ij ij) const {
  if (!inb(ij)) {
    std::cout << "Out of bounds ij: " << ij << std::endl;
    assert(false);
  }
}

// bool Board::MovedEnPassantLastTurn(Piece adjacent_piece,
//                                    PieceColor adjacent_piece_color) const {
//   if (adjacent_piece.type() != PieceType::PAWN) {
//     return false;
//   }
//   if (adjacent_piece.color() != adjacent_piece_color) {
//     return false;
//   }
//   if (adjacent_piece_color == PieceColor::BLACK) {
//     return black_en_passant_.pawn.id() == adjacent_piece.id() &&
//            black_en_passant_.moved_en_passant_last_turn;
//   } else if (adjacent_piece_color == PieceColor::WHITE) {
//     return white_en_passant_.pawn.id() == adjacent_piece.id() &&
//            white_en_passant_.moved_en_passant_last_turn;
//   }
//   return false;
// }

bool Board::CanCaptureEnPassant(ij adjacent_square, Piece pawn) const {
  ErrorIfOob(adjacent_square);
  Piece adjacent_pawn;
  if ((adjacent_pawn = GetPiece(adjacent_square)).type() != PieceType::PAWN) {
    return false;
  }

  if (pawn.color() == adjacent_pawn.color()) {
    return false;
  }

  if (pawn.color() == PieceColor::WHITE) {
    return black_en_passant_.pawn.id() == adjacent_pawn.id() &&
           black_en_passant_.moved_en_passant_last_turn;
  } else if (pawn.color() == PieceColor::BLACK) {
    return white_en_passant_.pawn.id() == adjacent_pawn.id() &&
           white_en_passant_.moved_en_passant_last_turn;
  }
  return false;
}

Board::Undo Board::MakeMove(Piece piece, ij cur_location, move move) {
  ErrorIfOob(cur_location);
  ErrorIfOob(move.loc);
  // Reset en_passant every turn.
  white_en_passant_ = en_passant();
  black_en_passant_ = en_passant();

  Board::Undo undo;
  undo.moved_piece = piece;
  undo.original_piece_location = cur_location;
  undo.new_piece_location = move.loc;
  Piece piece_at_new_location = GetPiece(move.loc);

  // Handle capturing en passant
  if (move.en_passant_capture) {
    undo.captured_en_passant = true;
    ij captured_en_passant_pawn_location = {.i = cur_location.i,
                                            .j = (move.loc.j)};
    undo.captured_en_passant_pawn_location = captured_en_passant_pawn_location;
    // Move the capturing pawn
    board_[cur_location.i][cur_location.j] = Piece();
    board_[move.loc.i][move.loc.j] = piece;
    piece_locations_.ChangePieceLocation(piece, cur_location, move.loc);
    piece_locations_.RemovePiece(GetPiece(captured_en_passant_pawn_location),
                                 captured_en_passant_pawn_location);
    board_[captured_en_passant_pawn_location.i]
          [captured_en_passant_pawn_location.j] = Piece();
    return undo;
  }

  undo.piece_at_new_location = piece_at_new_location;

  if (!piece_at_new_location.empty()) {
    piece_locations_.RemovePiece(piece_at_new_location, move.loc);
  }
  board_[cur_location.i][cur_location.j] = Piece();
  board_[move.loc.i][move.loc.j] = piece;
  piece_locations_.ChangePieceLocation(piece, cur_location, move.loc);

  // TODO(vmpeels): maybe i need to do some checking for taking en passant.

  // Handle moving two squares with a pawn. Order matters when resetting and
  // then checking for en passant -- resetting should happen first.
  if (piece.type() == PieceType::PAWN) {
    if (piece.color() == PieceColor::WHITE) {
      if (cur_location.i == SECOND_RANK_I && move.loc.i == FOURTH_RANK_I) {
        white_en_passant_.moved_en_passant_last_turn = true;
        white_en_passant_.pawn = piece;
        white_en_passant_.location = move.loc;
      }
    } else if (piece.color() == PieceColor::BLACK) {
      if (cur_location.i == SEVENTH_RANK_I && move.loc.i == FIFTH_RANK_I) {
        black_en_passant_.moved_en_passant_last_turn = true;
        black_en_passant_.pawn = piece;
        black_en_passant_.location = move.loc;
      }
    }
  }
  return undo;
}

void Board::UndoMove(Board::Undo undo) {
  ErrorIfOob(undo.new_piece_location);
  ErrorIfOob(undo.original_piece_location);
  board_[undo.original_piece_location.i][undo.original_piece_location.j] =
      undo.moved_piece;
  piece_locations_.ChangePieceLocation(
      undo.moved_piece, undo.new_piece_location, undo.original_piece_location);

  board_[undo.new_piece_location.i][undo.new_piece_location.j] =
      undo.piece_at_new_location;
  if (!undo.piece_at_new_location.empty()) {
    piece_locations_.AddPiece(undo.piece_at_new_location,
                              undo.new_piece_location);
  }
}

void Board::ArrangePieces() {
  // Now arrange the pieces on the squares in the starting chess formation.
  // BoardOrientation is for white. We're going to use chess notation
  // to guarantee that the positioning on the board is correct.

  // White pawns go on the second rank across all files.
  std::vector<ij> white_pawn_ij = {A2, B2, C2, D2, E2, F2, G2, H2};
  for (const auto &wij : white_pawn_ij) {
    Piece pawn = Piece(PieceType::PAWN, PieceColor::WHITE, wij);
    // pawn_manager_.AddPawn(pawn, wij);
    PlacePiece(pawn, wij);
  }

  // White pieces are arranged manually
  PlacePiece(Piece(PieceType::ROOK, PieceColor::WHITE, A1), A1);
  PlacePiece(Piece(PieceType::KNIGHT, PieceColor::WHITE, B1), B1);
  PlacePiece(Piece(PieceType::BISHOP, PieceColor::WHITE, C1), C1);
  PlacePiece(Piece(PieceType::QUEEN, PieceColor::WHITE, D1), D1);
  PlacePiece(Piece(PieceType::KING, PieceColor::WHITE, E1), E1);
  PlacePiece(Piece(PieceType::BISHOP, PieceColor::WHITE, F1), F1);
  PlacePiece(Piece(PieceType::KNIGHT, PieceColor::WHITE, G1), G1);
  PlacePiece(Piece(PieceType::ROOK, PieceColor::WHITE, H1), H1);

  // Black pawns go on the 7th rank across all files.
  std::vector<ij> black_pawn_ij = {A7, B7, C7, D7, E7, F7, G7, H7};
  for (const auto &bij : black_pawn_ij) {
    Piece pawn = Piece(PieceType::PAWN, PieceColor::BLACK, bij);
    // pawn_manager_.AddPawn(pawn, bij);
    PlacePiece(pawn, bij);
  }

  // Black pieces are arranged manually
  PlacePiece(Piece(PieceType::ROOK, PieceColor::BLACK, A8), A8);
  PlacePiece(Piece(PieceType::KNIGHT, PieceColor::BLACK, B8), B8);
  PlacePiece(Piece(PieceType::BISHOP, PieceColor::BLACK, C8), C8);
  PlacePiece(Piece(PieceType::QUEEN, PieceColor::BLACK, D8), D8);
  PlacePiece(Piece(PieceType::KING, PieceColor::BLACK, E8), E8);
  PlacePiece(Piece(PieceType::BISHOP, PieceColor::BLACK, F8), F8);
  PlacePiece(Piece(PieceType::KNIGHT, PieceColor::BLACK, G8), G8);
  PlacePiece(Piece(PieceType::ROOK, PieceColor::BLACK, H8), H8);
}

Board::Board() : orientation_(BoardOrientation::WHITE) {
  // Initialize the board with all the black and the white pieces.

  // First, we fill in the board will all empty pieces.
  for (int i = 0; i < NUM_RANKS; ++i) {
    std::vector<Piece> row;
    for (int j = 0; j < NUM_FILES; ++j) {
      row.push_back(Piece());
    }
    board_.push_back(row);
  }
}

void Board::PlacePiece(Piece p, ij ij) {
  ErrorIfOob(ij);

  if (!GetPiece(ij).empty()) {
    std::cout << "Cannot place piece at ij " << ij
              << ". Piece already exists there." << std::endl;
  }
  board_[ij.i][ij.j] = p;
  piece_locations_.AddPiece(p, ij);
}

Piece Board::GetPiece(ij ij) const {
  if (!inb(ij)) {
    std::cout << "Out of bounds ij: " << ij << std::endl;
    assert(false);
  }
  // std::cout << "Getting piece at ij: " << ij << std::endl;
  return board_[ij.i][ij.j];
}

void Board::flip() {
  if (orientation_ == BoardOrientation::WHITE) {
    orientation_ = BoardOrientation::BLACK;
  } else {
    orientation_ = BoardOrientation::WHITE;
  }
}

std::string Board::ViewBoard(const Board &board,
                             BoardOrientation orientation) const {
  /*

  For white board orientation:
     a  b  c  d  e  f  g  h
  8 [_, _, _, _, _, _, _, _] 8
  7 [_, _, _, _, _, _, _, _] 7
  6 [_, _, _, _, _, _, _, _] 6
  5 [_, _, _, _, _, _, _, _] 5
  4 [_, _, _, _, _, _, _, _] 4
  3 [_, _, _, _, _, _, _, _] 3
  2 [_, _, _, _, _, _, _, _] 2
  1 [_, _, _, _, _, _, _, _] 1
     a  b  c  d  e  f  g  h

  Black board orientation
     h  g  f  e  d  c  b  a
  1 [_, _, _, _, _, _, _, _] 1
  2 [_, _, _, _, _, _, _, _] 2
  3 [_, _, _, _, _, _, _, _] 3
  4 [_, _, _, _, _, _, _, _] 4
  5 [_, _, _, _, _, _, _, _] 5
  6 [_, _, _, _, _, _, _, _] 6
  7 [_, _, _, _, _, _, _, _] 7
  8 [_, _, _, _, _, _, _, _] 8
     h  g  f  e  d  c  b  a
  */

  std::vector<std::vector<ij>> board_ij;
  std::vector<char> files;
  std::vector<char> ranks;
  if (orientation == BoardOrientation::WHITE) {
    board_ij = {
        {A8, B8, C8, D8, E8, F8, G8, H8}, {A7, B7, C7, D7, E7, F7, G7, H7},
        {A6, B6, C6, D6, E6, F6, G6, H6}, {A5, B5, C5, D5, E5, F5, G5, H5},
        {A4, B4, C4, D4, E4, F4, G4, H4}, {A3, B3, C3, D3, E3, F3, G3, H3},
        {A2, B2, C2, D2, E2, F2, G2, H2}, {A1, B1, C1, D1, E1, F1, G1, H1}};
    files = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    ranks = {'8', '7', '6', '5', '4', '3', '2', '1'};
  } else {
    board_ij = {
        {H1, G1, F1, E1, D1, C1, B1, A1}, {H2, G2, F2, E2, D2, C2, B2, A2},
        {H3, G3, F3, E3, D3, C3, B3, A3}, {H4, G4, F4, E4, D4, C4, B4, A4},
        {H5, G5, F5, E5, D5, C5, B5, A5}, {H6, G6, F6, E6, D6, C6, B6, A6},
        {H7, G7, F7, E7, D7, C7, B7, A7}, {H8, G8, F8, E8, D8, C8, B8, A8}};
    files = {'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    ranks = {'1', '2', '3', '4', '5', '6', '7', '8'};
  }

  // 1. Print out the files at the top of the board.

  // 3 spaces to align the files with the board. Explanation:
  // 1 space for char for rank + 1 space between rank and open bracket + 1
  // space for open bracket
  std::string prefix_space = "   ";
  std::string postfix_space = "   ";

  // // 2 spaces to align the files with the spots. Explanation:
  // // 1 space for comma after the spot, 1 space for the space between
  // comma
  // and next spot.
  std::string between_files_space = "  ";
  std::stringstream ss;

  // Print
  ss << prefix_space;
  std::string separator;
  for (char file : files) {
    ss << separator;
    ss << file;
    separator = between_files_space;
  }
  ss << postfix_space << '\n';

  // 2. Print out each rank, followed by the row of pieces. Each row
  // starts with a rank and open bracket and ends with a closing bracket.
  // The spots are comma separated within the rows.

  // Piece symbols will be separated by a comma and a space.
  std::string between_piece_separator = ", ";
  // Print
  for (int i = 0; i < NUM_RANKS; ++i) {
    separator = "";
    char rank = ranks[i];
    ss << rank << " [";
    for (int j = 0; j < NUM_RANKS; ++j) {
      ij board_coord = board_ij[i][j];
      Piece piece = board.GetPiece(board_coord);
      ss << separator << piece.symbol();
      separator = between_piece_separator;
    }
    ss << "] " << rank << '\n';
  }

  // 3. Print out the files at the bottom as the last line.

  // Print
  ss << prefix_space;
  separator = "";
  for (char file : files) {
    ss << separator;
    ss << file;
    separator = between_files_space;
  }
  ss << postfix_space << std::endl; // Use std::endl to force a flush.
  return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
  os << board.ViewBoard(board, board.orientation_);
  return os;
}
} // namespace chess