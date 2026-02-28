#pragma once

#include <cstdint>
#include <vector>
#include <iosfwd>
#include <string>

namespace life {

struct Grid {
    using Cell = std::uint8_t;

    Grid(int width, int height);

    int width() const { return width_; }
    int height() const { return height_; }

    Cell get(int x, int y) const;
    void set(int x, int y, Cell v);
    void fill(Cell v);

private:
    int width_;
    int height_;
    std::vector<Cell> cells_; // flat storage
};

void render(std::ostream& os, const Grid& g,
            const std::string& alive = "#",
            const std::string& dead  = " ");

} // namespace life