#pragma once

#include "Base.h"

using namespace base;

class Animal {
	ObjectPool<Transform>::iterator myTree;
	vec2 myDest;
public:
	bool foundTree;
	float searchTimer;
	float moveSpeed;
	float eatSpeed;
	float weight;
	float scale;
	float walkRange;

	unsigned int *name;
	
	Animal(float moveSpd = 5.f, float eat = 3, float m_weight = 10,
		float m_scale = 1, float m_range = 2000.f, float sTimer = 0,
		bool fTree = false) : moveSpeed(moveSpd), eatSpeed(eat),
		weight(m_weight), scale(m_scale) , walkRange(m_range) {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	vec2 closestTree(ObjectPool<Transform>::iterator tree, 
		ObjectPool<Transform>::iterator animal) {
		//printf("searching... \n");
		float distance = dist(animal->getGlobalPosition(), tree->getGlobalPosition());
		bool isTreeClose = distance < walkRange;
		
		if (isTreeClose == true && foundTree == false) {
			foundTree = true;
			printf("found tree=&i , dist=%f \n", foundTree, distance);
			myDest = tree->getGlobalPosition();
			return myDest;
		}
		else return myDest = (animal->getGlobalPosition() + vec2{randomRange(-10,10), randomRange(-10,10)});
	}

	void gotoTree(ObjectPool<Transform>::iterator animal, float dt) {
		if (foundTree = true) {
			vec2 currentPos = animal->getGlobalPosition();
			float t = 0;
			while (t < 1) {
				t += dt / 6.f;
				animal->setGlobalPosition(lerp(currentPos, myDest, dt));
			}
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