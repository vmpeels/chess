# Thoughts

Thoughts that I'm having while I'm working on this project

## Questions
- How is it possible that I'm able to access the board coordinates created in
board_coordinates.h without including that file in any of the files that use it?
  - Answer: Because I was building and running in bazel with the flag "--feature=layering_check".
  - Documentation: https://bazel.build/docs/bazel-and-cpp