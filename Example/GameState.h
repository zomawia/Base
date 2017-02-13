#pragma once

#include "../sfw/sfwdraw.h"
#include "../Base/BaseState.h"
#include "Factory.h"


class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_ship, spr_bullet, spr_roid;

public:
	virtual void init()
	{
		spr_bullet = sfw::loadTextureMap("../res/bullet.png");
		spr_space = sfw::loadTextureMap("../res/space.jpg");
		spr_ship = sfw::loadTextureMap("../res/ship.png");
		spr_roid = sfw::loadTextureMap("../res/rock.png");
	}

	virtual void play()
	{
		factory.spawnStaticImage(spr_space, 0, 0, 800, 600);
		factory.currentCamera = factory.spawnCamera(800, 600, 1);
		factory.currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });	

		factory.spawnPlayer(spr_ship);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
	}

	virtual void stop()
	{
		for (auto it = factory.begin(); it != factory.end(); it.free());
	}

	virtual size_t next() const { return 0; }

	virtual void step()
	{
		float dt = sfw::getDeltaTime();

		// maybe spawn some asteroids here.

		for each(auto &e in factory)
		{
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			if (e.transform && e.rigidbody && e.controller)
			{
				e.controller->poll(&e.transform, &e.rigidbody, dt);
				if (e.controller->shotRequest)
				{
					factory.spawnBullet(spr_bullet, e.transform->getGlobalPosition(), vec2{ 32,32 }, e.transform->getGlobalAngle(), 10, 1);
				}
			}
			if (e.lifetime)
				e.lifetime->age(dt);

		
		}


		for(auto it = factory.begin(); it != factory.end(); it++)
			for(auto bit = it; bit != factory.end(); bit++)
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				{
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						if (cd.result())
						{
							if (it->rigidbody && bit->rigidbody)
								base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);
							
							else if (it->rigidbody && !bit->rigidbody)							
								base::StaticResolution(cd, &it->transform, &it->rigidbody);					
						}
					}
				}

	}


	virtual void draw()	
	{
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, factory.currentCamera->camera->getCameraMatrix(&factory.currentCamera->transform));
	}
};