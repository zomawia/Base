#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"


/*
	The gamestate represents a discrete container of all that is 
	necessary to drive the game experience.

	A factory object is used to manage the creation and deletion of
	objects in the simulation.

	The game state updates the entities within the factory using
	a series of 'systems.'
*/

class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_ship, 
		spr_tree1, spr_tree2,
		spr_rock1, spr_rock2,
		spr_animal, spr_font;
	ObjectPool<Entity>::iterator currentCamera;


public:
	virtual void init()
	{
		//spr_bullet = sfw::loadTextureMap("../res/bullet.png");
		spr_rock1 = sfw::loadTextureMap("../res/rock1.png");
		spr_rock2 = sfw::loadTextureMap("../res/rock2.png");
		spr_tree1 = sfw::loadTextureMap("../res/tree1.png");
		spr_tree2 = sfw::loadTextureMap("../res/tree2.png");
		spr_space = sfw::loadTextureMap("../res/space.png");
		spr_ship = sfw::loadTextureMap("../res/ship.png");
		spr_animal = sfw::loadTextureMap("../res/animal.png");
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
	}

	virtual void play()
	{
		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(1600, 900, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 800, 0 });

		// call some spawning functions!
		factory.spawnStaticImage(spr_space, 0, -450, 3400, 2000);

		for (int i = 0; i < 1; ++i) {
			factory.spawnTree(spr_tree1);
			factory.spawnTree(spr_tree2);
			factory.spawnAnimal(spr_animal);
			factory.spawnRock(spr_rock1);
			factory.spawnRock(spr_rock2);

		}
		//factory.spawnPlayer(spr_ship, spr_font, true);
		
		

	}

	virtual void stop()
	{

	}

	// should return what state we're going to.
	// REMEMBER TO HAVE ENTRY AND STAY states for each application state!
	virtual size_t next() const { return 0; }


	// update loop, where 'systems' exist
	virtual void step()
	{
		float dt = sfw::getDeltaTime();

		// maybe spawn some asteroids here.		

		for(auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			// controller update
			if (e.transform && e.rigidbody && e.controller)
			{
				
			}

			if (e.cameraControllers) {
				e.cameraControllers->poll(&currentCamera->transform, &currentCamera->rigidbody);
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


		//animal find tree
		for (auto it = factory.begin(); it != factory.end(); it++) {
			for (auto bit = it; bit != factory.end(); bit++)
				if (it != bit && bit->animal && it->tree) {
						//printf("found animal and tree\n");
						bit->animal->setTarget(bit->transform, it->transform);
				}
		}



		// Physics system!		
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for(auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				// if they aren't the same and they both have collidable bits...
				{
					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
						// if there was a collision,
						if (cd.result())
						{
							// condition for dynamic resolution
							if (it->rigidbody && bit->rigidbody)
								base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);
							
							// condition for static resolution
							else if (it->rigidbody && !bit->rigidbody)							
								base::StaticResolution(cd, &it->transform, &it->rigidbody);					
						}
					}
				}

	}


	virtual void draw()	
	{
		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
		{
			if (e.transform->getAffectedByScale() && e.sprite)
				e.sprite->scaleDraw(&e.transform, cam, &currentCamera->transform);
			else if (e.transform && !e.transform->getAffectedByScale() && e.sprite)
				e.sprite->draw(&e.transform, cam);
		}
		// draw text
		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);


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
	}
};