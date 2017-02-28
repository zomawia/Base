#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"

class MenuState : public BaseState
{
	Factory factory;

	unsigned spr_button, spr_cursor;
	ObjectPool<Entity>::iterator currentCamera;
	
	virtual void play() {
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());


	}

	virtual void stop()
	{

	}

	virtual size_t next() const { return 0; }


	// update loop, where 'systems' exist
	virtual void step()
	{

	}


	virtual void draw()
	{
		float dt = sfw::getDeltaTime();

		float camX = currentCamera->transform->getGlobalPosition().x;
		float camY = currentCamera->transform->getGlobalPosition().y;

		printf("x:%f   y:%f\n", camX, camY);

		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

	}
};