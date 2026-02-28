#pragma once

#include "grid.h"

namespace life {

int count_neighbors(const Grid& g, int x, int y);

void step(const Grid& current, Grid& next);

}