#include "FloatUtils.h"
#include <cmath>

bool FloatUtils::isEqual(double x, double y) {
    return (fabs(x - y) < 0.001);
}
