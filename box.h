#pragma once

#include "ofMain.h"

class Box {

	// Private Memebers
	glm::vec2 position;
	bool isMine;
	float boxSize;
	int numberOfAdjacentMines = 0;
	bool flagged = false;
	bool revealed = false;

public:
	// Default Constructor
	Box();
	// Constructor
	Box(glm::vec2, float, bool, int, bool flagged = false, bool revealed = false);

	void toggleFlag();
	void display();
};
