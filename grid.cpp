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

	// Set Neighbours
	setNeighbours();

	for (Box& box : boxes) {
		box.setReveal(); // TO BE REMOVED
	}
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

	// Set Neighbours
	setNeighbours(); //!!!!!! CAUSES CRASHING // NEED TO BE FIXED

	for (Box& box : boxes) {
		box.setReveal(); // TO BE REMOVED
	}
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
	std::cout << "Checking neighbors for box size: " << boxes.size() << "\n";

	for (int i = 0; i < boxes.size(); i++) {
		// Check out of bounds conditions

		int numberOfNeighbours = 0;

		if (i < boxes.size()) {
			// Access boxes[i]
		}

		//std::cout << "Boxes size: " << boxes.size() << ", Rows: " << currentRows << ", Columns: " << currentColumns << std::endl;

		// Check if neighbouring boxes are mines, if is add to number of neighbours

		// Check if in bounds if in bounds: 
		// Check if mine, if it is a mine, increment number of mines

		//Top Neighbours
		if (i - currentColumns >= 0) {
			std::cout << "Mine index: " << i << " Top in bounds - boxes index: " << i - currentColumns << "\n";

			// Top
			if (boxes[i - currentColumns].isMine) {
				numberOfNeighbours++;
			}

			// Top Right
			if ((i + 1) % currentColumns != 0) {
				std::cout << "Mine index: " << i << " Top Right in bounds - boxes index: " << i - currentColumns + 1 << "\n";

				if (boxes[i - currentColumns + 1].isMine) {
					numberOfNeighbours++;
				}
			}

			// Top Left
			if (i % currentColumns != 0) {
				std::cout << "Mine index: " << i << " Top Left in bounds - boxes index: " << i - currentColumns - 1 << "\n";

				if (boxes[i - currentColumns - 1].isMine) {
					numberOfNeighbours++;
				}
			}
		}

		// Mid Neighbours
		// Right Neighbour
		if ((i + 1) % currentColumns != 0) {
			std::cout << "Mine index: " << i << " Right in bounds - boxes index: " << i + 1 << "\n";

			if (boxes[i + 1].isMine) {
				numberOfNeighbours++;
			}
		}

		// Left Neighbour
		if (i % currentColumns != 0) {
			std::cout << "Mine index: " << i << " Left in bounds - boxes index: " << i - 1 << "\n";

			if (boxes[i - 1].isMine) {
				numberOfNeighbours++;
			}
		}

		// Bottom Neighbours
		if (i + currentColumns <= (boxes.size() - 1)) {
			std::cout << "Mine index: " << i << " Bottom in bounds - boxes index: " << i + currentColumns << "\n";

			// Bottom
			if (boxes[i + currentColumns].isMine) {
				numberOfNeighbours++;
			}

			// Bottom Right
			if ((i + 1) % currentColumns != 0) {
				std::cout << "Mine index: " << i << " Bottom right in bounds - boxes index: " << i + currentColumns + 1 << "\n";

				if (boxes[i + currentColumns + 1].isMine) {
					numberOfNeighbours++;
				}
			}

			// Bottom Left
			if (i % currentColumns != 0) {
				std::cout << "Mine index: " << i << " Bottom left in bounds - boxes index: " << i + currentColumns - 1 << "\n";

				if (boxes[i + currentColumns - 1].isMine) {
					numberOfNeighbours++;
				}
			}
		}

		boxes[i].setAdjacent(numberOfNeighbours);

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

void Grid::displayGrid(ofImage& mineImage, ofTrueTypeFont& font) {
	for (Box& box : boxes) {
		box.display(mineImage, font);
	}
}