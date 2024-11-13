#pragma once

#include "ofMain.h"
#include "Box.h"

#include <random>

// A class to contain a grid organized vector of boxes for minesweeper game
class Grid {

	// Private members for Grid class
	int currentRows;
	int currentColumns;
	int currentMines;
	float boxSize;

	// Setting mine location vector
	std::vector<int>mineLocations;

	// Number of boxes flagged
	int flaggedCount = 0;

	// For game class
	bool mineIsRevealed = false;

public:
	// Public Members
	std::vector<Box>boxes;

	// Default Constructor
	Grid();
	// Constructor when given parameters
	Grid(int currentRows, int currentColumns, int currentMines, float boxSize);

	// Grid class forward declaring functions
	void createBoxes();
	void setRandomMineLocations();
	void setNeighbours();
	void generateGrid();
	void generateGrid(int rows, int columns, int mines, float boxSize);
	void checkBoxHovered(float mousePositionX, float mousePositionY);
	int getClickedBox(float mousePositionX, float mousePositionY);
	void flagClickedBox(int boxClicked);
	void revealClickedBox(int boxClicked);
	void revealEmptyNeighbours(int boxIndex);
	int getFlaggedAmount();
	bool isMineRevealed();
	bool isOnlyMinesRemaining();
	void flagAllRemaining();
	void revealAllMines();
	void displayGrid(ofImage& mineImage, ofImage& flagImage, ofTrueTypeFont& numberFont, ofTrueTypeFont& textFont);
	void displayMinesLeft(ofTrueTypeFont& font);
};