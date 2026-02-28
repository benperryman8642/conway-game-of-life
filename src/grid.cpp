#include "grid.h"
#include <ostream>

namespace life {

Grid::Grid(int width, int height)
    : width_(width),
      height_(height),
      cells_(width * height, 0)
{
}

Grid::Cell Grid::get(int x, int y) const {
    return cells_[y * width_ + x];
}

void Grid::set(int x, int y, Cell v) {
    cells_[y * width_ + x] = v;
}

void Grid::fill(Cell v) {
    std::fill(cells_.begin(), cells_.end(), v);
}

void render(std::ostream& os, const Grid& g,
            const std::string& alive,
            const std::string& dead)
{
    for (int y = 0; y < g.height(); ++y) {
        for (int x = 0; x < g.width(); ++x) {
            os << (g.get(x, y) ? alive : dead);
        }
        os << '\n';
    }
}

} // namespace life