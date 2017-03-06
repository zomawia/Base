#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"

class GameState : public BaseState
{
	Factory factory;
	
	unsigned spr_space, spr_gras1, spr_gras2, 
		spr_tree1, spr_tree2, spr_rock1, spr_rock2,	spr_animal, spr_font,
		spr_HUDfont, spr_button, spr_cursor, spr_wind, spr_egg;

	ObjectPool<Entity>::iterator currentCamera;
	ObjectPool<Entity>::iterator buttonAnimal;
	ObjectPool<Entity>::iterator buttonTree;
	ObjectPool<Entity>::iterator buttonTime;
	ObjectPool<Entity>::iterator buttonWind;
	ObjectPool<Entity>::iterator buttonAss3;
public:
	float dtMult = 1.f;

	virtual void init()
	{
		//spr_bullet = sfw::loadTextureMap("../res/bullet.png");
		//spr_ship = sfw::loadTextureMap("../res/ship.png");

		spr_rock1 = sfw::loadTextureMap("../res/rock1.png");
		spr_rock2 = sfw::loadTextureMap("../res/rock2.png");
		spr_tree1 = sfw::loadTextureMap("../res/tree1.png");
		spr_tree2 = sfw::loadTextureMap("../res/tree2.png");
		spr_space = sfw::loadTextureMap("../res/space.png");
		spr_gras1 = sfw::loadTextureMap("../res/grass1.png");
		spr_gras2 = sfw::loadTextureMap("../res/grass2.png");
		spr_animal = sfw::loadTextureMap("../res/animal.png", 3, 2);
		
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
		spr_button = sfw::loadTextureMap("../res/button.png");
		spr_HUDfont = sfw::loadTextureMap("../res/uglyfont.png", 16, 16);
		spr_cursor = sfw::loadTextureMap("../res/cursor.png");

		spr_wind = sfw::loadTextureMap("../res/wind.png");
		spr_egg = sfw::loadTextureMap("../res/eggfacts.png");

	}

	virtual void play()
	{
		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(1600, 900, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 800, 0 });

		factory.spawnStaticImage(spr_space, 0, -450, 3600, 2000);

		buttonAss3		= factory.spawnButton(spr_button, spr_HUDfont, -50, -50, 12, 14, "ass3");
		buttonAnimal	= factory.spawnButton(spr_button, spr_HUDfont, -50, -130, 12, 14, "animal");
		buttonTree		= factory.spawnButton(spr_button, spr_HUDfont, -50, -210, 12, 14, "tree");
		buttonWind		= factory.spawnButton(spr_button, spr_HUDfont, -50, -290, 12, 14, "wind");
		buttonTime		= factory.spawnButton(spr_button, spr_HUDfont, -50, -370, 12, 14, "time");

		factory.spawnController(spr_cursor, spr_font);

		for (int i = 0; i < 6; ++i) {
			factory.spawnTree(spr_tree1);
			factory.spawnTree(spr_tree2);

			factory.spawnAnimal(spr_animal, spr_font);

			factory.spawnRock(spr_rock1);
			factory.spawnRock(spr_rock2);

			factory.spawnGrass(spr_gras1);
			factory.spawnGrass(spr_gras2);
			factory.spawnGrass(spr_gras1);
			factory.spawnGrass(spr_gras2);
		}

	}

	virtual void stop()
	{

	}

	// should return what state we're going to.
	// REMEMBER TO HAVE ENTRY AND STAY states for each application state!
	virtual size_t next() const { 
		if (sfw::getKey(KEY_ESCAPE))
			return MENU;
		
		return GAME; 
	}


	// update loop, where 'systems' exist
	virtual void step()
	{
		float dt = sfw::getDeltaTime() * dtMult;

		int windChance = randomRange(0, 100);

		if (windChance == 20) {			
			factory.spawnWind(spr_wind);
			factory.spawnWind(spr_wind);
		}

		// maybe spawn some asteroids here.		

		for (auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

			// state-machine updates
			if (e.animal) {
				e.text->setString(e.animal->getStateToChar());				
			}

			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			// controller update
			if (e.controller) {				
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

				if (!e.lifetime->isAlive() && e.egg && e.egg->spawned == false) {
					e.egg->spawned = true;
					factory.spawnAnimal(spr_animal, spr_font, e.egg->myPos);
				}
				
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


		//animal do stuff
		for (auto it = factory.begin(); it != factory.end(); it++) {
			for (auto bit = it; bit != factory.end(); bit++) {
				if (it != bit && bit->animal && it->tree)
				{
					bit->animal->setTarget(bit->transform, it->transform);
					bit->animal->gotoDest(bit->transform, dt);
					bit->animal->processEating(bit->transform, it->tree, dt);

					//kill animal
					if (bit->animal->shouldThisAnimaBeEuthanisedOrBePutDeathPermanently() == true)
					{
						bit->onFree();
						bit.free();
					}
				}

				if (it != bit && it->animal && bit->animal) {
					it->animal->processEgging(it->transform, bit->transform);
					if (it->animal->canLayEgg() == true) {
						it->animal->layedEgg = true;
						factory.spawnEgg(spr_egg, it->transform->getGlobalPosition());
					}
				}
			}

		}

		//tree do stuff



		// Physics system!		
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for (auto bit = it; bit != factory.end(); bit++) {		  // for every other entity
				if (!it->animal || !it->rock || !bit->animal || !bit->rock)
				{
					if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
						// if they aren't the same and they both have collidable bits...
					{
						//// test their bounding boxes
						if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
						{
							// if true, get the penetration and normal from the convex hulls
							auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);

							if (cd.result() && it->tree && bit->wind) {
								int c = randomRange(0, 1);
								c = 1 ? factory.spawnSapling(spr_tree1, it->transform->getGlobalPosition(), abs(bit->rigidbody->velocity.x))
									: factory.spawnSapling(spr_tree2, it->transform->getGlobalPosition(), abs(bit->rigidbody->velocity.x));
							}

							// if there was a collision,
							if (cd.result() && it->button && bit->controller && bit->controller->isClicked == true)
							{
								if (it->button == buttonAnimal->button) {
									factory.spawnAnimal(spr_animal, spr_font);
									//printf("spawned animal\n");
								}

								else if (it->button == buttonTree->button) {
									int c = randomRange(0, 1);
									c = 1 ? factory.spawnTree(spr_tree1, spr_font)
										: factory.spawnTree(spr_tree2, spr_font);
									//printf("spawned tree\n");
								}

								else if (it->button == buttonTime->button) {
									dtMult += 1.0f;

									if (dtMult > 3)
										dtMult = 1.f;
									//printf("increased time mult to: %f\n", dtMult);
								}

								else if (it->button == buttonWind->button) {
									for (int i = 0; i < 20; ++i)
										factory.spawnWind(spr_wind);
								}

								else if (it->button == buttonAss3->button) {
									factory.spawnEgg(spr_egg, { 0, -300 });
								}
							}
						}
					}
				}				
			}

	}


	virtual void draw()	
	{
		float dt = sfw::getDeltaTime();
		
		float camX = currentCamera->transform->getGlobalPosition().x;
		float camY = currentCamera->transform->getGlobalPosition().y;

		//printf("x:%f   y:%f\n", camX, camY);

		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
		{
			//if (e.transform && e.collider)
			//	e.collider->draw(&e.transform, cam);
			
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

//#ifdef _DEBUG
//		
//		//printf("cam x = %f, cam y = %f\n", 
//		//	currentCamera->transform->getGlobalPosition().x,
//		//	currentCamera->transform->getGlobalPosition().y);
//
//		for each(auto &e in factory)
//			if (e.transform)
//				e.transform->draw(cam);
//
//		for each(auto &e in factory)
//			if (e.transform && e.collider)
//				e.collider->draw(&e.transform, cam);
//
//		for each(auto &e in factory)
//			if (e.transform && e.rigidbody)
//				e.rigidbody->draw(&e.transform, cam);
//#endif
