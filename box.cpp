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

void Box::display() {
	if (!revealed) {
		ofSetColor(255, 255, 255);
		ofDrawRectangle(position.x, position.y, boxSize, boxSize);

		ofSetColor(0, 0, 0);
		ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));

		ofSetColor(150, 150, 150);
		ofDrawRectangle(position.x + (boxSize * 0.2f), position.y + (boxSize * 0.2f), boxSize - (boxSize * 0.4f), boxSize - (boxSize * 0.4f));
	}
}