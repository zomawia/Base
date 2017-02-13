#pragma once

#include "../Base/Base.h"

#include "PlayerController.h"

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
	ObjectPool<Text>::iterator text;

	ObjectPool<PlayerController>::iterator controller;

	~Entity()
	{
		transform.free();
		rigidbody.free();
		collider.free();
		sprite.free();
		lifetime.free();
		camera.free();
		text.free();
		controller.free();
	}
};