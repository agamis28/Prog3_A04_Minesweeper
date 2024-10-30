#pragma once

#include "ofMain.h"
#include "Box.h"

#include <random>

class Grid {

	// Private Members In Constructor
	int currentRows;
	int currentColumns;
	int currentmines;
	float boxSize;

	// Setting mine location vector
	std::vector<int>mineLocations;

public:
	// Public Members
	std::vector<Box>boxes;

	// Default Constructor
	Grid();
	// Constructor
	Grid(int currentRows, int currentColumns, int currentMines, float boxSize);

	// Functions
	void setRandomMineLocations(int gridSize, int mineCount);
	void createBoxes();
	void generateGrid();
	void generateGrid(int rows, int columns, int mines, float boxSize);
	void checkBoxHovered(float mousePositionX, float mousePositionY);
	void displayGrid(ofImage mineImage);
};