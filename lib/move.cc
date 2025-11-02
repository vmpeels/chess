#include "move.h"

namespace chess {
bool operator==(const move lhs, const move rhs) {
  return lhs.loc == rhs.loc && lhs.capture == rhs.capture &&
         lhs.en_passant_capture == rhs.en_passant_capture;
}

bool operator!=(const move lhs, const move rhs) { return !(lhs == rhs); }

std::ostream &operator<<(std::ostream &os, move move) {
  os << move.loc << (move.capture ? "x" : "");
  return os;
}

} // namespace chess