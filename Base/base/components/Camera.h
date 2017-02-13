#pragma once

#include "compdef.h"
#include "Transform.h"

namespace base
{
	class Camera
	{
	public:
		vec2 offset, scale;

		Camera(vec2 a_offset = vec2{400,300}, vec2 a_scale = vec2{ 1,1 })
			: offset(a_offset), scale(a_scale)
		{
		}

		mat3 getCameraMatrix(const Transform *T) const
		{
			return mat3::translate(offset) * mat3::scale(scale) * T->getGlobalTransform().inverse();
		}
	};
}