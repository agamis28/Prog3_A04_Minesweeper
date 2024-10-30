#include "grid.h"
#include "box.h"

// Grid Constructor 
// Constructors Default Settings
Grid::Grid() :
	currentRows{ 8 },
	currentColumns{ 8 },
	currentmines{ 10 },
	boxSize{ 5.0f }
{
}

// Constructor With Parameters
Grid::Grid(int currentRows, int currentColumns, int currentmines, float boxSize) :
	currentRows{ currentRows },
	currentColumns{ currentColumns },
	currentmines{ currentmines },
	boxSize{ boxSize } {
}

// Generates a grid using default grid members
void Grid::generateGrid() {

	// Clear out old boxes if there is any
	boxes.clear();

	for (int row = 0; row < currentRows; row++) {
		for (int column = 0; column < currentColumns; column++) {
			float x = column * boxSize;
			float y = row * boxSize;
			boxes.emplace_back(Box(glm::vec2(x, y), boxSize, false, 0));
		}
	}
}

// Uses parameters instead of default grid members
void Grid::generateGrid(int rows, int columns, int mines, float boxSize) {

	// Clear out old boxes if there is any
	boxes.clear();

	// Changing current rows to parameter giving rows
	currentRows = rows;
	currentColumns = columns;

	for (int row = 0; row < currentRows; row++) {
		for (int column = 0; column < currentColumns; column++) {
			float x = column * boxSize;
			float y = row * boxSize;
			boxes.emplace_back(Box(glm::vec2(x, y), boxSize, false, 0));
		}
	}
}

void Grid::displayGrid() {
	for (Box& box : boxes) {
		box.display();
	}
}