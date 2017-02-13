#pragma once

#include "hull.h"

namespace base
{
struct collision
{
	float penetration; vec2 normal;

	bool result() const { return penetration >= 0; }
};


inline collision best(const collision &A, const collision &B)
{
	auto n = A.penetration <  B.penetration ? A : B;
	auto x = A.penetration >= B.penetration ? A : B;

	return x.penetration < 0 ? x : n;
}


collision collides(const hull &A, const hull &B)
{
	vec2 axes[MAX_HULL_SIZE + MAX_HULL_SIZE];

	size_t size = 0;
	for (int i = 0; i < A.size; ++i) axes[size++] = A.normals[i];
	for (int i = 0; i < B.size; ++i) axes[size++] = B.normals[i];

	collision retval = collision{ INFINITY };

	for(int i = 0; i < size; ++i)
	{
		auto &axis = axes[i];

		float pDl = A.max(axis) - B.min(axis);
		float pDr = B.max(axis) - A.min(axis);	

		auto t = collision{ flops::min(pDl, pDr), copysignf(1, pDl - pDr) * axis };

		retval = best(retval, t);
	}
	return retval;
}
}