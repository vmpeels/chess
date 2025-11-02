#include <iostream>
#include <string>

#include "lib/board.h"
#include "lib/constants.h"
#include "lib/ij.h"
#include "lib/move_manager.h"
#include "lib/piece.h"

using ::chess::Board;

enum class Turn {
  WHITE,
  BLACK,
};

Turn FlipTurn(Turn cur) {
  switch (cur) {
  case Turn::WHITE:
    return Turn::BLACK;
  case Turn::BLACK:
    return Turn::WHITE;
  }
}

std::string WhoToPlay(Turn turn) {
  switch (turn) {
  case Turn::WHITE:
    return "     == White to play ==    ";
  case Turn::BLACK:
    return "== Black to play ==";
  }
}

bool ValidPieceFormat(std::string piece) {
  if (piece.size() != 3) {
    return false;
  }
  char piece_symbol = piece[0];
  if (!chess::ValidPieceSymbol(piece_symbol)) {
    return false;
  }
  char file = piece[1];
  if (!chess::ValidFileChar(file)) {
    return false;
  }
  char rank = piece[2];
  if (!chess::ValidRankChar(rank)) {
    return false;
  }
  return true;
}

bool ValidMove(const std::string &move) {
  return chess::ValidFileChar(move[0]) && chess::ValidRankChar(move[1]);
}

std::string
LegalMovesFileRankString(const std::vector<chess::ij> &legal_moves) {
  std::string legal_move_filerank_string = "{";
  std::string separator = "";

  for (int i = 0; i < legal_moves.size(); ++i) {
    legal_move_filerank_string += chess::ToFr(legal_moves[i]);
    if (i != legal_moves.size() - 1) {
      legal_move_filerank_string += ",";
    }
  }
  legal_move_filerank_string += "}";
  return legal_move_filerank_string;
}

int main() {
  std::cout << "welcome to chess!" << std::endl;

  std::cout << "press enter to start a game..." << std::endl;
  std::cin.get();

  bool game_over = false;
  Board board;
  board.ArrangePieces();
  Turn cur_turn = Turn::WHITE;
  while (!game_over) {
    std::cout << WhoToPlay(cur_turn) << std::endl;
    std::cout << '\n';
    std::cout << board << std::endl;
    std::cout << '\n';

    // TODO(ryan)
    // Move picker loop.
    bool made_move = false;
    while (!made_move) {
      std::cout << "Type a piece to move: ";
      std::string piece_str;
      getline(std::cin, piece_str);
      if (!ValidPieceFormat(piece_str)) {
        std::cout << "Invalid piece format! Format for typing piece is <piece "
                     "symbol><file><rank>: Please retry.\n";
        continue;
      }
      char piece_symbol = piece_str[0];
      char file = piece_str[1];
      char rank = piece_str[2];
      chess::ij piece_location = chess::FrToIj(file, rank);
      chess::Piece piece = board.GetPiece(chess::FrToIj(file, rank));
      if (piece.empty()) {
        std::cout << "No piece at " << file << rank << std::endl;
        continue;
      }
      if (piece.symbol() != piece_symbol) {
        std::cout << "Internal error. Queried piece does not match board's "
                     "piece. Board piece symbol: "
                  << piece.symbol() << " queried piece symbol: " << piece_symbol
                  << std::endl;
        continue;
      }

      chess::MoveManager move_manager;
      std::vector<chess::ij> legal_moves =
          move_manager.GetLegalMoves(board, piece, piece_location);
      std::string fileranks;
      std::cout << "Please select a move from the list of valid moves: "
                << LegalMovesFileRankString(legal_moves) << std::endl;
      bool received_valid_move_or_quit = false;
      std::string move_str;
      while (!received_valid_move_or_quit) {
        getline(std::cin, move_str);
        if (move_str == "q") {
          received_valid_move_or_quit = true;
        } else if (!ValidMove(move_str)) {
          std::cout << "enter a valid move or type q to exit" << std::endl;
        } else {
          received_valid_move_or_quit = true;
        }
      }

      chess::ij get_move_ij = chess::FrToIj(move_str);
      board.MakeMove(piece, piece_location, get_move_ij);
      made_move = true;
    }

    // Type a piece to move. Format = <piece symbol><file><rank>. EX: ra2 == The
    // rook on A2.
    //
    // Program lists all possible moves. Type the move you want to
    // move the rook to. Confirm move. Make move.
  }
}