#include "box.h"

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

void Box::setColor(ofColor newColor) {
	boxInnerColor = newColor;
}

// Check if the box contains a position
bool Box::containsPosition(float x, float y) {
	return x >= position.x && x <= position.x + boxSize && y >= position.y && y <= position.y + boxSize; // Returns true if position param is within the bounds of box.
}

void Box::display(ofImage& mineImage) {

	// When not
	if (!revealed) {
		ofSetColor(255, 255, 255);
		ofDrawRectangle(position.x, position.y, boxSize, boxSize);

		ofSetColor(0, 0, 0);
		ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));

		ofSetColor(boxInnerColor);
		ofDrawRectangle(position.x + (boxSize * 0.2f), position.y + (boxSize * 0.2f), boxSize - (boxSize * 0.4f), boxSize - (boxSize * 0.4f));
	}
	else {
		// If mine display mine, else display number of adjacent mines, if no adjacent mines show empty
		if (isMine) {
			// Draw Bomb image when is mine and revealed
			if (mineImage.isAllocated()) {
				ofSetColor(255);
				mineImage.draw(position.x, position.y, boxSize - 1, (boxSize - 1) * 0.94);
			}
		}
		else {
			// When there is adjacent mines display a number
			if (numberOfAdjacentMines != 0) {
				// display adjacent mines
			}
		}
	}
}
