#include "ij.h"

namespace chess {
// == static board coordinates ==
constexpr ij A1{7, 0};
constexpr ij A2{6, 0};
constexpr ij A3{5, 0};
constexpr ij A4{4, 0};
constexpr ij A5{3, 0};
constexpr ij A6{2, 0};
constexpr ij A7{1, 0};
constexpr ij A8{0, 0};

constexpr ij B1{7, 1};
constexpr ij B2{6, 1};
constexpr ij B3{5, 1};
constexpr ij B4{4, 1};
constexpr ij B5{3, 1};
constexpr ij B6{2, 1};
constexpr ij B7{1, 1};
constexpr ij B8{0, 1};

constexpr ij C1{7, 2};
constexpr ij C2{6, 2};
constexpr ij C3{5, 2};
constexpr ij C4{4, 2};
constexpr ij C5{3, 2};
constexpr ij C6{2, 2};
constexpr ij C7{1, 2};
constexpr ij C8{0, 2};

constexpr ij D1{7, 3};
constexpr ij D2{6, 3};
constexpr ij D3{5, 3};
constexpr ij D4{4, 3};
constexpr ij D5{3, 3};
constexpr ij D6{2, 3};
constexpr ij D7{1, 3};
constexpr ij D8{0, 3};

constexpr ij E1{7, 4};
constexpr ij E2{6, 4};
constexpr ij E3{5, 4};
constexpr ij E4{4, 4};
constexpr ij E5{3, 4};
constexpr ij E6{2, 4};
constexpr ij E7{1, 4};
constexpr ij E8{0, 4};

constexpr ij F1{7, 5};
constexpr ij F2{6, 5};
constexpr ij F3{5, 5};
constexpr ij F4{4, 5};
constexpr ij F5{3, 5};
constexpr ij F6{2, 5};
constexpr ij F7{1, 5};
constexpr ij F8{0, 5};

constexpr ij G1{7, 6};
constexpr ij G2{6, 6};
constexpr ij G3{5, 6};
constexpr ij G4{4, 6};
constexpr ij G5{3, 6};
constexpr ij G6{2, 6};
constexpr ij G7{1, 6};
constexpr ij G8{0, 6};

constexpr ij H1{7, 7};
constexpr ij H2{6, 7};
constexpr ij H3{5, 7};
constexpr ij H4{4, 7};
constexpr ij H5{3, 7};
constexpr ij H6{2, 7};
constexpr ij H7{1, 7};
constexpr ij H8{0, 7};

constexpr int PAWN_STARTING_RANK_WHITE = A2.j;
constexpr int PAWN_STARTING_RANK_BLACK = A7.j;

} // namespace chess