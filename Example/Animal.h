#pragma once

#include "Base.h"
#include "Tree.h"

using namespace base;

class Animal {	
	//ObjectPool<Tree>::iterator myTree;
	
	vec2 closestTree;
	vec2 myDest;
	vec2 myPosition;
public:
	enum aState
	{
		STABLE, MOVING, EATING, PROBE 
	};
	aState animalState;
	int dir;
	bool atTree;
	bool goingRandom;
	float searchTimer;
	float moveSpeed;
	float eatSpeed;
	float weight;
	vec2 scale;
	float walkRange;

	unsigned int *name;
	
	Animal(float moveSpd = 50, float eat = .75f, float m_weight = 10,
		vec2 m_scale = { 30,20 }, float m_range = 300, float sTimer = 0)
		: moveSpeed(moveSpd), eatSpeed(eat), weight(m_weight), scale(m_scale) ,
		walkRange(m_range), atTree(false), myDest(vec2{NULL,NULL}), goingRandom(false),
		animalState(STABLE), dir(0) {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	char* getStateToChar() { 
		char* retval;

		switch (animalState) {
		case EATING:
			retval = "EATING";
			break;
		case MOVING:
			retval = "MOVING";
			break;
		case PROBE:
			retval = "PROBE";
			break;		
		case STABLE:
		default:
			retval = "STABLE";
			break;
		}
							
		return retval; 
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
			return treePos;
		}
		else return myDest;
	}

	bool isAtDestination(const ObjectPool<Transform>::iterator &animal) {
		vec2 animalPos = animal->getGlobalPosition();
		float closeEnough = dist(animalPos, myDest);		
		
		//printf("%f\n", closeEnough);

		if (atTree == false && (animalPos == myDest || closeEnough < 10.f) ) {
			printf("I am at my destination!\n");
			animalState = STABLE;
			return true;
		}
		else return false;
	}

	bool isAtTree(const ObjectPool<Transform>::iterator &animal,
		const ObjectPool<Transform>::iterator &tree) {

		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();
		float closeEnough = dist(animalPos, treePos);

		if (animalPos == treePos || closeEnough < 10.f ) {
			atTree = true;
			animalState = PROBE;
			return true;
		}
		else return false;
	}

	bool canEatFromTree(ObjectPool<Tree>::iterator &tree) {
		if (tree->getIsPaired() == false) {
			tree->setIsPaired(true);
			return true;
		}
		else return false;
	}

	//void setMyTree(const ObjectPool<Tree>::iterator &tree) {
	//	myTree = tree;
	//}

	void setTarget(const ObjectPool<Transform>::iterator &animal, const ObjectPool<Transform>::iterator &tree) {
		vec2 animalPos = animal->getGlobalPosition();
		vec2 treePos = tree->getGlobalPosition();

		if (myDest.x == NULL && myDest.y == NULL) {
			setRandomDest(animal);
			printf("Random dest for starting\n");
		}
		
		if (isAtDestination(animal) == false) 
		{
			if (isTreeClose(animal, tree) == true && (animalState == MOVING || animalState == STABLE)) {
				myDest = getClosestTree(animal, tree);
				//atTree = true;
				printf("Near a tree. Going = %f, %f \n", myDest.x, myDest.y);
			}
			
			else if (isTreeClose(animal, tree) == false && animalState == STABLE) {
				setRandomDest(animal);
				printf("Not at dest. Going random -- %f, %f \n", myDest.x, myDest.y);
			}
		}
		
		else if (isAtDestination(animal) == true)
		{
			if (isAtTree(animal, tree) == true) {
				//check if tree available
				printf("Im at a tree\n");
				animalState = PROBE;
			}
			else if (isAtTree(animal, tree) == false && animalState == STABLE){
				setRandomDest(animal);
				printf("At destination cant find tree. Going random -- %f, %f \n", myDest.x, myDest.y);
			}				
		}
	}

	void gotoDest(ObjectPool<Transform>::iterator &animal, float dt) {		
		if (isAtDestination(animal) == false ) {
			vec2 currentDir = (myDest - animal->getGlobalPosition()).normal()*moveSpeed;
			vec2 currentPos = animal->getGlobalPosition();
			
			dir = animal->getDirection(currentDir);
			animal->setGlobalPosition(lerp(currentPos, currentPos + currentDir, dt));

		}
	}

	void growAnimal(ObjectPool<Transform>::iterator &transform, vec2 scale) {
		transform->setLocalScale(scale);
	}

	void processEating(ObjectPool<Transform>::iterator &animal, ObjectPool<Tree>::iterator &tree, float dt) {
		//check tree validity
		if (animalState == PROBE && canEatFromTree(tree) == true) {
			//ok to eat, start eating
			printf("I can eat!\n");
			animalState = EATING;
		}

		if (animalState == EATING) {			
			// grow
			scale += dt * eatSpeed;
			growAnimal(animal, scale);
			// grow tree
			//tree->scale;

			printf("I am eating now.\n");

		}
	}

	bool shouldThisAnimaBeEuthanisedOrBePutDeathPermanently(){
		if (scale.x > 225) return true;
		else return false;
	}

	void canLayEgg() {}
	void LayEgg() {}

	unsigned int *getName() const { return name; };
};