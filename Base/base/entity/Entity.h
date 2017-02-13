#pragma once

#include "../Components.h"
#include "../Data.h"

using namespace base;

class Entity
{
public:
	ObjectPool<Transform>::iterator transform;
	ObjectPool<Rigidbody>::iterator rigidbody;
	ObjectPool<Collider>::iterator  collider;
	ObjectPool<Lifetime>::iterator lifetime;
	ObjectPool<Sprite>::iterator sprite;
	ObjectPool<Camera>::iterator camera;

	~Entity()
	{
		transform.free();
		rigidbody.free();
		collider.free();
		sprite.free();
		lifetime.free();
		camera.free();
	}
};