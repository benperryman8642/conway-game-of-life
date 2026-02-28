#include "life.h"

namespace life {

static int wrap(int v, int n) {
    v %= n;
    if (v < 0) v += n;
    return v;
}

int count_neighbors(const Grid& g, int x, int y) {
    const int w = g.width();
    const int h = g.height();

    int count = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;

            const int nx = wrap(x + dx, w);
            const int ny = wrap(y + dy, h);

            count += (g.get(nx, ny) ? 1 : 0);
        }
    }
    return count;
}

void step(const Grid& current, Grid& next) {
    if (next.width() != current.width() || next.height() != current.height()) {
        next = Grid(current.width(), current.height());
    }

    next.fill(0);

    for (int y = 0; y < current.height(); ++y) {
        for (int x = 0; x < current.width(); ++x) {
            const int n = count_neighbors(current, x, y);
            const bool alive = current.get(x, y) != 0;

            bool out = false;
            if (alive) out = (n == 2 || n == 3);
            else out = (n == 3);

            next.set(x, y, static_cast<Grid::Cell>(out ? 1 : 0));
        }
    }
}

} // namespace life