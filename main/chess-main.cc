#include <iostream>
#include <string>

#include "lib/board.h"
#include "lib/constants.h"

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
  if (std::find(chess::PIECE_SYMBOLS.begin(), chess::PIECE_SYMBOLS.end(),
                piece_symbol) == chess::PIECE_SYMBOLS.end()) {
    return false;
  }
  char file = piece[1];
  if (std::find(chess::FILES.begin(), chess::FILES.end(), file) ==
      chess::FILES.end()) {
    return false;
  }
  char rank = piece[2];
  if (std::find(chess::RANKS.begin(), chess::RANKS.end(), rank) ==
      chess::RANKS.end()) {
    return false;
  }
  return true;
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
      std::string piece;
      getline(std::cin, piece);
      if (!ValidPieceFormat(piece)) {
        std::cout << "Invalid piece format! Format for typing piece is <piece "
                     "symbol><file><rank>: Please retry.\n";
        continue;
      }
    }

    // Type a piece to move. Format = <piece symbol><file><rank>. EX: ra2 == The
    // rook on A2.
    //
    // Program lists all possible moves. Type the move you want to
    // move the rook to. Confirm move. Make move.
  }
}