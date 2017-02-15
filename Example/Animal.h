#pragma once

#include "Base.h"

using namespace base;

class Animal {
	ObjectPool<Transform>::iterator myTree;
	vec2 myDest;
public:
	float moveSpeed;
	float eatSpeed;
	float weight;
	float scale;
	float walkRange;

	unsigned int *name;
	
	Animal(float moveSpd = 1.5f, float eat = 3, float m_weight = 10,
		float m_scale = 1, float m_range = 75) : moveSpeed(moveSpd), eatSpeed(eat),
		weight(m_weight), scale(m_scale) , walkRange(m_range) {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	vec2 closestTree(ObjectPool<Transform>::iterator tree, 
		ObjectPool<Transform>::iterator animal) {
		bool isTreeClose = dist(animal->getGlobalPosition(), tree->getGlobalPosition()) < walkRange;
		
		if (isTreeClose) {
			myDest = tree->getGlobalPosition();
			return myDest;
		}
		else return myDest = (animal->getGlobalPosition() + vec2{randomRange(-10,10), randomRange(-10,10)});
	}

	void gotoTree(ObjectPool<Transform>::iterator animal, float dt) {
		vec2 currentPos = animal->getGlobalPosition();
		float t = 0;
		while (t < 1) {
			t += dt * moveSpeed;
			animal->setGlobalPosition(lerp(currentPos, myDest, dt));
		}
	}

	bool isTreeTaken() {

	}

	bool canEatFromTree() {

	}

	void eatTree() {

	}

	unsigned int *getName() const { return name; };
};