#ifndef PIECE_H
#define PIECE_H

#include "ij.h"
#include "lib/constants.h"
#include <string>

namespace chess {

class Piece {

private:
  char symbol_;
  std::string name_;
  PieceType type_;
  PieceColor color_;
  std::string id_;

public:
  Piece();

  Piece(PieceType type, PieceColor color, ij location);

  char symbol() const;

  std::string name() const;

  PieceColor color() const;

  PieceType type() const;

  std::string id() const;

  std::string shortstr() const;

  std::string str() const;

  bool empty() const;

  friend std::ostream &operator<<(std::ostream &os, Piece piece);
  friend bool operator==(const Piece &l, const Piece &r);
  friend bool operator!=(const Piece &l, const Piece &r);
};

std::ostream &operator<<(std::ostream &os, Piece piece);
bool operator==(const Piece &l, const Piece &r);
bool operator!=(const Piece &l, const Piece &r);

} // namespace chess

#endif