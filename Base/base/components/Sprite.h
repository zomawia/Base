#pragma once

#include "compdef.h"
#include "Transform.h"


namespace base
{
// The sprite will always be attached to the
class Sprite
{
public:
	size_t sprite_id, frame_id;
	vec2 offset, dimensions;
	float angle;
	bool centered;
	unsigned tint;

	Sprite(size_t a_sprite_id = 0, float w = 1, float h = 1) :
		sprite_id(a_sprite_id), dimensions(w,h),
		frame_id(0), offset(0,0), angle(0), centered(true), tint(0xffffffff)
	{}

	mat3 getDrawMatrix() const
	{
		return  mat3::translate(offset) * mat3::rotate(angle) * mat3::scale(dimensions);
	}

	void draw(const Transform *T, const mat3 &C) const
	{
		mat3 glob = C * T->getGlobalTransform() * getDrawMatrix();
		sfw::drawTextureMatrix3(sprite_id, frame_id, tint, glob.v, 0);
	}
};

}
//sfw::drawTE