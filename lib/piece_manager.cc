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
    if (p.type() == PieceType::KING) {
      black_king_id_ = p.id();
    }
    black_pieces_[p.id()] = location;
    break;
  }
  case PieceColor::WHITE: {
    if (p.type() == PieceType::KING) {
      white_king_id_ = p.id();
    }
    white_pieces_[p.id()] = location;
    break;
  }
  default:
    std::cout << "adding piece with unknown piece color" << std::endl;
    assert(false);
  }
}

ij PieceManager::GetKingLocation(PieceColor color) {
  if (PieceColor::BLACK == color) {
    return black_pieces_[black_king_id_];
  }
  return white_pieces_[white_king_id_];
}

std::vector<ij> PieceManager::GetPieceLocations(PieceColor color) {
  std::vector<ij> locations;
  if (color == PieceColor::BLACK) {
    for (auto black_piece : black_pieces_) {
      locations.push_back(black_piece.second);
    }
  } else if (color == PieceColor::WHITE) {
    for (auto white_piece : white_pieces_) {
      locations.push_back(white_piece.second);
    }
  }
  return locations;
}

} // namespace chess