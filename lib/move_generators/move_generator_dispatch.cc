#include "move_generator_dispatch.h"
#include "lib/constants.h"
#include "lib/move_generators/bishop/bishop_move_generator.h"
#include "lib/move_generators/king/king_move_generator.h"
#include "lib/move_generators/knight/knight_move_generator.h"
#include "lib/move_generators/pawn/pawn_move_generator.h"
#include "lib/move_generators/queen/queen_move_generator.h"
#include "lib/move_generators/rook/rook_move_generator.h"
#include "move_generator.h"

namespace chess {
std::unique_ptr<MoveGenerator> GetMoveGenerator(PieceType piece_type) {
  switch (piece_type) {
  case PieceType::PAWN:
    return std::make_unique<PawnMoveGenerator>();
  case PieceType::ROOK:
    return std::make_unique<RookMoveGenerator>();
  case PieceType::KNIGHT:
    return std::make_unique<KnightMoveGenerator>();
  case PieceType::BISHOP:
    return std::make_unique<BishopMoveGenerator>();
  case PieceType::QUEEN:
    return std::make_unique<QueenMoveGenerator>();
  case PieceType::KING:
    return std::make_unique<KingMoveGenerator>();
  default:
    std::cout << "got unhandleable piece type: " << piece_type << std::endl;
    assert(false);
  }
}

} // namespace chess