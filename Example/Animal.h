#pragma once

#include "Base.h"

using namespace base;

class Animal {
	ObjectPool<Transform>::iterator myTree;
	vec2 closestTree;
	vec2 myDest;
	vec2 myPosition;
public:
	bool foundTree;
	bool isTreeClose;
	float searchTimer;
	float moveSpeed;
	float eatSpeed;
	float weight;
	float scale;
	float walkRange;

	unsigned int *name;
	
	Animal(float moveSpd = 5.f, float eat = 3, float m_weight = 10,
		float m_scale = 1, float m_range = 3000, float sTimer = 0)
		: moveSpeed(moveSpd), eatSpeed(eat), weight(m_weight), scale(m_scale) ,
		walkRange(m_range), isTreeClose(false), foundTree(false), closestTree(vec2{ -INFINITY, -INFINITY }), myDest(vec2{-INFINITY, -INFINITY}) {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	vec2 getClosestTree() { return closestTree; }
	
	vec2 setclosestTree(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree) {
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();

		float oldDest = dist(animalPos, myDest);
		float newDest = dist(animalPos, treePos);

		if (newDest < oldDest)
		return dist(animalPos, treePos);
	}

	void setTarget(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree) {		

		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();
		
		float distance = dist(animalPos, treePos);

		isTreeClose = distance < walkRange ? true : false;

		//printf("istreeclose=%f \n", isTreeClose);

		//printf("found tree=%i , dist=%f, walkrange=%f \n", foundTree, distance, walkRange);

		//if (animal->getGlobalPosition() == myPosition)

		if (isTreeClose == true && foundTree == false) {
			foundTree = true;			
			myDest = tree->getGlobalPosition();
		}
		else 
			myDest = (animal->getGlobalPosition() + vec2{randomRange(-25,25), randomRange(-25,25)});

		printf("myDest = %f, %f \n",myDest.x, myDest.y);
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