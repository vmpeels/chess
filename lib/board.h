#ifndef BOARD_H
#define BOARD_H

#include "board_coordinates.h"
#include "move.h"
#include "piece.h"
#include "piece_manager.h"
#include <vector>

namespace chess {

class Board {
private:
  // Check if ij is inb, errors if not.
  void ErrorIfOob(ij ij) const;

  // Creates a string representation of the board based on the given board
  // orientation.
  std::string ViewBoard(const Board &board, BoardOrientation orientation) const;

  // Underlying data structure representing the board.
  std::vector<std::vector<Piece>> board_;

  // Orientation of the board.
  BoardOrientation orientation_;

  // Used to store locations of each piece by id. Key is the piece id, value is
  // the location.
  PieceManager piece_locations_;

  struct en_passant {
    bool moved_en_passant_last_turn = false;
    Piece pawn;
    ij location{-1, -1};
    en_passant()
        : moved_en_passant_last_turn(false), pawn(Piece()), location({-1, -1}) {
    }
  };

  en_passant black_en_passant_;
  en_passant white_en_passant_;

public:
  struct Undo {
    Piece moved_piece;
    ij original_piece_location{-1, -1};
    ij new_piece_location{-1, -1};
    Piece piece_at_new_location;
    bool captured_en_passant = false;
    ij captured_en_passant_pawn_location{-1, -1};
  };
  Board();

  // Places a piece on the board at the given filerank, errors out if a piece
  // is already there.
  void PlacePiece(Piece p, ij ij);

  // Moves a piece to a new location. Takes the piece at the new_location if
  // there is a piece of opposite color there (and it's not the king.)
  Undo MakeMove(Piece piece, ij cur_location, move move);

  // Undoes a move.
  void UndoMove(Undo undo);

  // Gets piece at ij ij.
  Piece GetPiece(ij ij) const;

  // Flips the board orientation.
  void flip();

  // Adds the default position of the chess board.
  void ArrangePieces();

  // bool MovedEnPassantLastTurn(Piece adjacent_piece,
  //                             PieceColor adjacent_piece_color) const;

  bool CanCaptureEnPassant(ij adjacent_square, Piece pawn) const;

  friend std::ostream &operator<<(std::ostream &os, const Board &board);
};

std::ostream &operator<<(std::ostream &os, const Board &board);

} // namespace chess

#endif