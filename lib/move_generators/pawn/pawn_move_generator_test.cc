#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "lib/board.h"
#include "lib/move.h"
#include "lib/move_generators/move_generator_test_util.h"
#include "lib/piece.h"
#include "pawn_move_generator.h"

namespace chess {
namespace {

using ::testing::UnorderedElementsAreArray;

TEST(PawnMoveGeneratorTest, GetAttackingSquaresWhite) {
  Board board;
  ij location = D2;
  Piece pawn(PieceType::PAWN, PieceColor::WHITE, location);
  board.PlacePiece(pawn, location);

  std::vector<move> expected_attacking_squares =
      testing::ConvertToMoves({C3, E3});
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetAttackingSquares(board, pawn, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_attacking_squares));
}

TEST(PawnMoveGeneratorTest, GetAttackingSquaresBlack) {
  Board board;
  ij location = D7;
  Piece pawn(PieceType::PAWN, PieceColor::BLACK, location);
  board.PlacePiece(pawn, location);

  std::vector<move> expected_attacking_squares =
      testing::ConvertToMoves({C6, E6});
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetAttackingSquares(board, pawn, location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_attacking_squares));
}

TEST(PawnMoveGeneratorTest, GetAttackingSquaresEdgeOfBoardWhite) {
  Board board;
  ij location1 = A2;
  Piece pawn1(PieceType::PAWN, PieceColor::WHITE, location1);
  board.PlacePiece(pawn1, location1);

  std::vector<move> expected_attacking_squares1 = testing::ConvertToMoves({B3});
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves1 =
      pawn_move_generator.GetAttackingSquares(board, pawn1, location1);
  EXPECT_THAT(possible_moves1,
              UnorderedElementsAreArray(expected_attacking_squares1));

  ij location2 = H2;
  Piece pawn2(PieceType::PAWN, PieceColor::WHITE, location2);
  board.PlacePiece(pawn2, location2);

  std::vector<move> expected_attacking_squares2 = testing::ConvertToMoves({G3});
  std::vector<move> possible_moves2 =
      pawn_move_generator.GetAttackingSquares(board, pawn2, location2);
  EXPECT_THAT(possible_moves2,
              UnorderedElementsAreArray(expected_attacking_squares2));
}

TEST(PawnMoveGeneratorTest, GetAttackingSquaresEdgeOfBoardBlack) {
  Board board;
  ij location1 = A7;
  Piece pawn1(PieceType::PAWN, PieceColor::BLACK, location1);
  board.PlacePiece(pawn1, location1);

  std::vector<move> expected_attacking_squares1 = testing::ConvertToMoves({B6});
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves1 =
      pawn_move_generator.GetAttackingSquares(board, pawn1, location1);
  EXPECT_THAT(possible_moves1,
              UnorderedElementsAreArray(expected_attacking_squares1));

  ij location2 = H7;
  Piece pawn2(PieceType::PAWN, PieceColor::BLACK, location2);
  board.PlacePiece(pawn2, location2);

  std::vector<move> expected_attacking_squares2 = testing::ConvertToMoves({G6});
  std::vector<move> possible_moves2 =
      pawn_move_generator.GetAttackingSquares(board, pawn2, location2);
  EXPECT_THAT(possible_moves2,
              UnorderedElementsAreArray(expected_attacking_squares2));
}

TEST(PawnMoveGeneratorTest, GetPossibleMovesStartingSquareWhite) {
  Board board;
  ij start_location = D2;
  Piece pawn(PieceType::PAWN, PieceColor::WHITE, start_location);
  board.PlacePiece(pawn, start_location);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      D3, // Default move
      D4, // En passant
  });
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetPossibleMoves(board, pawn, start_location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(PawnMoveGeneratorTest, GetPossibleMovesStartingSquareBlack) {
  Board board;
  ij start_location = D7;
  Piece pawn(PieceType::PAWN, PieceColor::BLACK, start_location);
  board.PlacePiece(pawn, start_location);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves({
      D6, // Default move
      D5, // En passant
  });
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetPossibleMoves(board, pawn, start_location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(PawnMoveGeneratorTest,
     GetPossibleMovesStartingSquarePiecesCanCaptureWhite) {
  Board board;
  ij start_location = D2;
  Piece pawn(PieceType::PAWN, PieceColor::WHITE, start_location);
  board.PlacePiece(pawn, start_location);

  Piece capturable1(PieceType::PAWN, PieceColor::BLACK, C3);
  Piece capturable2(PieceType::PAWN, PieceColor::BLACK, E3);
  board.PlacePiece(capturable1, C3);
  board.PlacePiece(capturable2, E3);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves(
      {
          D3,    // Default move
          D4,    // En passant
          C3, E3 // Can capture pieces on C3 and E3
      },
      {C3, E3});
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetPossibleMoves(board, pawn, start_location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(PawnMoveGeneratorTest,
     GetPossibleMovesStartingSquarePiecesCanCaptureBlack) {
  Board board;
  ij start_location = D7;
  Piece pawn(PieceType::PAWN, PieceColor::BLACK, start_location);
  board.PlacePiece(pawn, start_location);

  Piece capturable1(PieceType::PAWN, PieceColor::WHITE, C6);
  Piece capturable2(PieceType::PAWN, PieceColor::WHITE, E6);
  board.PlacePiece(capturable1, C6);
  board.PlacePiece(capturable2, E6);

  std::vector<move> expected_possible_moves = testing::ConvertToMoves(
      {
          D6,    // Default move
          D5,    // En passant
          C6, E6 // Can capture pieces on C3 and E3
      },
      {C6, E6});
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetPossibleMoves(board, pawn, start_location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(PawnMoveGeneratorTest,
     GetPossibleMovesStartingSquareCaptureEnPassantWhite) {
  Board board;
  ij start_location = D5;
  Piece white_pawn(PieceType::PAWN, PieceColor::WHITE, start_location);
  board.PlacePiece(white_pawn, start_location);

  // Now place the black pawn on its starting location, then move it en passant.
  Piece black_pawn(PieceType::PAWN, PieceColor::BLACK, C7);
  board.PlacePiece(black_pawn, C7);
  board.MakeMove(black_pawn, C7, {.loc = C5, .capture = false});

  std::vector<move> expected_possible_moves = {
      {.loc = D6, .capture = false, .en_passant_capture = false},
      {.loc = C6, .capture = true, .en_passant_capture = true}};
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetPossibleMoves(board, white_pawn, start_location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

TEST(PawnMoveGeneratorTest,
     GetPossibleMovesStartingSquareCaptureEnPassantBlack) {
  Board board;
  ij start_location = D4;
  Piece black_pawn(PieceType::PAWN, PieceColor::BLACK, start_location);
  board.PlacePiece(black_pawn, start_location);

  // Now place the white pawn on its starting location, then move it en passant.
  Piece white_pawn(PieceType::PAWN, PieceColor::WHITE, C2);
  board.PlacePiece(white_pawn, C2);
  board.MakeMove(white_pawn, C2, {.loc = C4, .capture = false});

  std::vector<move> expected_possible_moves = {
      {.loc = D3, .capture = false, .en_passant_capture = false},
      {.loc = C3, .capture = true, .en_passant_capture = true}};
  PawnMoveGenerator pawn_move_generator;
  std::vector<move> possible_moves =
      pawn_move_generator.GetPossibleMoves(board, black_pawn, start_location);
  EXPECT_THAT(possible_moves,
              UnorderedElementsAreArray(expected_possible_moves));
}

} // namespace
} // namespace chess