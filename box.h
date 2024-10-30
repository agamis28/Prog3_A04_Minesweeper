#pragma once

#include "ofMain.h"

class Box {

	// Private Memebers
	glm::vec2 position;
	float boxSize;
	bool isMine;
	int numberOfAdjacentMines = 0;
	bool flagged = false;
	bool revealed = false;

public:
	// Default Constructor
	Box();
	// Constructor
	Box(glm::vec2 position, float boxSize, bool isMine, int numberOfAdjacentMines, bool flagged = false, bool revealed = false);

	void toggleFlag();
	void display();
};
