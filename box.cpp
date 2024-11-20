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

// Used for later
void Box::toggleFlag() {
	flagged = !flagged;
}

bool Box::getFlagged() {
	return flagged;
}

// Sets 'isMine' to true
void Box::setMine() {
	isMine = true;
}

// Returns bool of 'isMine'
bool Box::getMine() {
	return isMine;
}

// Sets' numberOfAdjacentMines' to parameter value
void Box::setAdjacent(int numberOfAdjacent) {
	numberOfAdjacentMines = numberOfAdjacent;
}

// Returns int of 'numberOfAdjacentMines'
int Box::getAdjacent() {
	return numberOfAdjacentMines;
}

// Sets 'revealed' to true
void Box::setReveal() {
	revealed = true;
}

// Returns bool of 'revealed'
bool Box::getRevealed() {
	return revealed;
}

// Sets color of none revealed box (Used for hover interactivity)
void Box::setColor(ofColor newColor) {
	boxInnerColor = newColor;
}

// Check if the box contains a position, if the given position is within the bounds of this box. Return true.
bool Box::containsPosition(float x, float y) {
	return x >= position.x && x <= position.x + boxSize && y >= position.y && y <= position.y + boxSize; // Returns true if position param is within the bounds of box.
}

// Displays box when not revealed. When revealed only show background draw squares. If revealed and is mine show a mine image. If revealed and has adjacent mines, draw those associated numbers.
void Box::display(ofImage& backgroundImage, ofImage& coverImage, ofImage& mineImage, ofImage& flagImage, ofImage& hitMineImage, ofTrueTypeFont& font) {

	// When not revealed draw default box
	if (!revealed) {
		//// Outline
		//ofSetColor(0);
		//ofDrawRectangle(position.x, position.y, boxSize, boxSize);

		//// Background
		//ofSetColor(255);
		//ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));

		//// Cover
		//ofSetColor(boxInnerColor);
		//ofDrawRectangle(position.x + (boxSize * 0.2f), position.y + (boxSize * 0.2f), boxSize - (boxSize * 0.4f), boxSize - (boxSize * 0.4f));

		// Draw background image when image is allocated
		if (backgroundImage.isAllocated()) {
			// Background Image
			ofSetColor(255);
			backgroundImage.draw(position.x + (boxSize / 8), position.y + (boxSize / 6), boxSize, boxSize);
		}

		// Draw covered box image when image is allocated
		if (coverImage.isAllocated()) {
			// Cover Image
			ofSetColor(255);
			coverImage.draw(position.x + (boxSize / 8), position.y + (boxSize / 6), boxSize, boxSize);
		}

		if (flagged) {
			// Draw flag image when image is allocated
			if (flagImage.isAllocated()) {
				// Flag Image
				ofSetColor(255);
				flagImage.draw(position.x + (boxSize / 8), position.y + (boxSize / 6), boxSize, boxSize);
			}
		}
	}
	else {
		// When revealed, do not draw cover anymore

		// If isMine, display mine
		// Else display number of adjacent mines, if no adjacent mines show empty
		if (isMine) {
			//// Outline
			//ofSetColor(0);
			//ofDrawRectangle(position.x, position.y, boxSize, boxSize);

			//// Background
			//ofSetColor(255);
			//ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));

			// Draw mine image when image is allocated
			if (mineImage.isAllocated()) {
				// Mine Image
				ofSetColor(255);
				mineImage.draw(position.x + (boxSize / 8), position.y + (boxSize / 6), boxSize, boxSize);
			}
		}
		else {
			//// Outline
			//ofSetColor(0);
			//ofDrawRectangle(position.x, position.y, boxSize, boxSize);

			//// Background
			//ofSetColor(255);
			//ofDrawRectangle(position.x + (boxSize * 0.1f), position.y + (boxSize * 0.1f), boxSize - (boxSize * 0.2f), boxSize - (boxSize * 0.2f));

			// Draw background image when image is allocated
			if (backgroundImage.isAllocated()) {
				// Background Image
				ofSetColor(255);
				backgroundImage.draw(position.x + (boxSize / 8), position.y + (boxSize / 6), boxSize, boxSize);
			}

			// When there is adjacent mines display a number
			if (numberOfAdjacentMines != 0) {
				// Use font and display number of 'numberOfAdjacentMines'
				ofSetColor(0);
				font.drawString(std::to_string(numberOfAdjacentMines), position.x + (boxSize / 2), position.y + (boxSize / 1.10f));
			}
		}
	}
}
