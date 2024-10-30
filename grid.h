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
	Grid(int currentRows, int currentColumns, int currentMines, float boxSize);

	// Functions
	void generateGrid();
	void generateGrid(int rows, int columns, int mines, float boxSize);
	void displayGrid();
};