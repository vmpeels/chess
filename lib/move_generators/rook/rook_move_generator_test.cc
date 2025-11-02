#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lib/board.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator_test_util.h"
#include "lib/piece.h"
#include "rook_move_generator.h"

namespace chess {
namespace {
using ::testing::UnorderedElementsAreArray;

TEST(RookMoveGeneratorTest, GetPossibleMovesDefault) {
  Board board;
  ij location = D4;
  Piece rook(PieceType::ROOK, PieceColor::WHITE, location);
  board.PlacePiece(rook, D4);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      D5, D6, D7, D8, // Up
      D3, D2, D1,     // Down
      C4, B4, A4,     // Left
      E4, F4, G4, H4  // Right
  });
  RookMoveGenerator rook_move_generator;
  std::vector<move> possible_moves =
      rook_move_generator.GetPossibleMoves(board, rook, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(RookMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfOppositeColorExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece rook(PieceType::ROOK, PieceColor::WHITE, location);
  board.PlacePiece(rook, D4);

  Piece pawn(PieceType::PAWN, PieceColor::BLACK, E4);
  board.PlacePiece(pawn, E4);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves(
      {
          D5,
          D6,
          D7,
          D8, // Up
          D3,
          D2,
          D1, // Down
          C4,
          B4,
          A4, // Left
          E4, // Right
      },
      E4);
  RookMoveGenerator rook_move_generator;
  std::vector<move> possible_moves =
      rook_move_generator.GetPossibleMoves(board, rook, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(BishopMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfSameColorNotExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece rook(PieceType::ROOK, PieceColor::WHITE, location);
  board.PlacePiece(rook, D4);

  Piece pawn(PieceType::PAWN, PieceColor::WHITE, E4);
  board.PlacePiece(pawn, E4);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      D5,
      D6,
      D7,
      D8, // Up
      D3,
      D2,
      D1, // Down
      C4,
      B4,
      A4, // Left
          // No right
  });
  RookMoveGenerator rook_move_generator;
  std::vector<move> possible_moves =
      rook_move_generator.GetPossibleMoves(board, rook, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(BishopMoveGenerator, GetPossibleMovesEdgeOfBoard) {
  Board board;
  ij location = A1;
  Piece rook(PieceType::ROOK, PieceColor::WHITE, location);
  board.PlacePiece(rook, location);
  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      A2,
      A3,
      A4,
      A5,
      A6,
      A7,
      A8, // Up
      B1,
      C1,
      D1,
      E1,
      F1,
      G1,
      H1, // Right
  });
  RookMoveGenerator rook_move_generator;
  std::vector<move> possible_moves =
      rook_move_generator.GetPossibleMoves(board, rook, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}
} // namespace
} // namespace chess