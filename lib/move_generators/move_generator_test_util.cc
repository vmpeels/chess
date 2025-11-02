#include "move_generator_test_util.h"

namespace chess {
namespace testing {
std::vector<move> ConvertToMoves(const std::vector<ij> &ijs,
                                 std::optional<ij> capture) {
  std::vector<move> moves;
  for (ij my_ij : ijs) {
    moves.push_back(move{.loc = my_ij,
                         .capture = capture.has_value() && my_ij == *capture});
  }
  return moves;
}

std::vector<move> ConvertToMoves(const std::vector<ij> &ijs,
                                 const std::vector<ij> &captures) {
  std::vector<move> moves;
  for (ij my_ij : ijs) {
    moves.push_back(move{.loc = my_ij,
                         .capture = std::find(captures.begin(), captures.end(),
                                              my_ij) != captures.end()});
  }
  return moves;
}

} // namespace testing
} // namespace chess