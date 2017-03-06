#pragma once

#include "base.h"

using namespace base;

class Tree {
	bool isPaired;
public:	
	
	float growSpeed;
	float scale;

	unsigned int *name;

	Tree() : growSpeed(2), scale(1), isPaired(false)  {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}
	void setIsPaired(bool ok) { isPaired = ok; }
	bool getIsPaired() { return isPaired; }

	unsigned int *getName() const { return name; };
};