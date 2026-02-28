#include <cstdint>
#include <iostream>
#include "simulation.h"

int main() {
    std::random_device rd;
    std::uint32_t seed = rd();

    std::cout << "Seed: " << seed << "\n";

    life::Simulation sim(seed, /*alive_probability=*/0.35, /*fps=*/15);
    sim.run();

    return 0;
}