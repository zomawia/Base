#pragma once

#include <random>
#include "flops.h"

namespace base
{
inline float rand01() { return (float)rand() / RAND_MAX; }

inline float randRange(float a, float b) { return flops::lerp(a, b, rand01()); }

// Random number generator
inline float randomRange(int start, int end){ return (rand() % (end - start + 1) + start); }

}