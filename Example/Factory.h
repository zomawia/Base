#pragma once

#include "Entity.h"
#include <string>

class Factory
{	
	ObjectPool<Entity>	  entities;
	
	// The factory will store an object pool for each component type
	ObjectPool<Transform> transforms;
	ObjectPool<Rigidbody> rigidbodies;
	ObjectPool<Collider>  colliders;
	ObjectPool<Sprite>    sprites;
	ObjectPool<Lifetime>  lifetimes;
	ObjectPool<Camera>    cameras;
	ObjectPool<Text>	  texts;	

	ObjectPool<PlayerController> controllers;
	ObjectPool<CameraController> cameraControllers;
	
	ObjectPool<Animal>	animals;
	ObjectPool<Tree>	trees;
	ObjectPool<Button>	buttons;

	ObjectPool<Wind>	winds;
	ObjectPool<Rock>	rocks;
	ObjectPool<Egg>		eggs;

public:

	// iterators to access the entity pool
	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }

	// for now, they're all the same size
	Factory(size_t size = 512)
		: entities(size), transforms(size), rigidbodies(size),
		colliders(size), sprites(size), lifetimes(size),
		cameras(10), controllers(size), texts(size),
		cameraControllers(10), animals(size), trees(size), buttons(20), winds(size),
		rocks(size), eggs(size)
	{
	}

	// What follows are specialized spawning functions
	// just observe the steps taken and replicate for your own usages

	ObjectPool<Entity>::iterator spawnCamera(float w2, float h2, float zoom)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->camera = cameras.push();
		e->camera->offset = vec2{w2,h2};
		e->camera->scale = vec2{ zoom,zoom };
		e->cameraControllers = cameraControllers.push();
		return e;
	}

	ObjectPool<Entity>::iterator spawnButton(unsigned sprite, unsigned font, 
		float x, float y, float w, float h, char *text)	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->button = buttons.push();		
		//e->sprite = sprites.push();
		e->collider = colliders.push();

		e->button->setString(text);
		e->button->tint = WHITE;
		e->transform->setLocalScale(vec2{ 76,76 });

		e->button->sprite_id = sprite;
		e->button->frame_id = 0;
		e->button->dimensions = vec2{ w,h };
		e->button->font = font;
		e->button->offset = vec2{ x,y };
		
		//e->sprite->sprite_id = sprite;
		//e->sprite->dimensions = vec2{ w,h };
		//	e->sprite->tint = WHITE;
		
		return e;
	}

	ObjectPool<Entity>::iterator spawnController(unsigned sprite, unsigned font, bool isScaled = false)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->collider = colliders.push();
		e->sprite = sprites.push();
		e->controller = controllers.push();

		e->text = texts.push();

		e->text->sprite_id = font;
		e->text->offset = vec2{ -24,-24 };
		e->text->off_scale = vec2{.5f,.5f};
		e->text->setString("ass3");

		e->transform->setLocalScale(vec2{12,12});

		e->sprite->sprite_id = sprite;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{ w,h };
		//	e->sprite->tint = WHITE;
		e->transform->setLocalPosition(vec2{ x,y });
		return e;
	}

	ObjectPool<Entity>::iterator spawnTree(unsigned sprite, bool isScaled = true)
	{
		auto e = entities.push();

		e->tree = trees.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->lifetime = lifetimes.push();

		e->lifetime->lifespan = randomRange(30, 75);

		e->transform->setLocalScale(vec2{ 48,48 });
		
		//e->transform->setGlobalPosition(vec2::fromAngle(randRange(0, 360)*DEG2RAD)*(rand01() * 200 + 64));
		
		e->transform->setGlobalPosition(vec2{ randomRange(-1500, 1500), randomRange(-800, 0) });

		//e->rigidbody->addSpin(rand01()*12-6);

		e->sprite->sprite_id = sprite;
		//e->sprite->tint = GREEN;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnSapling(unsigned sprite, vec2 pos, float windOffset, bool isScaled = true)
	{
		auto e = entities.push();

		e->tree = trees.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->lifetime = lifetimes.push();

		e->lifetime->lifespan = randomRange(30, 75);

		e->transform->setLocalScale(vec2{ 48,48 });

		//e->transform->setGlobalPosition(vec2::fromAngle(randRange(0, 360)*DEG2RAD)*(rand01() * 200 + 64));

		e->transform->setGlobalPosition(vec2{ pos.x - windOffset, pos.y});

		//e->rigidbody->addSpin(rand01()*12-6);

		e->sprite->sprite_id = sprite;
		//e->sprite->tint = GREEN;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnWind(unsigned sprite, bool isScaled = true)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->collider = colliders.push();
		e->wind = winds.push();
		e->sprite = sprites.push();

		e->rigidbody->addImpulse(vec2{ -250, 0 });

		e->lifetime = lifetimes.push();
		e->lifetime->lifespan = randomRange(1, 10);

		e->transform->setLocalScale({ randomRange(3, 6), 1 });
		e->transform->setGlobalPosition(vec2{ randomRange(-1500, 1500), randomRange(-800, 0) });

		e->sprite->sprite_id = sprite;
		//e->sprite->tint = WHITE;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnRock(unsigned sprite, bool isScaled = true)
	{
		auto e = entities.push();

		e->rock = rocks.push();
		e->transform = transforms.push();
		//e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		//e->collider = colliders.push();

		e->transform->setLocalScale(vec2{ 12,12 });

		//e->transform->setGlobalPosition(vec2::fromAngle(randRange(0, 360)*DEG2RAD)*(rand01() * 200 + 64));

		e->transform->setGlobalPosition(vec2{ randomRange(-1500, 1500), randomRange(-800, 0) });

		//e->rigidbody->addSpin(rand01()*12-6);

		e->sprite->sprite_id = sprite;
		//e->sprite->tint = GREEN;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnEgg(unsigned sprite, vec2 pos, bool isScaled = true)
	{
		auto e = entities.push();

		e->egg = eggs.push();
		e->transform = transforms.push();		
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();

		e->lifetime->lifespan = 15.f;

		e->egg->myPos = pos;

		e->transform->setLocalScale(vec2{ 8,12 });
		e->transform->setGlobalPosition(vec2{ pos.x, pos.y });
		
		e->sprite->sprite_id = sprite;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnGrass(unsigned sprite, bool isScaled = true)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->sprite = sprites.push();

		e->transform->setLocalScale(vec2{ randomRange(4, 6), randomRange(4, 10) });
		e->transform->setGlobalPosition(vec2{ randomRange(-1500, 1500), randomRange(-800, 0) });

		e->sprite->sprite_id = sprite;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnAnimal(unsigned sprite, unsigned font = NULL, vec2 pos = { 0, 0 }, bool isScaled = true)
	{
		auto e = entities.push();

		e->animal = animals.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->text = texts.push();

		e->lifetime = lifetimes.push();
		e->lifetime->lifespan = randomRange(30, 75);

		e->transform->setLocalScale(vec2{ 30,20 });

		if (pos == vec2{ 0, 0 }) {
			e->transform->setGlobalPosition(vec2{ randomRange(-1500, 1500), randomRange(-800, -100) });
		}
		else
			e->transform->setGlobalPosition(pos);

		e->text->sprite_id = font;
		e->text->offset = vec2{ -24,-24 };
		e->text->off_scale = vec2{ .5f,.5f };
		
		e->text->setString("treehump");

		e->sprite->sprite_id = sprite;

		if (isScaled) {
			e->transform->setBeAffectedByScale();
		}

		return e;
	}

	ObjectPool<Entity>::iterator spawnBullet(unsigned sprite, vec2 pos, vec2 dim, float ang, float impulse, unsigned faction)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();
		e->collider = colliders.push();

		e->transform->setLocalPosition(pos);
		e->transform->setLocalScale(dim);
		e->transform->setLocalAngle(ang);

		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{ 1.2f, 1.2f };

		e->rigidbody->addImpulse(e->transform->getGlobalUp() * impulse);

		e->lifetime->lifespan = 1.6f;

		return e;
	}
};


