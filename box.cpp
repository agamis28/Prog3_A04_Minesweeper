#include "box.h"
#include <string>

// Box Constructor 
// Constructors Default Settings
Box::Box() : position{ 0, 0 },
boxSize{ 10.0f },
isMine{ false },
numberOfAdjacentMines{ 0 },
flagged{ false },
revealed{ false }
{
}

// Constructor With Parameters
Box::Box(glm::vec2 position, float boxSize, bool isMine, int numberOfAdjacentMines, bool flagged, bool revealed)
	: position{ position }, boxSize{
	boxSize
	}, isMine{ isMine }, numberOfAdjacentMines{ numberOfAdjacentMines }, flagged{ false }, revealed{ false } {}

void Box::toggleFlag() {

}

void Box::setMine() {
	isMine = true;
}

bool Box::getMine() {
	return isMine;
}


void Box::setAdjacent(int numberOfNeighbours) {
	numberOfAdjacentMines = numberOfNeighbours;
}

int Box::getAdjacent() {
	return numberOfAdjacentMines;
}


void Box::setReveal() {
	revealed = true;
}

bool Box::getRevealed() {
	return revealed;
}


void Box::setColor(ofColor newColor) {
	boxInnerColor = newColor;
}

// Check if the box contains a position
bool Box::containsPosition(float x, float y) {
	return x >= position.x && x <= position.x + boxSize && y >= position.y && y <= position.y + boxSize; // Returns true if position param is within the bounds of box.
}

void Box::display(ofImage& mineImage, ofTrueTypeFont& font) {

	// When not
	if (!revealed) {
		ofSetColor(0);
		ofDrawRectangle(position.x, position.y, boxSize, boxSize);

		ofSetColor(255);
		ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));

		ofSetColor(boxInnerColor);
		ofDrawRectangle(position.x + (boxSize * 0.2f), position.y + (boxSize * 0.2f), boxSize - (boxSize * 0.4f), boxSize - (boxSize * 0.4f));
	}
	else {
		// If mine display mine, else display number of adjacent mines, if no adjacent mines show empty
		if (isMine) {
			ofSetColor(0);
			ofDrawRectangle(position.x, position.y, boxSize, boxSize);

			ofSetColor(255);
			ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));
			// Draw Bomb image when is mine and revealed
			if (mineImage.isAllocated()) {
				ofSetColor(255);
				mineImage.draw(position.x + (boxSize / 8), position.y + (boxSize / 6), boxSize * 0.70f, (boxSize * 0.70f) * 0.94);
			}
		}
		else {
			ofSetColor(0);
			ofDrawRectangle(position.x, position.y, boxSize, boxSize);

			ofSetColor(255);
			ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));
			// When there is adjacent mines display a number
			if (numberOfAdjacentMines != 0) {
				// display adjacent mines
				ofSetColor(0);
				ofPushMatrix();
				font.drawString(std::to_string(numberOfAdjacentMines), position.x + (boxSize / 3), position.y + (boxSize / 1.25f));
			}
		}
	}
}
