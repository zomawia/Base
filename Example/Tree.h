#pragma once

class Tree {
public:
	float growSpeed;
	float scale;

	unsigned int *name;

	Tree() {};

	void setName(unsigned int *a_name) {
		name = a_name;
	}

	unsigned int *getName() const { return name; };
};