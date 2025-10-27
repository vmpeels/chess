#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <ostream>
#include <string_view>

// TODO(ryannvm): Maybe we can namespace different constants like
// chess::constants::symbols -> all the symbols go here
// chess::constants::names -> etc
namespace chess {

// Piece constants
constexpr char SYMBOL_PAWN = 'p';
constexpr char SYMBOL_KNIGHT = 'n';
constexpr char SYMBOL_BISHOP = 'b';
constexpr char SYMBOL_ROOK = 'r';
constexpr char SYMBOL_QUEEN = 'q';
constexpr char SYMBOL_KING = 'k';
constexpr char SYMBOL_EMPTY = '_';
constexpr std::array<char, 6> PIECE_SYMBOLS = {SYMBOL_PAWN,   SYMBOL_KNIGHT,
                                               SYMBOL_BISHOP, SYMBOL_ROOK,
                                               SYMBOL_QUEEN,  SYMBOL_KING};

constexpr std::string_view NAME_PAWN = "PAWN";
constexpr std::string_view NAME_KNIGHT = "KNIGHT";
constexpr std::string_view NAME_BISHOP = "BISHOP";
constexpr std::string_view NAME_ROOK = "ROOK";
constexpr std::string_view NAME_QUEEN = "QUEEN";
constexpr std::string_view NAME_KING = "KING";
constexpr std::string_view NAME_EMPTY = "EMPTY";

enum class PieceType {
  UNKNOWN,
  PAWN,
  KNIGHT,
  BISHOP,
  ROOK,
  QUEEN,
  KING,
  EMPTY, // EMPTY piece is a unique type that represents "no piece". Used so we
         // don't have to store optionals to pieces in the board.
};

std::ostream &operator<<(std::ostream &os, PieceType piece_type);

enum class PieceColor { UNKNOWN, BLACK, WHITE };

std::ostream &operator<<(std::ostream &os, PieceColor color);
PieceColor operator~(PieceColor color);

// Board constants
constexpr int NUM_FILES = 8;

constexpr char A_FILE = 'a';
constexpr char B_FILE = 'b';
constexpr char C_FILE = 'c';
constexpr char D_FILE = 'd';
constexpr char E_FILE = 'e';
constexpr char F_FILE = 'f';
constexpr char G_FILE = 'g';
constexpr char H_FILE = 'h';
constexpr std::array<char, NUM_FILES> FILES = {A_FILE, B_FILE, C_FILE, D_FILE,
                                               E_FILE, F_FILE, G_FILE, H_FILE};

constexpr char A_FILE_J = 0;
constexpr char B_FILE_J = 1;
constexpr char C_FILE_J = 2;
constexpr char D_FILE_J = 3;
constexpr char E_FILE_J = 4;
constexpr char F_FILE_J = 5;
constexpr char G_FILE_J = 6;
constexpr char H_FILE_J = 7;

constexpr int NUM_RANKS = 8;
constexpr char FIRST_RANK = '1';
constexpr char SECOND_RANK = '2';
constexpr char THIRD_RANK = '3';
constexpr char FOURTH_RANK = '4';
constexpr char FIFTH_RANK = '5';
constexpr char SIXTH_RANK = '6';
constexpr char SEVENTH_RANK = '7';
constexpr char EIGHTH_RANK = '8';
constexpr std::array<char, NUM_RANKS> RANKS = {
    FIRST_RANK, SECOND_RANK, THIRD_RANK,   FOURTH_RANK,
    FIFTH_RANK, SIXTH_RANK,  SEVENTH_RANK, EIGHTH_RANK};

constexpr int FIRST_RANK_I = 7;
constexpr int SECOND_RANK_I = 6;
constexpr int THIRD_RANK_I = 5;
constexpr int FOURTH_RANK_I = 4;
constexpr int FIFTH_RANK_I = 3;
constexpr int SIXTH_RANK_I = 2;
constexpr int SEVENTH_RANK_I = 1;
constexpr int EIGHTH_RANK_I = 0;

enum class BoardOrientation {
  UNKNOWN,
  BLACK,
  WHITE,
};

std::ostream &operator<<(std::ostream &os, BoardOrientation orientation);

} // namespace chess

#endif