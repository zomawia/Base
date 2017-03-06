#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"

//main menu first screen splash yes

class MenuState : public BaseState
{
	Factory factory;

	unsigned spr_space, spr_gras1, spr_gras2,
		spr_tree1, spr_tree2, spr_rock1, spr_rock2, spr_animal, spr_font,
		spr_HUDfont, spr_button, spr_cursor, spr_title;

	ObjectPool<Entity>::iterator currentCamera;
	ObjectPool<Entity>::iterator background;
	ObjectPool<Entity>::iterator buttonPlay;
	ObjectPool<Entity>::iterator buttonExit;

	bool backGroundFinishedMoving;
	bool runOnce;

public:	
	virtual void init() {	

		spr_rock1 = sfw::loadTextureMap("../res/rock1.png");
		spr_rock2 = sfw::loadTextureMap("../res/rock2.png");
		spr_tree1 = sfw::loadTextureMap("../res/tree1.png");
		spr_tree2 = sfw::loadTextureMap("../res/tree2.png");
		spr_space = sfw::loadTextureMap("../res/space.png");
		spr_gras1 = sfw::loadTextureMap("../res/grass1.png");
		spr_gras2 = sfw::loadTextureMap("../res/grass2.png");
		spr_animal = sfw::loadTextureMap("../res/animal.png", 3, 2);

		spr_font = sfw::loadTextureMap("../res/font.png", 32, 4);
		spr_button = sfw::loadTextureMap("../res/button.png");
		spr_HUDfont = sfw::loadTextureMap("../res/uglyfont.png", 16, 16);
		spr_cursor = sfw::loadTextureMap("../res/cursor.png");

		spr_title = sfw::loadTextureMap("../res/gameTitle.png");

	}

	virtual void play() {
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(1600, 900, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 800, 0 });

		background = factory.spawnStaticImage(spr_space, 0, -450, 3200, 1800);

		factory.spawnController(spr_cursor, spr_font);

		backGroundFinishedMoving = false;
		runOnce = false;
	}

	virtual void stop()
	{

	}

	virtual size_t next() const {
		if (sfw::getKey('P') || sfw::getKey(KEY_ENTER))
			return ENTER_GAME;

		if (sfw::getKey('E') || sfw::getKey(KEY_ESCAPE))
			return EXIT_MENU;

		return MENU;
	}


	// update loop, where 'systems' exist
	virtual void step() {
		float dt = sfw::getDeltaTime();

		// maybe spawn some asteroids here.		

		float posX = background->transform->getGlobalPosition().x;
		float posY = background->transform->getGlobalPosition().y;
		//printf("%f\n", posY);

		if (posY > -800) {
			background->transform->setGlobalPosition({ posX, posY - 95 * dt });
		}
		else {
			backGroundFinishedMoving = true;
		}

		if (backGroundFinishedMoving == true && runOnce == false) {
			factory.spawnStaticImage(spr_animal, -200, -650, 120, 100);
			factory.spawnStaticImage(spr_animal, -800, -520, 110, 95);
			factory.spawnStaticImage(spr_tree1, 120, -815, 150, 150);
			factory.spawnStaticImage(spr_tree2, 700, -640, 140, 140);
			
			buttonPlay = factory.spawnButton(spr_button, spr_HUDfont, -500, -90, 12, 14, "PLAY (P)");
			buttonPlay->transform->setLocalScale({ 140, 80 });
			buttonPlay->button->tint = WHITE;

			buttonExit = factory.spawnButton(spr_button, spr_HUDfont, -300, -190, 12, 14, "EXIT (E)");
			buttonExit->transform->setLocalScale({ 140, 80 });
			buttonExit->button->tint = WHITE;

			factory.spawnStaticImage(spr_title, 0, -400, 900, 500);

			runOnce = true;
		}



		for (auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

			// controller update
			if (e.controller)
			{
				vec2 screenMouse = { sfw::getMouseX(), sfw::getMouseY() };
				vec2 worldMouse = currentCamera->camera->getScreenPointToWorldPoint(&currentCamera->transform, screenMouse);

				e.controller->poll(&e.transform, worldMouse, dt);
			}

			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			if (e.cameraControllers) {
				e.cameraControllers->poll(&currentCamera->transform, &currentCamera->rigidbody);
			}

			if (e.button) {
				e.button->update(&e.transform, &currentCamera->transform);
			}

			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}
		}

		for (auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for (auto bit = it; bit != factory.end(); bit++)		  // for every other entity

				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
					// if they aren't the same and they both have collidable bits...
				{
					//// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);

						// if there was a collision,
						if (cd.result() && it->button && bit->controller && bit->controller->isClicked == true)
						{
							if (it->button == buttonPlay->button) {
								
								printf("next\n");
							}

							else if (it->button == buttonExit->button) {
								
								printf("strepcontext\n");
							}

							// condition for dynamic resolution
							//if (it->rigidbody && bit->rigidbody)
							//	base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);

							// condition for static resolution
							//else if (it->rigidbody && !bit->rigidbody)							
							//	base::StaticResolution(cd, &it->transform, &it->rigidbody);							
						}
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

		// draw sprites
		for each(auto &e in factory)
		{
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

			if (e.transform->getAffectedByScale() && e.sprite) {
				e.sprite->scaleDraw(&e.transform, cam, &currentCamera->transform);
			}

			if (!e.transform->getAffectedByScale() && !e.controller && e.transform && e.sprite) {
				if (!e.button)
					e.sprite->draw(&e.transform, cam);
			}
		}

		// draw text
		for each(auto &e in factory) {
			if (e.transform && e.text && !e.button)
				e.text->draw(&e.transform, cam);

			if (e.button) {
				e.button->draw(&e.transform, cam);
			}

			if (e.controller)
				e.sprite->draw(&e.transform, cam);
		}
	}
};