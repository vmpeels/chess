#ifndef MOVE_GENERATOR_TEST_UTIL_H
#define MOVE_GENERATOR_TEST_UTIL_H

#include "lib/ij.h"
#include "lib/move.h"
#include <optional>
#include <vector>

namespace chess {
namespace testing {
std::vector<move> ConvertToMoves(const std::vector<ij> &ijs,
                                 std::optional<ij> capture = std::nullopt);

std::vector<move> ConvertToMoves(const std::vector<ij> &ijs,
                                 const std::vector<ij> &capture);
} // namespace testing
} // namespace chess

#endif