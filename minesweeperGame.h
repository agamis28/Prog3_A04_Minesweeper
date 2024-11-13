#pragma once

#include "ofMain.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include "ofxGui.h"
#include "Box.h"
#include "Grid.h"

// A Minesweeper Game class, requires grid and box classes
class MinesweeperGame {

	// Private members in constructor
	float boxSize;
	int mineCount;

	// Private members for MinesweeperGame class
	enum GameState {
		inProgress,
		gameLoss,
		gameWon
	};
	GameState gameState = inProgress;
	bool invalidGameSettings = false; // When invalid game settings is false, do not restart game
	bool gameInProgress = false;
	Grid mainGrid;

	// Timer
	int timerCount = 0;
	float lastTime = 0;

	// OFX Initalized Variables
	ofxPanel gui;

	ofxIntSlider gridColumns;
	ofxIntSlider gridRows;
	ofxIntSlider numberOfMines;
	ofxButton restartBtn;
	ofxToggle flaggingMode;

	// Initalizing Fonts
	ofTrueTypeFont numberFont;
	ofTrueTypeFont textFont;


	// Images
	ofImage mineImage;
	ofImage flagImage;

public:

	// Default Constructor
	MinesweeperGame();
	// Constructor when given parameters
	MinesweeperGame(float sizeOfBox, int numberOfStartingMines);

	// MinesweeperGame class forward declaring functions
	void setupGame();
	void updateGame();
	void displayGame();
	void mouseMovedGame(int mousePositionX, int mousePositionY);
	void mousePressedGame(int mousePositionX, int mousePositionY);
};