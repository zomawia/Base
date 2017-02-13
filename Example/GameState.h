#pragma once

#include "../sfw/sfwdraw.h"
#include "../Base/BaseState.h"
#include "Factory.h"


class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_ship, spr_bullet, spr_roid, spr_font;

public:
	virtual void init()
	{
		spr_bullet = sfw::loadTextureMap("../res/bullet.png");
		spr_space = sfw::loadTextureMap("../res/space.jpg");
		spr_ship = sfw::loadTextureMap("../res/ship.png");
		spr_roid = sfw::loadTextureMap("../res/rock.png");
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
	}

	virtual void play()
	{
		factory.spawnStaticImage(spr_space, 0, 0, 800, 600);
		factory.currentCamera = factory.spawnCamera(800, 600, 1);
		factory.currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });	

		factory.spawnPlayer(spr_ship, spr_font);
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

		for(auto it = factory.begin(); it != factory.end();)
		{
			bool del = false;
			auto &e = *it;

			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			if (e.transform && e.rigidbody && e.controller)
			{
				e.controller->poll(&e.transform, &e.rigidbody, dt);
				if (e.controller->shotRequest)
				{
					factory.spawnBullet(spr_bullet, e.transform->getGlobalPosition()  + e.transform->getGlobalUp()*48,
											vec2{ 32,32 }, e.transform->getGlobalAngle(), 200, 1);
				}
			}
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}
			if (!del) it++;
			else it.free();
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
		auto cam = factory.currentCamera->camera->getCameraMatrix(&factory.currentCamera->transform);

		
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);


#ifdef _DEBUG
		for each(auto &e in factory)
			if (e.transform)
				e.transform->draw(cam);

		for each(auto &e in factory)
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.rigidbody)
				e.rigidbody->draw(&e.transform, cam);
#endif
	}
};