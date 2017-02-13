#pragma once

#include "mathdef.h"


namespace base
{
namespace flops
{

inline bool fequals(float a, float b) { return (a < b + FLUDGE && b < a + FLUDGE); }

inline float lerp(float s, float e, float t) { return (t - 1)*s + t*e; }

inline float min(float a, float b) { return a < b ? a : b; }

inline float max(float a, float b) { return a < b ? b : a; }

inline float clamp(float v, float n, float x) { return min(x, max(v, n)); }

inline float snap(float v, float n, float x) { return v - n < x - v ? n : x; }

inline bool overlap(float an, float ax, float bn, float bx)
{
	return (ax >= bn && bx >= an);
}

}
}