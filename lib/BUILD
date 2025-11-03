load("@rules_cc//cc:cc_library.bzl", "cc_library")

# TODO(vmpeels): Perhaps make our visibility rules better... does this whole
# thing really need to be public?
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "board",
    srcs = [
        "board.cc",
    ],
    hdrs = [
        "board.h",
    ],
    deps = [
        ":board_coordinates",
        ":constants",
        ":ij",
        ":move",
        ":piece",
        ":piece_manager",
    ],
)

cc_library(
    name = "constants",
    srcs = [
        "constants.cc",
    ],
    hdrs = [
        "constants.h",
    ],
)

cc_library(
    name = "piece_manager",
    srcs = ["piece_manager.cc"],
    hdrs = ["piece_manager.h"],
    deps = [
        ":ij",
        ":piece",
        "@abseil-cpp//absl/container:flat_hash_map",
    ],
)

cc_library(
    name = "board_coordinates",
    hdrs = [
        "board_coordinates.h",
    ],
    deps = [
        ":ij",
    ],
)

cc_library(
    name = "ij",
    srcs = [
        "ij.cc",
    ],
    hdrs = [
        "ij.h",
    ],
    deps = [
        ":constants",
    ],
)

cc_library(
    name = "piece",
    srcs = [
        "piece.cc",
    ],
    hdrs = [
        "piece.h",
    ],
    deps = [
        ":constants",
        ":ij",
    ],
)

cc_library(
    name = "move",
    srcs = [
        "move.cc",
    ],
    hdrs = [
        "move.h",
    ],
    deps = [
        ":ij",
    ],
)

cc_library(
    name = "move_manager",
    srcs = [
        "move_manager.cc",
    ],
    hdrs = [
        "move_manager.h",
    ],
    deps = [
        ":board",
        ":ij",
        ":move",
        ":piece",
        "//lib/move_generators:move_generator_dispatch",
    ],
)

cc_library(
    name = "chess-lib",
    hdrs = [
        "board.h",
    ],
    deps = [
        ":board",
        ":board_coordinates",
        ":constants",
        ":ij",
        ":move_manager",
        ":piece",
    ],
)
