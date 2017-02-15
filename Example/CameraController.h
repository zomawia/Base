#pragma once

#include "Base.h"

class CameraController
{

public:
	float speed = 5;

	void poll(base::Transform *T, base::Rigidbody *rb)
	{
		rb->drag = 25;
		
		if (sfw::getKey('W')) {
			rb->addImpulse(T->getGlobalUp() * speed);
			rb->drag = 0;
		}

		if (sfw::getKey('A')) {
			rb->addImpulse(T->getGlobalUp().left() * speed);
			rb->drag = 0;
		}

		if (sfw::getKey('D')) {
			rb->addImpulse(T->getGlobalUp().right() * speed);
			rb->drag = 0;
		}

		if (sfw::getKey('S')) {
			rb->addImpulse(T->getGlobalUp() * -speed);
			rb->drag = 0;
		}
		
		//bounds
		if (T->getGlobalPosition().y < 0) T->setGlobalPosition({ T->getGlobalPosition().x, 0 });
		if (T->getGlobalPosition().y > 300) T->setGlobalPosition({ T->getGlobalPosition().x, 300 });
		if (T->getGlobalPosition().x > 1600) T->setGlobalPosition({ 1600, T->getGlobalPosition().y });
		if (T->getGlobalPosition().x < 0) T->setGlobalPosition({ 0, T->getGlobalPosition().y });
	}
};