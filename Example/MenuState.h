#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"

class MenuState : public BaseState
{
	Factory factory;

	unsigned spr_button, spr_cursor, spr_space, spr_font, spr_HUDfont;
	ObjectPool<Entity>::iterator currentCamera;
	ObjectPool<Entity>::iterator buttonPlay;
	ObjectPool<Entity>::iterator buttonExit;
	
	virtual void init() {
		spr_space = sfw::loadTextureMap("../res/space.png");
		spr_font = sfw::loadTextureMap("../res/font.png", 32, 4);
		spr_button = sfw::loadTextureMap("../res/button.png");
		spr_HUDfont = sfw::loadTextureMap("../res/uglyfont.png", 16, 16);
		spr_cursor = sfw::loadTextureMap("../res/cursor.gif");

	}

	virtual void play() {
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(1600, 900, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 800, 0 });

		factory.spawnStaticImage(spr_space, 0, -450, 3600, 2000);


	}

	virtual void stop()
	{

	}

	virtual size_t next() const { return 0; }


	// update loop, where 'systems' exist
	virtual void step()	{
		float dt = sfw::getDeltaTime();

		// maybe spawn some asteroids here.		

		for (auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

			// state-machine updates
			if (e.animal) {
				e.text->setString(e.animal->getStateToChar());
			}

			// controller update
			if (e.controller)
			{
				vec2 screenMouse = { sfw::getMouseX(), sfw::getMouseY() };
				vec2 worldMouse = currentCamera->camera->getScreenPointToWorldPoint(&currentCamera->transform, screenMouse);

				e.controller->poll(&e.transform, worldMouse, dt);
			}

			if (e.cameraControllers) {
				e.cameraControllers->poll(&currentCamera->transform, &currentCamera->rigidbody);
			}

			if (e.button) {
				e.button->update(&e.transform, &currentCamera->transform);
			}

			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}
		}
	}


	virtual void draw()
	{
		float dt = sfw::getDeltaTime();

		float camX = currentCamera->transform->getGlobalPosition().x;
		float camY = currentCamera->transform->getGlobalPosition().y;

		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);



	}
};