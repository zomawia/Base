#pragma once

#include "../Maths.h"
//
//// slipping this in here so that drawing functions can be used
//// even if the library isn't linked up
//namespace sfw
//{
//	void sfw::drawTextureMatrix3(unsigned, unsigned, unsigned, const float[9], float);
//}
//


#ifndef TRANS_MAX_CHILDREN
#define TRANS_MAX_CHILDREN 16
#endif


#include "../../../sfw/sfwdraw.h"

namespace base
{
	inline void debugDrawLine(const vec2 &start, const vec2 &end, unsigned color = 0xffffffff)
	{
		sfw::drawLine(start.x, start.y, end.x, end.y, color);
	}
}