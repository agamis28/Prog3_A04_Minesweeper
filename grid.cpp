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

// Creating boxes with correct and current rows and columns, place them into vector 'boxes'
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

// Set up mineCount of random mine locations on in range of boxes vector 
void Grid::setRandomMineLocations() {
	// Setting up randomization
	std::random_device randomDevice;
	std::mt19937 gen(randomDevice());
	std::uniform_int_distribution<> dis(0, boxes.size() - 1);

	// Clear old mine locations
	mineLocations.clear();

	// Randomly choose a unique location in grid boxes vector while the mineLocations vector is less than mineCount
	while (mineLocations.size() <= currentMines) {
		mineLocations.emplace_back(dis(gen));
	}

	// Loop through all boxes. If box is one of the mine locations set as a mine
	for (int i = 0; i < boxes.size(); i++) {
		for (int mineLocation : mineLocations) {
			if (i == mineLocation) {
				boxes[i].setMine();
			}
		}
	}
}


// Loops through all boxes. Checks all neighbours of box, checks in a grid fashion following rows and columns. If neighbours are a mine, add to number of neighbours.
// After going through all neighbours. Set number of neighbours to number of adjacent mines on box
void Grid::setNeighbours() {
	//std::cout << "Checking neighbors for box size: " << boxes.size() << "\n";
	//std::cout << "Boxes size: " << boxes.size() << ", Rows: " << currentRows << ", Columns: " << currentColumns;


	// Looping through all boxes to check neighbours
	for (int i = 0; i < boxes.size(); i++) {

		// Counter for number of mines found in neighbours
		// Increment when finding mine as neighbour
		int numberOfNeighbours = 0;

		//Top Neighbours
		// Check if in bounds of top of grid
		if (i - currentColumns >= 0) {
			//std::cout << "Mine index: " << i << " Top in bounds - boxes index: " << i - currentColumns << "\n";

			// Top
			if (boxes[i - currentColumns].getMine()) {
				numberOfNeighbours++;
			}

			// Top Right
			// Check if in bounds of right of grid
			if ((i + 1) % currentColumns != 0) {
				//std::cout << "Mine index: " << i << " Top Right in bounds - boxes index: " << i - currentColumns + 1 << "\n";

				if (boxes[i - currentColumns + 1].getMine()) {
					numberOfNeighbours++;
				}
			}

			// Top Left
			// Check if in bounds of left of grid
			if (i % currentColumns != 0) {
				//std::cout << "Mine index: " << i << " Top Left in bounds - boxes index: " << i - currentColumns - 1 << "\n";

				if (boxes[i - currentColumns - 1].getMine()) {
					numberOfNeighbours++;
				}
			}
		}

		// Right Neighbour
		// Check if in bounds of right of grid
		if ((i + 1) % currentColumns != 0) {
			//std::cout << "Mine index: " << i << " Right in bounds - boxes index: " << i + 1 << "\n";

			if (boxes[i + 1].getMine()) {
				numberOfNeighbours++;
			}
		}

		// Left Neighbour
		// Check if in bounds of left of grid
		if (i % currentColumns != 0) {
			//std::cout << "Mine index: " << i << " Left in bounds - boxes index: " << i - 1 << "\n";

			if (boxes[i - 1].getMine()) {
				numberOfNeighbours++;
			}
		}

		// Bottom Neighbours
		// Check if in bounds of bottom of grid
		if (i + currentColumns <= (boxes.size() - 1)) {
			//std::cout << "Mine index: " << i << " Bottom in bounds - boxes index: " << i + currentColumns << "\n";

			// Bottom
			if (boxes[i + currentColumns].getMine()) {
				numberOfNeighbours++;
			}

			// Bottom Right
			// Check if in bounds of right of grid
			if ((i + 1) % currentColumns != 0) {
				//std::cout << "Mine index: " << i << " Bottom right in bounds - boxes index: " << i + currentColumns + 1 << "\n";

				if (boxes[i + currentColumns + 1].getMine()) {
					numberOfNeighbours++;
				}
			}

			// Bottom Left
			// Check if in bounds of left of grid
			if (i % currentColumns != 0) {
				//std::cout << "Mine index: " << i << " Bottom left in bounds - boxes index: " << i + currentColumns - 1 << "\n";

				if (boxes[i + currentColumns - 1].getMine()) {
					numberOfNeighbours++;
				}
			}
		}

		// Setting number of neighbours with mines to the number of adjacent mines on box
		boxes[i].setAdjacent(numberOfNeighbours);

		// **vv DEBUG vv**

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

		//**^^ DEBUG ^^**
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
}

// Uses parameters instead of default grid members
void Grid::generateGrid(int rows, int columns, int mines, float boxSize) {

	// Clear out old boxes if there is any
	boxes.clear();

	// Changing current to parameter given values
	currentRows = rows;
	currentColumns = columns;
	currentMines = mines;

	// Clear out old boxes if there is any
	createBoxes();

	// Setting randomized boxes to mines
	setRandomMineLocations();

	// Set Neighbours
	setNeighbours();
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

// When box is clicked reveal box or many empty boxes
void Grid::revealClickedBox(float x, float y) {

	// Loop through all boxes and see which one the given mouse positions it is on
	for (size_t i = 0; i < boxes.size(); i++) {

		// If mouse is on box reveal the box if not empty
		if (boxes[i].containsPosition(x, y)) {
			// Only when clicking an empty, reveal other adjacent emptys
			if (boxes[i].getAdjacent() == 0 && boxes[i].getMine() == false) {
				revealEmptyNeighbours(i);
			}
			else {
				// When not revealed reveal
				if (!boxes[i].getRevealed()) {
					boxes[i].setReveal();

				}
			}
		}
	}
}

// Reveals all neighbouring empty boxes and the first number the chunk of empty boxes reveal
void Grid::revealEmptyNeighbours(int boxIndex) {
	//std::cout << "Box index: " << boxIndex << "\n";

	// If box is already revealed, end function, else reveal box
	if (boxes[boxIndex].getRevealed()) {
		return;
	}
	else {
		boxes[boxIndex].setReveal();
	}

	// If box has adjacent mines stop running reveal empty neighbours
	if (boxes[boxIndex].getAdjacent() > 0) {
		return;
	}

	// Top Neighbours
	// Check In bounds
	if (boxIndex - currentColumns >= 0) {
		// Top
		// Reveal it, and its neighbours
		revealEmptyNeighbours(boxIndex - currentColumns);

		// Top Right
		// Check In bounds
		if ((boxIndex + 1) % currentColumns != 0) {
			// Reveal it, and its neighbours
			revealEmptyNeighbours(boxIndex - currentColumns + 1);
		}

		// Top Left
		// Check In bounds
		if (boxIndex % currentColumns != 0) {
			// Reveal it, and its neighbours
			revealEmptyNeighbours(boxIndex - currentColumns - 1);
		}
	}

	// Right Neighbour
	// Check In bounds
	if ((boxIndex + 1) % currentColumns != 0) {
		// Check Adjacent
		// Reveal it, and its neighbours
		revealEmptyNeighbours(boxIndex + 1);
	}
	// Left Neighbour
	// Check In bounds
	if (boxIndex % currentColumns != 0) {
		// Check Adjacent
		// Reveal it, and its neighbours
		revealEmptyNeighbours(boxIndex - 1);
	}

	// Bottom Neighbours
	// Check In bounds
	if (boxIndex + currentColumns <= (boxes.size() - 1)) {
		// Bottom
		// Reveal it, and its neighbours
		revealEmptyNeighbours(boxIndex + currentColumns);

		// Bottom Right
		// Check In bounds
		if ((boxIndex + 1) % currentColumns != 0) {
			revealEmptyNeighbours(boxIndex + currentColumns + 1);
		}

		// Bottom Left
		// Check In bounds
		if (boxIndex % currentColumns != 0) {
			// Reveal it, and its neighbours
			revealEmptyNeighbours(boxIndex + currentColumns - 1);
		}
	}

}

// Runs 'display' function on all of box classes in boxes vector, to display whole grid
// Takes in a loaded image and font to give to box class
void Grid::displayGrid(ofImage& mineImage, ofTrueTypeFont& font) {
	for (Box& box : boxes) {
		box.display(mineImage, font);
	}
}