#pragma once

#include "Base.h"

using namespace base;

class Button {
public:
	char m_characters[10];

public:
	unsigned sprite_id;
	unsigned font;
	vec2 font_scale = { 12,12 };
	vec2 offset = vec2{ 0,0 };
	vec2 off_scale = vec2{ 1, 1 };

	size_t frame_id;
	vec2 dimensions;
	float angle;
	bool centered;
	unsigned tint;


	void setString(const char *src) { strcpy_s(m_characters, 80, src); }
	Button() { setString(""); }

	void update(Transform *transform, const Transform *cam) {		
		// button transform is camera controllers transform
		transform->setGlobalPosition(cam->getGlobalPosition());
	}


	//Put in currentCameras Transform not the Buttons transform
	void draw(const Transform *T, const mat3 &cam)
	{
		auto glob = cam * T->getGlobalTransform();

		auto pos = glob.getTrans2D() + offset;
		auto dim = glob.getScale2D();

		sfw::drawTextureMatrix3(sprite_id, frame_id, tint, glob.v, 0);
		sfw::drawString(font, m_characters, pos.x, pos.y, dim.x*off_scale.x, dim.y*off_scale.y, 0);
	}

};

