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
}, isMine{ isMine }, numberOfAdjacentMines{ numberOfAdjacentMines }, flagged{ false }, revealed{ false }{}

void Box::toggleFlag() {

}

void Box::display() {
	if (!revealed) {
		ofSetColor(255, 255, 255);
		ofDrawRectangle(position.x - 2, position.y - 2, boxSize + 4, boxSize + 4);

		ofSetColor(0, 0, 0);
		ofDrawRectangle(position.x - 1, position.y - 1, boxSize + 2, boxSize + 2);

		ofSetColor(25, 25, 25);
		ofDrawRectangle(position.x - 1, position.y - 1, boxSize + 2, boxSize + 2);
	}
}
