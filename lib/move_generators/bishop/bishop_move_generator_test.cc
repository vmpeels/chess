#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bishop_move_generator.h"
#include "lib/board.h"
#include "lib/piece.h"

namespace chess {
namespace {

using ::testing::UnorderedElementsAreArray;

TEST(BishopMoveGeneratorTest, GetPossibleMovesDefault) {
  Board board;
  ij location = D4;
  Piece bishop(PieceType::BISHOP, PieceColor::WHITE, location);
  board.PlacePiece(bishop, location);

  BishopMoveGenerator bishop_move_generator;

  std::vector<ij> expected_possible_moves = {
      C5, B6, A7,     // Diagonal up to the left
      E5, F6, G7, H8, // Diagonal up to the right
      E3, F2, G1,     // Diagonal down to the right
      C3, B2, A1      // Diagonal down to the left
  };
  std::vector<ij> possible_moves =
      bishop_move_generator.GetPossibleMoves(board, bishop, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(BishopMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfOppositeColorExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece bishop(PieceType::BISHOP, PieceColor::WHITE, location);
  board.PlacePiece(bishop, location);

  Piece pawn(PieceType::PAWN, PieceColor::BLACK, E5);
  board.PlacePiece(pawn, E5);
  BishopMoveGenerator bishop_move_generator;

  std::vector<ij> expected_possible_moves = {
      C5, B6, A7, // Diagonal up to the left
      E5,         // Diagonal up to the right
      E3, F2, G1, // Diagonal down to the right
      C3, B2, A1  // Diagonal down to the left
  };
  std::vector<ij> possible_moves =
      bishop_move_generator.GetPossibleMoves(board, bishop, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(BishopMoveGeneratorTest,
     GetPossibleMovesHitsPieceOfSameColorNotExistsInLegalMoves) {
  Board board;
  ij location = D4;
  Piece bishop(PieceType::BISHOP, PieceColor::WHITE, D4);
  board.PlacePiece(bishop, D4);

  Piece pawn(PieceType::PAWN, PieceColor::WHITE, E5);
  board.PlacePiece(pawn, E5);
  BishopMoveGenerator bishop_move_generator;

  std::vector<ij> expected_possible_moves = {
      C5, B6, A7, // Diagonal up to the left
      E3, F2, G1, // Diagonal down to the right
      C3, B2, A1, // Diagonal down to the left
  };
  std::vector<ij> possible_moves =
      bishop_move_generator.GetPossibleMoves(board, bishop, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(BishopMoveGenerator, GetPossibleMovesEdgeOfBoard) {
  Board board;
  ij location = A1;
  Piece bishop(PieceType::BISHOP, PieceColor::WHITE, location);
  board.PlacePiece(bishop, location);
  BishopMoveGenerator bishop_move_generator;

  std::vector<ij> expected_possible_moves = {
      B2, C3, D4, E5, F6, G7, H8 // Diagonal up to the right
  };
  std::vector<ij> possible_moves =
      bishop_move_generator.GetPossibleMoves(board, bishop, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}
} // namespace
} // namespace chess