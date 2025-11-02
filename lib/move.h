#ifndef MOVE_H
#define MOVE_H

#include "lib/ij.h"

namespace chess {
struct move {
  ij loc;
  bool capture;
  friend bool operator==(const move lhs, const move rhs);
  friend bool operator!=(const move lhs, const move rhs);
};

std::ostream &operator<<(std::ostream &os, move ij);

} // namespace chess

#endif