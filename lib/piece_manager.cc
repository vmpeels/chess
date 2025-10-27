#include "piece_manager.h"
#include "piece.h"
#include <cassert>
#include <iostream>

namespace chess {

void PieceManager::ChangePieceLocation(Piece piece, ij cur_location,
                                       ij new_location) {
  switch (piece.color()) {
  case PieceColor::BLACK: {
    assert(black_pieces_.contains(piece.id()));
    assert(black_pieces_[piece.id()] == cur_location);
    black_pieces_[piece.id()] = new_location;
    break;
  }
  case PieceColor::WHITE: {
    assert(white_pieces_.contains(piece.id()));
    assert(white_pieces_[piece.id()] == cur_location);
    white_pieces_[piece.id()] = new_location;
    break;
  }
  default:
    std::cout << "Handling unknown piece: " << piece << std::endl;
    assert(false);
  }
}

void PieceManager::RemovePiece(Piece piece, ij location) {
  switch (piece.color()) {
  case PieceColor::BLACK: {
    assert(black_pieces_[piece.id()] == location);
    black_pieces_.erase(piece.id());
    break;
  }
  case PieceColor::WHITE: {
    assert(white_pieces_[piece.id()] == location);
    white_pieces_.erase(piece.id());
    break;
  }
  default:
    std::cout << "Handling unknown piece: " << piece << std::endl;
    assert(false);
  }
}

void PieceManager::AddPiece(Piece p, ij location) {
  if (black_pieces_.contains(p.id())) {
    std::cout << "adding piece already added: " << p << std::endl;
    assert(false);
  }
  if (white_pieces_.contains(p.id())) {
    std::cout << "adding piece already added: " << p << std::endl;
    assert(false);
  }
  switch (p.color()) {
  case PieceColor::BLACK: {
    black_pieces_[p.id()] = location;
    break;
  }
  case PieceColor::WHITE: {
    white_pieces_[p.id()] = location;
    break;
  }
  default:
    std::cout << "adding piece with unknown piece color" << std::endl;
    assert(false);
  }
}

} // namespace chess