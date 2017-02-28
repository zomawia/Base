#pragma once

#include "Base.h"

using namespace base;

class PlayerController
{

public:
	vec2 mouse;
	float clickTimer;
	bool isClicked = false;

	vec2 getMousePos() { return vec2{ sfw::getMouseX(), sfw::getMouseY() }; }
	

	void poll(base::Transform *T, vec2 worldMouse, float dt)
	{
		T->setGlobalPosition(worldMouse);
		
		//detect mouse clicks
		clickTimer -= dt;
		if (sfw::getMouseButton(MOUSE_BUTTON_LEFT) && clickTimer < 0)
		{
			isClicked = true;
			clickTimer = 0.5f;
		}
		else isClicked = false;
	}
};