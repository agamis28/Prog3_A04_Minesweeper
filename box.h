#pragma once

#include "ofMain.h"

class Box {
	// Defining box types enum
	enum BoxType {
		Empty,
		Number,
		Mine
	};

	float boxSize;
	BoxType boxType;
	int numberOfAdjacentMines = 0;
	bool flagged;
	bool revealed;


public:
	// Constructor
	Box(float boxSize, BoxType boxType, int numberOfAdjacentMines)
		: boxSize{ boxSize }, boxType{ boxType }, numberOfAdjacentMines{ numberOfAdjacentMines } {}

	void toggleFlag();
	void display();
};
