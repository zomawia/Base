#pragma once

#include "Base.h"

#include "PlayerController.h"
#include "CameraController.h"
#include "Animal.h"
#include "Tree.h"
#include "Button.h"

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
	ObjectPool<CameraController>::iterator cameraControllers;

	ObjectPool<Animal>::iterator animal;
	ObjectPool<Tree>::iterator tree;
	ObjectPool<Button>::iterator button;

	// example of a component in this project
	ObjectPool<PlayerController>::iterator controller;

	void onFree()
	{
		transform.free();
		rigidbody.free();
		collider.free();
		lifetime.free();
		sprite.free();
		camera.free();
		text.free();
		
		animal.free();
		tree.free();

		controller.free();
		cameraControllers.free();
	}
};