#pragma once

#include "Base.h"

using namespace base;

class Animal {	
	ObjectPool<Transform>::iterator myTree;
	
	vec2 closestTree;
	vec2 myDest;
	vec2 myPosition;
public:
	enum aState
	{
		WANDER, SEARCH, EATING, 
	};
	bool foundTree;
	float searchTimer;
	float moveSpeed;
	float eatSpeed;
	float weight;
	float scale;
	float walkRange;

	unsigned int *name;
	
	Animal(float moveSpd = 10.f, float eat = 3, float m_weight = 10,
		float m_scale = 1, float m_range = 200, float sTimer = 0)
		: moveSpeed(moveSpd), eatSpeed(eat), weight(m_weight), scale(m_scale) ,
		walkRange(m_range), foundTree(false), myDest(vec2{NULL,NULL}) {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	bool isTreeClose(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree){
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();		
		float distance = dist(animalPos, treePos);		
		return distance < walkRange ? true : false;
	}

	vec2 getClosestTree() { return closestTree; }
	
	void setRandomDest(const ObjectPool<Transform>::iterator &animal) {
		myDest = (animal->getGlobalPosition() + vec2{ randomRange(-20,20), randomRange(-20,20) });
	}

	void setClosestTree(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree) {
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();

		float oldDest = dist(animalPos, myDest);
		float newDest = dist(animalPos, treePos);

		if (newDest < oldDest) closestTree = newDest;
	}

	bool isAtDestination(const ObjectPool<Transform>::iterator &animal) {
		vec2 animalPos = animal->getGlobalPosition();
		float closeEnough = dist(animalPos, myDest);		
		
		if (animalPos == myDest || closeEnough < 10.f) {
			printf("I am at my destination!\n");
			return true;
		}
		else return false;
	}

	void setTarget(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree) {
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();

		if (myDest.x == NULL || myDest.y == NULL) {
			setRandomDest(animal);
		}

		if (isTreeClose(animal, tree) == true && foundTree == false && isAtDestination(animal) == false ) {
			setClosestTree(animal, tree);
			foundTree = true;
			myDest = closestTree;
			printf("1. myDest = %f, %f \n",myDest.x, myDest.y);			
		}
		
		if(isTreeClose(animal, tree) == false && isAtDestination(animal) == false ){
			setRandomDest(animal);
			printf("2. myDest = %f, %f \n",myDest.x, myDest.y);
		}

		if (isAtDestination(animal) == true) {
			setRandomDest(animal);
		}
	}

	void gotoDest(ObjectPool<Transform>::iterator &animal, float dt) {		
		if (isAtDestination(animal) == false ) {
			vec2 currentPos = animal->getGlobalPosition();
			float t = 0;
			while (t < 1) {
				t += dt / moveSpeed;
				animal->setGlobalPosition(lerp(currentPos, myDest, t));
				printf("globalpos = %f, %f\n", animal->getGlobalPosition().x, animal->getGlobalPosition().y);
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