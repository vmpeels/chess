#include "ij.h"
#include "constants.h"

#include <ostream>

namespace chess {

bool inb(ij ij) {
  return ij.i >= 0 && ij.i < NUM_RANKS && ij.j >= 0 && ij.j < NUM_FILES;
}

// == Operators ==
std::ostream &operator<<(std::ostream &os, ij ij) {
  return os << "(" << ij.i << "," << ij.j << ")";
}

bool operator==(const ij lhs, const ij rhs) {
  return lhs.i == rhs.i && lhs.j == rhs.j;
}

bool operator!=(const ij lhs, const ij rhs) { return !(lhs == rhs); }

ij operator+(const ij lhs, const ij rhs) {
  return {lhs.i + rhs.i, lhs.j + rhs.j};
}

std::string ToFr(ij ij) {
  std::string out;
  out += FILES[ij.j];
  out += RANKS[NUM_RANKS - ij.i - 1];
  return out;
}

} // namespace chess