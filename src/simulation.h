#pragma once

#include <cstdint>
#include <random>

#include "grid.h"

namespace life {

class Simulation {
public:
    Simulation(std::uint32_t seed, double alive_probability = 0.5, int fps = 15);

    void reseed(std::uint32_t seed);
    void randomize();
    void tick();   // advance one generation
    void render(); // draw current grid
    void run();    // animation loop (Ctrl+C to quit)

private:
    std::uint32_t seed_;
    std::mt19937 rng_;
    std::bernoulli_distribution alive_;

    int fps_ = 15;
    std::uint64_t generation_ = 0;

    int width_;
    int height_;

    Grid current_;
    Grid next_;

    void clear_screen_();
};

} // namespace life