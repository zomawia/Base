#pragma once

#include "base.h"

using namespace base;

class Tree {
	bool isPaired;
public:	
	//ObjectPool<Animal>::iterator myAnimal;
	
	float growSpeed;
	float scale;

	unsigned int *name;

	Tree() : growSpeed(1), scale(1), isPaired(false)  {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	bool getIsPaired() { return isPaired; }

	//void setMyAnimal(ObjectPool<Animal>::iterator animal) {
	//	myAnimal = animal;
	//}

	unsigned int *getName() const { return name; };
};