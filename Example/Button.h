#pragma once

#include "Base.h"

using namespace base;

class Button {
public:
	bool mouseOver;
	char m_characters[80];
	unsigned sprite_id;
	unsigned font;
	
	vec2 offset = vec2{ 0,0 };
	vec2 off_scale = vec2{ 1, 1 };

	size_t frame_id;
	vec2 dimensions;	

	unsigned tint;

	void setString(const char *src) { strcpy_s(m_characters, 80, src); }
	Button() { setString(""); }

	

	void update(Transform *transform, const Transform *cam) {				
		// needed for static button position
		transform->setGlobalPosition(cam->getGlobalPosition() + offset);
		
		if (mouseOver == true)
			tint = 0xff0000AA;
		else
			tint = 0x000000AA;
		

	}

	void draw(const Transform *T, const mat3 &cam)
	{
		auto glob = cam * T->getGlobalTransform();

		auto pos = glob.getTrans2D();
		auto dim = glob.getScale2D();

		//button sprite
		sfw::drawTextureMatrix3(sprite_id, frame_id, tint, glob.v, 0);
		
		//black shadowing
		sfw::drawString(font, m_characters, pos.x - 36, pos.y - 1, dimensions.x, dimensions.y, 0, 0, BLACK);

		//white text
		sfw::drawString(font, m_characters, pos.x-37, pos.y, dimensions.x, dimensions.y, 0);
	}

};

