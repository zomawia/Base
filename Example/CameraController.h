#pragma once

#include "Base.h"

class CameraController
{

public:
	float speed = 20;

	void poll(base::Transform *T, base::Rigidbody *rb, float dt)
	{
		if (sfw::getKey('W'))
			rb->addForce(T->getGlobalUp() * speed);
		
		if (sfw::getKey('A'))
			rb->addForce(T->getGlobalUp().right() * speed);

		if (sfw::getKey('D'))
			rb->addForce(T->getGlobalUp().left() * speed);

		if (sfw::getKey('S'))
			rb->addForce(T->getGlobalUp() * -speed);
	}
};