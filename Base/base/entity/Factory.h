#pragma once

#include "Entity.h"

class Factory
{
	ObjectPool<Entity>	  entities;
	ObjectPool<Transform> transforms;
	ObjectPool<Rigidbody> rigidbodies;
	ObjectPool<Collider>  colliders;
	ObjectPool<Sprite>    sprites;
	ObjectPool<Lifetime>  lifetimes;
	ObjectPool<Camera>    cameras;

public:
	ObjectPool<Entity>::iterator currentCamera;

	Factory(size_t size = 512, float sW =800, float sH = 600)
								: entities(size), transforms(size), rigidbodies(size),
								  colliders(size), sprites(size), lifetimes(size),
								  cameras(size)
	{
		currentCamera = spawnCamera(800,600,1);
	}

	ObjectPool<Entity>::iterator spawnCamera(float w2, float h2, float zoom)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->camera = cameras.push();
		e->camera->offset = vec2{w2,h2};
		e->camera->scale = vec2{ zoom,zoom };
		return e;
	}

	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{w,h};
		e->transform->setLocalPosition(vec2{ x,y });	
		return e;
	}

	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end()   { return entities.end(); }
};


