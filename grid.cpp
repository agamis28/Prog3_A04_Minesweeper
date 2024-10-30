#include "grid.h"
#include "box.h"
#include "iostream"

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

// Set up mineCount of random mine locations on in range of boxes vector 
void Grid::setRandomMineLocations(int mineCount) {
	// Setting up randomization
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<> dis(0, boxes.size() - 1);

	// Clear old mine locations
	mineLocations.clear();

	// Randomly choose a unique location in grid boxes vector while the mineLocations vector is less than mineCount
	while (mineLocations.size() < mineCount) {
		mineLocations.emplace_back(dis(gen));
	}

	for (int i = 0; i < boxes.size(); i++) {
		for (int mineLocation : mineLocations) {
			if (i == mineLocation) {
				boxes[i].setMine();
			}
		}
	}
}

// Creating boxes with correct rows and columns
void Grid::createBoxes() {
	for (int row = 0; row < currentRows; row++) {
		for (int column = 0; column < currentColumns; column++) {
			float x = column * boxSize;
			float y = row * boxSize;
			boxes.emplace_back(Box(glm::vec2(x, y), boxSize, false, 0));
		}
	}
}

// Generates a grid using default grid members
void Grid::generateGrid() {

	// Clear out old boxes if there is any
	boxes.clear();

	createBoxes();
}

// Uses parameters instead of default grid members
void Grid::generateGrid(int rows, int columns, int mines, float boxSize) {

	// Clear out old boxes if there is any
	boxes.clear();

	// Changing current rows to parameter giving rows
	currentRows = rows;
	currentColumns = columns;

	createBoxes();

	setRandomMineLocations(mines);
}

// Check if box on grid is hovered. If it is hovered or not change colors
void Grid::checkBoxHovered(float x, float y) {
	for (Box& box : boxes) {
		if (box.containsPosition(x, y)) {
			box.setColor(box.boxHoveredColor);
		}
		else {
			box.setColor(box.boxDefaultColor);
		}
	}
}

void Grid::displayGrid(ofImage& mineImage) {
	for (Box& box : boxes) {
		box.display(mineImage);
	}
}