#pragma once

#include "ofMain.h"
#include "Box.h"

class Grid {

	// Private Members
	int currentRows;
	int currentColumns;
	int currentmines;
	float boxSize;

public:
	// Public Members
	std::vector<Box>boxes;

	// Default Constructor
	Grid();
	// Constructor
	Grid(int, int, int, float);

	// Functions
	void generateGrid(int, int, int, float);
	void displayGrid();
};
