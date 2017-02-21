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
		STABLE, MOVING, EATING 
	};
	aState animalState;
	bool atTree;
	bool goingRandom;
	float searchTimer;
	float moveSpeed;
	float eatSpeed;
	float weight;
	float scale;
	float walkRange;

	unsigned int *name;
	
	Animal(float moveSpd = 10.f, float eat = 3, float m_weight = 10,
		float m_scale = 1, float m_range = 2500, float sTimer = 0)
		: moveSpeed(moveSpd), eatSpeed(eat), weight(m_weight), scale(m_scale) ,
		walkRange(m_range), atTree(false), myDest(vec2{NULL,NULL}), goingRandom(false),
		animalState(STABLE) {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	bool isTreeClose(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree){
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();		
		float distance = dist(animalPos, treePos);		
		return distance < walkRange ? true : false;
	}

	//vec2 getClosestTree() { return closestTree; }
	
	void setRandomDest(const ObjectPool<Transform>::iterator &animal) {
		animalState = MOVING;
		goingRandom = true;
		myDest = (animal->getGlobalPosition() + vec2{ randomRange(-150,150), randomRange(-150,150) });
	}

	vec2 getClosestTree(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree) {
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();

		float oldDest = dist(animalPos, myDest);
		float newDest = dist(animalPos, treePos);

		if (newDest < oldDest || goingRandom == true) {
			goingRandom = false;
			return newDest;
		}
		else return oldDest;
	}

	bool isAtDestination(const ObjectPool<Transform>::iterator &animal) {
		vec2 animalPos = animal->getGlobalPosition();
		float closeEnough = dist(animalPos, myDest);		
		
		//printf("%f\n", closeEnough);

		if (animalPos == myDest || closeEnough < 5.f) {
			//printf("I am at my destination!\n");
			animalState = STABLE;
			return true;
		}
		else return false;
	}

	void setTarget(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree) {
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();

		if (myDest.x == NULL && myDest.y == NULL) {
			setRandomDest(animal);
			printf("Random dest for starting\n");
		}

		if (isAtDestination(animal) == false) {
			if (isTreeClose(animal, tree) == true) {
				myDest = getClosestTree(animal, tree);
				//atTree = true;
				printf("Near a tree. Going = %f, %f \n", myDest.x, myDest.y);
			}
			
			else if (isTreeClose(animal, tree) == false && animalState == STABLE) {
				setRandomDest(animal);
				printf("Not at dest. Going random -- %f, %f \n", myDest.x, myDest.y);
			}
		}
		
		else if (isAtDestination(animal) == true){
			if (atTree==true) {
				//check if tree available
				printf("Im at a tree\n");
			}
			if (atTree==false){
				setRandomDest(animal);
				printf("At destination cant find tree. Going random -- %f, %f \n", myDest.x, myDest.y);
			}				
		}
	}

	void gotoDest(ObjectPool<Transform>::iterator &animal, float dt) {		
		if (isAtDestination(animal) == false ) {
			vec2 currentDir = (myDest - animal->getGlobalPosition()).normal()*moveSpeed;
			vec2 currentPos = animal->getGlobalPosition();
			//float t = 0;
			//while (t < 1)
			{
				//float t = dt /(moveSpeed);
				animal->setGlobalPosition(lerp(currentPos, currentPos + currentDir, dt));
				//printf("globalpos = %f, %f\n", animal->getGlobalPosition().x, animal->getGlobalPosition().y);
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