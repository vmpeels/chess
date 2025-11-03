#ifndef PIECE_MANAGER_H
#define PIECE_MANAGER_H

#include "absl/container/flat_hash_map.h"
#include "ij.h"
#include "piece.h"
#include <string>

namespace chess {

// TODO(vmpeels): What is the point of this class? What is it doing?
class PieceManager {
public:
  PieceManager() = default;
  void AddPiece(Piece p, ij location);
  void RemovePiece(Piece piece, ij location);
  void ChangePieceLocation(Piece piece, ij cur_location, ij new_location);
  ij GetKingLocation(PieceColor color);
  std::vector<ij> GetPieceLocations(PieceColor color);

private:
  absl::flat_hash_map<std::string, ij> black_pieces_;
  absl::flat_hash_map<std::string, ij> white_pieces_;
  std::string white_king_id_;
  std::string black_king_id_;
};

} // namespace chess

#endif