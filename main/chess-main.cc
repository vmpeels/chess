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
  if (move.length() != 3 && move.length() != 4) {
    std::cout << "here1" << std::endl;
    return false;
  }
  char piece_symbol = move[0];
  if (!chess::ValidPieceSymbol(piece_symbol)) {
    std::cout << "here2" << std::endl;

    return false;
  }

  char file;
  char rank;
  if (move.length() == 3) {
    file = move[1];
    rank = move[2];
  } else {
    if (!chess::IsCaptureSymbol(move[1])) {
      std::cout << "here3" << std::endl;

      return false;
    }
    file = move[2];
    rank = move[3];
  }
  std::cout << "here4" << std::endl;
  return chess::ValidFileChar(file) && chess::ValidRankChar(rank);
}

chess::move StrToMove(const std::string &my_move) {
  if (!ValidMove(my_move)) {
    std::cout << "error converting string to move for move: " << my_move
              << std::endl;
    assert(false);
  }
  char file;
  char rank;
  if (my_move.length() == 3) {
    file = my_move[1];
    rank = my_move[2];
  } else {
    file = my_move[2];
    rank = my_move[3];
  }
  return {.loc = chess::FrToIj(file, rank), .capture = my_move.length() == 4};
}

std::string
LegalMovesFileRankString(const std::vector<chess::move> &legal_moves,
                         char piece_symbol) {
  std::string legal_move_filerank_string = "{";
  std::string separator = "";

  for (int i = 0; i < legal_moves.size(); ++i) {
    legal_move_filerank_string += piece_symbol;
    if (legal_moves[i].capture) {
      legal_move_filerank_string += 'x';
    }
    legal_move_filerank_string += chess::ToFr(legal_moves[i].loc);
    if (i != legal_moves.size() - 1) {
      legal_move_filerank_string += ",";
    }
  }
  legal_move_filerank_string += "}";
  return legal_move_filerank_string;
}

int main() {
  std::cout << "welcome to chess!" << std::endl;
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
      std::vector<chess::move> legal_moves =
          move_manager.GetLegalMoves(board, piece, piece_location);
      std::string fileranks;
      std::cout << "Please select a move from the list of valid moves: "
                << LegalMovesFileRankString(legal_moves, piece.symbol())
                << std::endl;
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

      chess::move my_move = StrToMove(move_str);
      board.MakeMove(piece, piece_location, my_move);
      made_move = true;
    }

    // Type a piece to move. Format = <piece symbol><file><rank>. EX: ra2 == The
    // rook on A2.
    //
    // Program lists all possible moves. Type the move you want to
    // move the rook to. Confirm move. Make move.
  }
}