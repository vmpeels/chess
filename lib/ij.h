#ifndef BOARD_COORDINATES_H
#define BOARD_COORDINATES_H

#include <cassert>
#include <iostream>

namespace chess {

// TODO(vmpeels): What if we did some sort of thing with type aliasing for the
// ij struct? Like, something where we type alias the i to "rank" and "j" to
// file. Can we enforce comparisons that ranks can only be equal to other rank?
struct ij {
  int i = -1;
  int j = -1;

  friend bool operator==(const ij lhs, const ij rhs);
  friend bool operator!=(const ij lhs, const ij rhs);
};

// Operators
bool inb(ij ij);
std::ostream &operator<<(std::ostream &os, ij ij);
ij operator+(const ij lhs, const ij rhs);
std::string ToFr(ij ij);
ij FrToIj(const std::string &fr);
ij FrToIj(char file, char rank);

} // namespace chess

#endif