#include "grid.h"
#include "box.h"
#include "iostream"

// Grid Constructor 
// Constructors Default Settings
Grid::Grid() :
	currentRows{ 8 },
	currentColumns{ 8 },
	currentMines{ 10 },
	boxSize{ 5.0f }
{
}

// Constructor With Parameters
Grid::Grid(int currentRows, int currentColumns, int currentMines, float boxSize) :
	currentRows{ currentRows },
	currentColumns{ currentColumns },
	currentMines{ currentMines },
	boxSize{ boxSize } {
}

// Set up mineCount of random mine locations on in range of boxes vector 
void Grid::setRandomMineLocations() {
	// Setting up randomization
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<> dis(0, boxes.size() - 1);

	// Clear old mine locations
	mineLocations.clear();

	// Randomly choose a unique location in grid boxes vector while the mineLocations vector is less than mineCount
	while (mineLocations.size() < currentMines) {
		mineLocations.emplace_back(dis(gen));
	}

	for (int i = 0; i < boxes.size(); i++) {
		for (int mineLocation : mineLocations) {
			if (i == mineLocation) {
				boxes[i].setMine();
				boxes[i].setReveal(); // REMOVE
			}
		}
	}
}

// Creating boxes with correct rows and columns
void Grid::createBoxes() {
	for (int row = 0; row < currentRows; row++) {
		for (int column = 0; column < currentColumns; column++) {

			// Set position based on which row and column. Also setting to center of screen.
			float x = column * boxSize + (ofGetWidth() / 2 - currentColumns / 2 * boxSize);
			float y = row * boxSize + (ofGetHeight() / 2 - currentRows / 2 * boxSize);
			// Adding to boxes vector
			boxes.emplace_back(Box(glm::vec2(x, y), boxSize, false, 0));
		}
	}
}

// Generates a grid using default grid members
void Grid::generateGrid() {

	// Clear out old boxes if there is any
	boxes.clear();

	// Creating boxes for rows and columns
	createBoxes();

	// Setting randomized boxes to mines
	setRandomMineLocations();
}

// Uses parameters instead of default grid members
void Grid::generateGrid(int rows, int columns, int mines, float boxSize) {

	// Clear out old boxes if there is any
	boxes.clear();

	// Changing current rows to parameter giving rows
	currentRows = rows;
	currentColumns = columns;
	currentMines = mines;

	// Clear out old boxes if there is any
	createBoxes();

	// Setting randomized boxes to mines
	setRandomMineLocations();
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

void Grid::setNeighbours() {
	for (int i = 0; i < boxes.size(); i++) {
		// Check out of bounds conditions

		int numberOfNeighbours = 0;

		// Check if neighbouring boxes are mines, if is add to number of neighbours

		// Check if in bounds if in bounds: 
		// Check if mine, if it is a mine, increment number of mines

		std::cout << "Index: " << i << "\n";

		// Top Neighbours
		if (i - currentRows >= 0) {
			// Top
			if (boxes[i - currentRows].isMine) {
				numberOfNeighbours++;
				std::cout << "Top Incremented" << "\n";
			}

			// Top Right
			if ((i + 1) % currentColumns != 0) {
				if (boxes[i - currentRows + 1].isMine) {
					numberOfNeighbours++;
					std::cout << "Top RIght Incremented" << "\n";
				}
			}

			// Top Left
			if (i % currentColumns != 0) {
				if (boxes[i - currentRows - 1].isMine) {
					numberOfNeighbours++;
					std::cout << "Top Left Incremented" << "\n";
				}
			}
		}

		// Mid Neighbours
		// Right Neighbour
		if ((i + 1) % currentColumns != 0) {
			if (boxes[i + 1].isMine) {
				numberOfNeighbours++;
				std::cout << "Mid Right Incremented" << "\n";
			}
		}

		// Left Neighbour
		if (i % currentColumns != 0) {
			if (boxes[i - 1].isMine) {
				numberOfNeighbours++;
				std::cout << "Mid Left Incremented" << "\n";
			}
		}

		// Bottom Neighbours
		if (i + currentRows <= (boxes.size() - 1)) {
			// Bottom
			if (boxes[i + currentRows].isMine) {
				numberOfNeighbours++;
				std::cout << "Bottom Incremented" << "\n";
			}

			// Bottom Right
			if ((i + 1) % currentColumns != 0) {
				if (boxes[i + currentRows + 1].isMine) {
					numberOfNeighbours++;
					std::cout << "Bottom Right Incremented" << "\n";
				}
			}

			// Bottom Left
			if (i % currentColumns != 0) {
				if (boxes[i + currentRows - 1].isMine) {
					numberOfNeighbours++;
					std::cout << "Bottom Left Incremented" << "\n";
				}
			}
		}

		//std::cout << "Mine index: " << i << " # of Neighbours: " << numberOfNeighbours << "\n";

		// Out of bounds debug
		//std::cout << "Mine index: " << i << "\n";

		//// Left
		//if (i % currentColumns != 0) {
		//	std::cout << "In of bounds left" << "\n";;
		//}
		//else {
		//	std::cout << "Out of bounds left" << "\n";;
		//}

		//// Top
		//if (i - currentRows >= 0) {
		//	std::cout << "In of bounds top" << "\n";;
		//}
		//else {
		//	std::cout << "Out of bounds top" << "\n";;
		//}

		//// Bottom
		//if (i + currentRows <= (boxes.size() - 1)) {
		//	std::cout << "In of bounds bottom" << "\n";;
		//}
		//else {
		//	std::cout << "Out of bounds bottom" << "\n";;
		//}

		//// Right
		//if ((i + 1) % currentColumns != 0) {
		//	std::cout << "In of bounds right" << "\n";;
		//}
		//else {
		//	std::cout << "Out of bounds right" << "\n";;
		//}

	}
}

void Grid::displayGrid(ofImage& mineImage) {
	for (Box& box : boxes) {
		box.display(mineImage);
	}
}