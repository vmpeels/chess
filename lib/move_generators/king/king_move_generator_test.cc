#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "king_move_generator.h"
#include "lib/board.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator_test_util.h"
#include "lib/piece.h"

namespace chess {
namespace {

using ::testing::UnorderedElementsAreArray;

TEST(KingMoveGeneratorTest, GetPossibleMovesDefault) {
  Board board;
  ij location = D4;
  Piece king(PieceType::KING, PieceColor::WHITE, location);
  board.PlacePiece(king, location);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      C5, D5, E5, // above the king
      C4, E4,     // same as king
      C3, D3, E3  // below king
  });
  KingMoveGenerator king_move_generator;
  std::vector<move> possible_moves =
      king_move_generator.GetPossibleMoves(board, king, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(KingMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfOppositeColorExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece king(PieceType::KING, PieceColor::WHITE, location);
  board.PlacePiece(king, location);

  board.PlacePiece(Piece(PieceType::PAWN, PieceColor::BLACK, C5), C5);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves(
      {
          C5, D5, E5, // above the king
          C4, E4,     // same as king
          C3, D3, E3  // below king
      },
      C5);
  KingMoveGenerator king_move_generator;
  std::vector<move> possible_moves =
      king_move_generator.GetPossibleMoves(board, king, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(KingMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfSameColorNotExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece king(PieceType::KING, PieceColor::WHITE, location);
  board.PlacePiece(king, location);

  board.PlacePiece(Piece(PieceType::PAWN, PieceColor::WHITE, C5), C5);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      D5, E5,    // above the king
      C4, E4,    // same as king
      C3, D3, E3 // below king
  });
  KingMoveGenerator king_move_generator;
  std::vector<move> possible_moves =
      king_move_generator.GetPossibleMoves(board, king, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(KingMoveGeneratorTest, GetPossibleMovesEdgeOfBoard) {
  Board board;
  ij location = A1;
  Piece king(PieceType::KING, PieceColor::WHITE, location);
  board.PlacePiece(king, location);

  std::vector<move> expected_possible_moves =
      testing::ConvertToMoves({A2, B2, B1});
  KingMoveGenerator king_move_generator;
  std::vector<move> possible_moves =
      king_move_generator.GetPossibleMoves(board, king, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}
} // namespace
} // namespace chess