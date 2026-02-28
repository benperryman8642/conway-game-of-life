#include "simulation.h"
#include <utility>
#include <chrono>
#include <iostream>
#include <thread>
#include <sys/ioctl.h>
#include <unistd.h>

#include "life.h"

namespace life {

static std::pair<int,int> get_terminal_size() {
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return { static_cast<int>(w.ws_col), static_cast<int>(w.ws_row) };
}

static std::pair<int,int> compute_grid_size() {
    auto [cols, rows] = get_terminal_size();
    const int header_space = 3;

    int w = cols;
    int h = rows - header_space;

    if (w < 5) w = 5;
    if (h < 5) h = 5;

    return {w, h};
}

Simulation::Simulation(std::uint32_t seed, double alive_probability, int fps)
    : seed_(seed),
      rng_(seed),
      alive_(alive_probability),
      fps_(fps),
      width_(compute_grid_size().first),
      height_(compute_grid_size().second),
      current_(width_, height_),
      next_(width_, height_)
{
    if (fps_ < 1) fps_ = 1;
    if (fps_ > 120) fps_ = 120;

    if (alive_probability < 0.0) alive_probability = 0.0;
    if (alive_probability > 1.0) alive_probability = 1.0;
    alive_ = std::bernoulli_distribution(alive_probability);

    randomize();
}

void Simulation::reseed(std::uint32_t seed) {
    seed_ = seed;
    rng_.seed(seed);
}

void Simulation::randomize() {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            current_.set(x, y, static_cast<Grid::Cell>(alive_(rng_) ? 1 : 0));
        }
    }
    generation_ = 0;
}

void Simulation::tick() {
    step(current_, next_);
    current_ = next_; // copies cells; fine for now at this size
    ++generation_;
}

void Simulation::clear_screen_() {
    // ANSI escape: clear + move cursor to home
    std::cout << "\x1B[2J\x1B[H";
}

void Simulation::render() {
    clear_screen_();
    std::cout << "Conway's Game of Life | gen: " << generation_
              << " | Seed: " << seed_
              << " | " << width_ << "x" << height_
              << " | Ctrl+C to quit\n\n";
    life::render(std::cout, current_, "█", " ");
    std::cout.flush();
}

void Simulation::run() {
    const auto frame = std::chrono::milliseconds(1000 / fps_);

    while (true) {
        render();
        tick();
        std::this_thread::sleep_for(frame);
    }
}

}