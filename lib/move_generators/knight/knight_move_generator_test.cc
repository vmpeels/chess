#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "knight_move_generator.h"
#include "lib/board.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator_test_util.h"
#include "lib/piece.h"

namespace chess {
namespace {
using ::testing::UnorderedElementsAreArray;

TEST(KnightMoveGeneratorTest, GetPossibleMovesDefault) {
  Board board;
  ij location = D4;
  Piece knight(PieceType::KNIGHT, PieceColor::WHITE, location);
  board.PlacePiece(knight, location);

  std::vector<move> expected_possible_moves =
      testing::ConvertToMoves({B3, C2, E2, F3, B5, C6, E6, F5});
  KnightMoveGenerator knight_move_generator;
  std::vector<move> possible_moves =
      knight_move_generator.GetPossibleMoves(board, knight, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(KnightMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfOppositeColorExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece knight(PieceType::KNIGHT, PieceColor::WHITE, location);
  board.PlacePiece(knight, location);

  board.PlacePiece(Piece(PieceType::PAWN, PieceColor::BLACK, B3), B3);

  std::vector<move> expected_possible_moves =
      testing::ConvertToMoves({B3, C2, E2, F3, B5, C6, E6, F5}, B3);
  KnightMoveGenerator knight_move_generator;
  std::vector<move> possible_moves =
      knight_move_generator.GetPossibleMoves(board, knight, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(KnightMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfSameColorNotExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece knight(PieceType::KNIGHT, PieceColor::WHITE, location);
  board.PlacePiece(knight, location);

  board.PlacePiece(Piece(PieceType::PAWN, PieceColor::WHITE, B3), B3);

  std::vector<move> expected_possible_moves =
      testing::ConvertToMoves({C2, E2, F3, B5, C6, E6, F5});
  KnightMoveGenerator knight_move_generator;
  std::vector<move> possible_moves =
      knight_move_generator.GetPossibleMoves(board, knight, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(KnightMoveGeneratorTest, GetPossibleMovesEdgeOfBoard) {
  Board board;
  ij location = A1;
  Piece knight(PieceType::KNIGHT, PieceColor::WHITE, A1);
  board.PlacePiece(knight, location);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({B3, C2});
  KnightMoveGenerator knight_move_generator;
  std::vector<move> possible_moves =
      knight_move_generator.GetPossibleMoves(board, knight, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}
} // namespace
} // namespace chess