#include "constants.h"
#include <cassert>

namespace chess {

std::ostream &operator<<(std::ostream &os, PieceColor color) {
  switch (color) {
  case PieceColor::BLACK:
    os << "BLACK";
    break;
  case PieceColor::WHITE:
    os << "WHITE";
    break;
  case PieceColor::UNKNOWN:
    os << "UNKNOWN";
  }
  return os;
}

PieceColor operator~(PieceColor color) {
  switch (color) {
  case PieceColor::BLACK:
    return PieceColor::WHITE;
  case PieceColor::WHITE:
    return PieceColor::BLACK;
  case PieceColor::UNKNOWN:
    assert(false);
  }
}

std::ostream &operator<<(std::ostream &os, BoardOrientation orientation) {
  switch (orientation) {
  case BoardOrientation::WHITE:
    os << "WHITE";
    break;
  case BoardOrientation::BLACK:
    os << "BLACK";
    break;
  default:
    os << "UNKNOWN";
    break;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, PieceType piece_type) {
  switch (piece_type) {
  case PieceType::BISHOP:
    os << "bishop";
    return os;
  case PieceType::KING:
    os << "king";
    return os;
  case PieceType::KNIGHT:
    os << "knight";
    return os;
  case PieceType::QUEEN:
    os << "queen";
    return os;
  case PieceType::ROOK:
    os << "rook";
    return os;
  case PieceType::EMPTY:
    os << "empty";
    return os;
  case PieceType::UNKNOWN:
    os << "unknown";
    return os;
  default:
    assert(false);
  }
  return os;
}

} // namespace chess