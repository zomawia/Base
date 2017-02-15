#pragma once

#include "Base.h"

using namespace base;

class Animal {
public:
	float moveSpeed;
	float eatSpeed;
	float weight;
	float scale;

	unsigned int *name;
	
	Animal(float move = 2, float eat = 3, float m_weight = 10,
		float m_scale = 1) : moveSpeed(move), eatSpeed(eat),
		weight(m_weight), scale(m_scale) {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	bool isTreeClose(Transform *tree, Transform *animal) {
		vec2 findVec = animal->getGlobalPosition() - tree->getGlobalPosition();
		return false;
	}

	void gotoTree(Transform *tree, Transform *animal) {

	}

	bool canEatFromTree() {

	}

	void eatTree() {

	}

	unsigned int *getName() const { return name; };
};