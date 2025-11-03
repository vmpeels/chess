#ifndef MOVE_GENERATOR_DISPATCH_H
#define MOVE_GENERATOR_DISPATCH_H
#include "lib/constants.h"
#include "move_generator.h"
namespace chess {

std::unique_ptr<MoveGenerator> GetMoveGenerator(PieceType piece_type);

}
#endif