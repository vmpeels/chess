#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lib/board.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator_test_util.h"
#include "lib/piece.h"
#include "queen_move_generator.h"

namespace chess {
namespace {
using ::testing::UnorderedElementsAreArray;

TEST(QueenMoveGeneratorTest, GetPossibleMovesDefault) {
  Board board;
  ij location = D4;
  Piece queen(PieceType::QUEEN, PieceColor::WHITE, D4);
  board.PlacePiece(queen, D4);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      C5, B6, A7,     // Diagonal up to the left
      E5, F6, G7, H8, // Diagonal up to the right
      E3, F2, G1,     // Diagonal down to the right
      C3, B2, A1,     // Diagonal down to the left
      D5, D6, D7, D8, // Up
      D3, D2, D1,     // Down
      C4, B4, A4,     // Left
      E4, F4, G4, H4  // Right
  });
  QueenMoveGenerator queen_move_generator;
  std::vector<move> possible_moves =
      queen_move_generator.GetPossibleMoves(board, queen, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(QueenMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfOppositeColorExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece queen(PieceType::QUEEN, PieceColor::WHITE, location);
  board.PlacePiece(queen, D4);

  Piece pawn1(PieceType::PAWN, PieceColor::BLACK, E5);
  board.PlacePiece(pawn1, E5);
  Piece pawn2(PieceType::PAWN, PieceColor::BLACK, E4);
  board.PlacePiece(pawn2, E4);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves(
      {
          C5, B6, A7,     // Diagonal up to the left
          E5,             // Diagonal up to the right
          E3, F2, G1,     // Diagonal down to the right
          C3, B2, A1,     // Diagonal down to the left
          D5, D6, D7, D8, // Up
          D3, D2, D1,     // Down
          C4, B4, A4,     // Left
          E4,             // Right
      },
      {E4, E5});
  QueenMoveGenerator queen_move_generator;
  std::vector<move> possible_moves =
      queen_move_generator.GetPossibleMoves(board, queen, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(QueenMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfSameColorNotExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece queen(PieceType::QUEEN, PieceColor::WHITE, location);
  board.PlacePiece(queen, D4);

  Piece pawn1(PieceType::PAWN, PieceColor::WHITE, E5);
  board.PlacePiece(pawn1, E5);

  Piece pawn2(PieceType::PAWN, PieceColor::WHITE, E4);
  board.PlacePiece(pawn2, E4);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      C5, B6, A7,     // Diagonal up to the left
      E3, F2, G1,     // Diagonal down to the right
      C3, B2, A1,     // Diagonal down to the left
      D5, D6, D7, D8, // Up
      D3, D2, D1,     // Down
      C4, B4, A4,     // Left
  });
  QueenMoveGenerator queen_move_generator;
  std::vector<move> possible_moves =
      queen_move_generator.GetPossibleMoves(board, queen, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(QueenMoveGenerator, GetPossibleMovesEdgeOfBoard) {
  Board board;
  ij location = A1;
  Piece queen(PieceType::QUEEN, PieceColor::WHITE, location);
  board.PlacePiece(queen, location);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      B2, C3, D4, E5, F6, G7, H8, // Diagonal up to the right
      A2, A3, A4, A5, A6, A7, A8, // Up
      B1, C1, D1, E1, F1, G1, H1, // Right
  });
  QueenMoveGenerator queen_move_generator;
  std::vector<move> possible_moves =
      queen_move_generator.GetPossibleMoves(board, queen, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}
} // namespace
} // namespace chess