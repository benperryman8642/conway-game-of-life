# Conway's Game of Life

A small C++ implementation of Conway's Game of Life. This repository contains the source, headers, and a Makefile to build a command-line binary that runs the simulation.

## Repository layout

- `src/` — C++ source files and headers
- `build/` — build output
- `Makefile` — build rules

## Requirements

- A C++ compiler (g++/clang++) supporting C++20 or newer.
- make

## Build

From the repository root run:

```bash
make
```

This will compile the sources and place the binary under `build/` (the Makefile may create `build/life`).

## Run

To run the compiled program:

```bash
make run
```

Adjust arguments as the binary supports (see output/help from running the program).

## License

See the `LICENSE` file in the repo root.
