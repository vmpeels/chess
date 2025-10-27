load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_library(
    name = "move_generator",
    srcs = ["move_generator.cc"],
    hdrs = ["move_generator.h"],
    deps = [
        "//lib:board",
        "//lib:board_coordinates",
        "//lib:piece",
    ],
)

cc_library(
    name = "bishop_move_generator",
    srcs = ["bishop/bishop_move_generator.cc"],
    hdrs = ["bishop/bishop_move_generator.h"],
    deps = [
        ":move_generator",
        "//lib:board",
        "//lib:board_coordinates",
        "//lib:piece",
    ],
)

cc_test(
    name = "bishop_move_generator_test",
    size = "small",
    srcs = [
        "bishop/bishop_move_generator_test.cc",
    ],
    deps = [
        ":bishop_move_generator",
        "//lib:board",
        "//lib:piece",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "rook_move_generator",
    srcs = ["rook/rook_move_generator.cc"],
    hdrs = ["rook/rook_move_generator.h"],
    deps = [
        ":move_generator",
        "//lib:board",
        "//lib:board_coordinates",
        "//lib:piece",
    ],
)

cc_test(
    name = "rook_move_generator_test",
    size = "small",
    srcs = [
        "rook/rook_move_generator_test.cc",
    ],
    deps = [
        ":rook_move_generator",
        "//lib:board",
        "//lib:piece",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "knight_move_generator",
    srcs = ["knight/knight_move_generator.cc"],
    hdrs = ["knight/knight_move_generator.h"],
    deps = [
        ":move_generator",
        "//lib:board",
        "//lib:board_coordinates",
        "//lib:piece",
    ],
)

cc_test(
    name = "knight_move_generator_test",
    size = "small",
    srcs = [
        "knight/knight_move_generator_test.cc",
    ],
    deps = [
        ":knight_move_generator",
        "//lib:board",
        "//lib:piece",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "queen_move_generator",
    srcs = ["queen/queen_move_generator.cc"],
    hdrs = ["queen/queen_move_generator.h"],
    deps = [
        ":move_generator",
        "//lib:board",
        "//lib:board_coordinates",
        "//lib:piece",
    ],
)

cc_test(
    name = "queen_move_generator_test",
    size = "small",
    srcs = [
        "queen/queen_move_generator_test.cc",
    ],
    deps = [
        ":queen_move_generator",
        "//lib:board",
        "//lib:piece",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "king_move_generator",
    srcs = ["king/king_move_generator.cc"],
    hdrs = ["king/king_move_generator.h"],
    deps = [
        ":move_generator",
        "//lib:board",
        "//lib:board_coordinates",
        "//lib:piece",
    ],
)

cc_test(
    name = "king_move_generator_test",
    size = "small",
    srcs = [
        "king/king_move_generator_test.cc",
    ],
    deps = [
        ":king_move_generator",
        "//lib:board",
        "//lib:piece",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "pawn_move_generator",
    srcs = ["pawn_move_generator.cc"],
    hdrs = ["pawn_move_generator.h"],
    deps = [
        ":move_generator",
        "//lib:board",
        "//lib:board_coordinates",
        "//lib:piece",
    ],
)

cc_test(
    name = "pawn_move_generator_test",
    size = "small",
    srcs = [
        "pawn_move_generator_test.cc",
    ],
    deps = [
        ":pawn_move_generator",
        "//lib:board",
        "//lib:piece",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

test_suite(
    name = "move_generator_tests",
    tests = [
        ":bishop_move_generator_test",
        ":king_move_generator_test",
        ":knight_move_generator_test",
        ":queen_move_generator_test",
        ":rook_move_generator_test",
    ],
)
