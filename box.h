#pragma once

#include "ofMain.h"
#include <string>

// A class for a box in a grid on a minesweeper game
class Box {

	// Private members for Box class
	glm::vec2 position;
	float boxSize;
	bool isMine;
	int numberOfAdjacentMines = 0;
	bool flagged = false;
	bool revealed = true;

	// Color box when not revealed
	ofColor boxInnerColor = ofColor(150, 150, 150);

public:

	// Default Constructor
	Box();
	// Constructor when given parameters
	Box(glm::vec2 position, float boxSize, bool isMine, int numberOfAdjacentMines, bool flagged = false, bool revealed = true);

	// Public members for colors (Allows other classes to get box colors)
	ofColor boxDefaultColor = boxInnerColor;
	ofColor boxHoveredColor = ofColor(100, 100, 100);

	// Box class forward declaring functions
	void toggleFlag();
	void setColor(ofColor settingBoxInnerColor);
	void setMine();
	bool getMine();
	void setAdjacent(int numberOfNeighbours);
	int getAdjacent();
	void setReveal();
	bool getRevealed();
	bool containsPosition(float x, float y); // Returns true if x and y positions are within the bounds of this box's position and size
	void display(ofImage& mineImage, ofImage& flagImage, ofTrueTypeFont& numberFont);
};
