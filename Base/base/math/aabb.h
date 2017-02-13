#pragma once

#include "mat3.h"

namespace base
{
struct aabb
{
	vec2 pos, dim;

	vec2 min() const { return pos - dim; }
	vec2 max() const { return pos + dim; }
	
	aabb(const vec2 &pos = vec2(0,0), const vec2 &half_extents = vec2(.5f,.5f)) : pos(pos), dim(half_extents) {}

	static aabb fromMinMax(const vec2 &N, const vec2 &X)
	{
		return aabb{ (N + X) / 2, (X-N)/2 };
	}
};


inline aabb operator*(const mat3 &M, const aabb& A)
{
	vec3 tP[4];

	// First we want to transform the points
	tP[0] = M * vec3{ A.min(), 1 };
	tP[1] = M * vec3{ A.max(), 1 };
	tP[2] = M * vec3{ A.max().x, A.min().y, 1 };
	tP[3] = M * vec3{ A.min().x, A.max().y, 1 };

	// find the minimum and maximum extents of the transformed points
	vec2 minv = tP[0].xy;
	vec2 maxv = tP[0].xy;

	for (int i = 1; i < 4; ++i)
	{
		minv = min(minv, tP[i].xy);
		maxv = max(maxv, tP[i].xy);
	}

	// evaluate the position and dimensions
	return aabb::fromMinMax(minv, maxv);
}

inline aabb operator+(const aabb &A, const aabb &B) { return aabb::fromMinMax(min(A.min(), B.min()), max(A.max(), B.max())); }

inline bool overlap(const aabb &A, const aabb &B)
{
	return flops::overlap(A.min().x, A.max().x, B.min().x, B.max().x) &&
		   flops::overlap(A.min().y, A.max().y, B.min().y, B.max().y);
}
}