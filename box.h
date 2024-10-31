#pragma once

#include "ofMain.h"
#include <string>

class Box {

	// Private Memebers
	glm::vec2 position;
	float boxSize;
	int numberOfAdjacentMines = 0;
	bool flagged = false;
	bool revealed = true;

	ofColor boxInnerColor = ofColor(150, 150, 150);
public:
	// Default Constructor
	Box();
	// Constructor
	Box(glm::vec2 position, float boxSize, bool isMine, int numberOfAdjacentMines, bool flagged = false, bool revealed = true);

	// Public member
	bool isMine;

	// Public members colors
	ofColor boxDefaultColor = boxInnerColor;
	ofColor boxHoveredColor = ofColor(100, 100, 100);

	void toggleFlag();
	void setColor(ofColor settingBoxInnerColor);
	void setMine();
	void setAdjacent(int numberOfNeighbours);
	int getAdjacent();
	void setReveal();
	bool getRevealed();
	bool containsPosition(float x, float y); // Returns true if x and y positions are within the bounds of this box's position and size
	void display(ofImage& mineImage, ofTrueTypeFont& numberFont);
};
