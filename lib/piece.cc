#include "piece.h"
#include "ij.h"
#include <cassert>
#include <iostream>
#include <sstream>

namespace chess {

Piece::Piece() {
  type_ = PieceType::EMPTY;
  color_ = PieceColor::UNKNOWN;
  symbol_ = SYMBOL_EMPTY;
  name_ = NAME_EMPTY;
}

Piece::Piece(PieceType type, PieceColor color, ij location)
    : type_(type), color_(color) {
  switch (type) {
  case PieceType::PAWN:
    symbol_ = SYMBOL_PAWN;
    name_ = NAME_PAWN;
    break;
  case PieceType::KNIGHT:
    symbol_ = SYMBOL_KNIGHT;
    name_ = NAME_KNIGHT;
    break;
  case PieceType::BISHOP:
    symbol_ = SYMBOL_BISHOP;
    name_ = NAME_BISHOP;
    break;
  case PieceType::ROOK:
    symbol_ = SYMBOL_ROOK;
    name_ = NAME_ROOK;
    break;
  case PieceType::QUEEN:
    symbol_ = SYMBOL_QUEEN;
    name_ = NAME_QUEEN;
    break;
  case PieceType::KING:
    symbol_ = SYMBOL_KING;
    name_ = NAME_KING;
    break;
  case PieceType::EMPTY:
    symbol_ = SYMBOL_EMPTY;
    name_ = NAME_EMPTY;
  default:
    std::cout << "Error! Trying to construct piece with unknown value."
              << std::endl;
    assert(false);
    break;
  }
  id_ = shortstr() + ToFr(location);
}

std::string Piece::str() const {
  std::stringstream ss;
  ss << "{" << symbol() << ", " << name() << "," << color() << "}";
  return ss.str();
}

std::string Piece::shortstr() const {
  std::stringstream ss;
  char color = (color_ == PieceColor::UNKNOWN
                    ? '_'
                    : (color_ == PieceColor::BLACK ? 'b' : 'w'));
  ss << symbol() << color;
  return ss.str();
}

std::string Piece::id() const { return id_; }

std::ostream &operator<<(std::ostream &os, Piece piece) {
  os << piece.str();
  return os;
}

char Piece::symbol() const { return symbol_; }

std::string Piece::name() const { return name_; }

PieceColor Piece::color() const { return color_; }

PieceType Piece::type() const { return type_; }

bool Piece::empty() const { return type_ == PieceType::EMPTY; }

bool operator==(const Piece &l, const Piece &r) { return l.type_ == r.type_; }

bool operator!=(const Piece &l, const Piece &r) { return !(l == r); }

} // namespace chess