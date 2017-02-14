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

	void scaleDraw(const Transform *T, const mat3 &C, const Transform *CT) {		
		// the top y pos divided by uhh
		float a = T->getGlobalPosition().y;
		float b = CT->getGlobalPosition().y;
		float sc = dist(vec2{ 0,a }, vec2{ 0,b }) / 200;

		if (sc > 8) sc = 8;
		if (sc < .25f) sc = .25f;

		mat3 glob = C * T->getGlobalTransform() * mat3::translate(offset) * mat3::rotate(angle) * mat3::scale(dimensions * sc);

		sfw::drawTextureMatrix3(sprite_id, frame_id, tint, glob.v, 0);
	}

	void draw(const Transform *T, const mat3 &C) const	{
		mat3 glob = C * T->getGlobalTransform() * getDrawMatrix();		
		sfw::drawTextureMatrix3(sprite_id, frame_id, tint, glob.v, 0);
	}
};

}
//sfw::drawTE