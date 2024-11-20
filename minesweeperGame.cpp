#include "minesweeperGame.h"

// Minesweeper Game Constructor 
// Constructors Default Settings
MinesweeperGame::MinesweeperGame() : boxSize{ 45.0f }, mineCount{ 10 } {}

// Constructor With Parameters
MinesweeperGame::MinesweeperGame(float sizeOfBox, int mineCount)
	: boxSize{ sizeOfBox }, mineCount{ mineCount } {}

// Setting up all aspects of minesweeper game
void MinesweeperGame::setupGame() {
	// Setting up gui
	gui.setup();
	gui.add(gridColumns.setup("# of Columns", 8, 5, 50));
	gui.add(gridRows.setup("# of Rows", 8, 5, 25));
	gui.add(numberOfMines.setup("# of Mines", 10, 2, 450));
	gui.add(restartBtn.setup("Restart"));
	gui.add(flaggingMode.setup("Flagging Mode", false));

	//gui.add(flaggingMode.setup("Flagging Mode", false));

	// Setting up images
	backgroundImage.load("MinesweeperTile000.png");
	coverImage.load("MinesweeperTile001.png");
	mineImage.load("MinesweeperTile002.png");
	flagImage.load("MinesweeperTile004.png");
	hitMineImage.load("MinesweeperTile003.png");

	// Setting up fonts
	numberFont.load("VCR_OSD_MONO_1.001.ttf", boxSize / 2);
	textFont.load("VCR_OSD_MONO_1.001.ttf", boxSize / 4);

	// Background
	ofBackground(200, 200, 200);

	// Setting up grid
	mainGrid = Grid(8, 8, mineCount, boxSize);
	// Generating the grid (Random mine placement, checking all neighbouring mine count)
	mainGrid.generateGrid();
}

// Update all aspects of minesweeper game
void MinesweeperGame::updateGame() {
	// When pressing restart button, generate new grid with corresponding gui given rows and columns (mines)
	if (restartBtn) {
		// Only allow restart when grid boxes are more than number of mines
		if (mainGrid.boxes.size() > numberOfMines) {
			invalidGameSettings = false;
			mainGrid.generateGrid(gridRows, gridColumns, numberOfMines, boxSize);
			gameInProgress = false;
			timerCount = 0;
			gameState = inProgress;
		}
		else {
			// When too many mines set invalidGameSettings to true
			invalidGameSettings = true;
		}
	}

	// Timer
	if (gameInProgress) {
		// Get the elapsed time since the start of the game
		float currentTime = ofGetElapsedTimef();

		// If one second has passed, increment the timer count
		if (currentTime - lastTime >= 1.0f) {
			timerCount++;
			lastTime = currentTime; // Update last time to current time
		}
	}

	// Shaking
	// If is shaking is active shake for shake duration with shake force random radius of shake
	if (isShaking) {

		// Add random shake position each frame
		shakePosition.x = ofRandom(-shakeForce, shakeForce);
		shakePosition.y = ofRandom(-shakeForce, shakeForce);

		// Add time of last frame to  the shake time
		shakeElapsedTime += ofGetLastFrameTime();

		// Stop shaking when elapsed time surpasses the duration
		if (shakeElapsedTime >= shakeDuration) {
			isShaking = false;
			shakePosition.set(0, 0);
			shakeElapsedTime = 0;
		}
	}
}

// Display all aspects of minesweeper game
void MinesweeperGame::displayGame() {

	// Keep screen shake only elements inside of matrix
	ofPushMatrix();
	// Move all elements to the shaked position if there is any
	ofTranslate(shakePosition);

	// Drawing Grid
	mainGrid.displayGrid(backgroundImage, coverImage, mineImage, flagImage, hitMineImage, numberFont, textFont);

	// Drawing game lost and game won messages
	if (gameState == gameLoss) {
		ofSetColor(0);
		textFont.drawString("SORRY, YOU UNCOVERED A MINE. YOU LOST. PLEASE TRY AGAIN ", ofGetWidth() / 2 - boxSize * 5, ofGetHeight() / 2 - boxSize * 5);
	}
	if (gameState == gameWon) {
		ofSetColor(0);
		textFont.drawString("YAY YOU WON! YOU UNCOVERED EVERYTHING BUT THE MINES! YOU BEAT THE GAME IN " + std::to_string(timerCount) + " SECONDS!", ofGetWidth() / 2 - boxSize * 8.5, ofGetHeight() / 2 - boxSize * 5);
	}

	// Draw Timer
	ofSetColor(0);
	textFont.drawString("Timer: " + std::to_string(timerCount), ofGetWidth() / 2 + boxSize * 2, 50);

	// When game is invalid, let player know with bitmap graphics
	if (invalidGameSettings) {
		ofDrawBitmapStringHighlight("Sorry there are too many mines", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
		ofDrawBitmapStringHighlight("for the number of boxes!", ofGetWidth() / 2 - 30, ofGetHeight() / 2 + 25);
		ofDrawBitmapStringHighlight("Please Try Again", ofGetWidth() / 2, ofGetHeight() / 2 + 50);
	}

	// Reset matrix to normal
	ofPopMatrix();

	// Drawing gui
	gui.draw();
}

// When mouse moves, highlight the hovered box if hovering a box
void MinesweeperGame::mouseMovedGame(int x, int y) {
	// While game is in progress
	if (gameState == inProgress) {
		// When mouse is moved, check the box it is hovered over on grid and changes its color
		mainGrid.checkBoxHovered(x, y);
	}
}

// When mouse is pressed, reveal the clicked box or flag it
void MinesweeperGame::mousePressedGame(int x, int y, int button) {
	// While game is in progress
	if (gameState == inProgress) {

		// Set game in progress back to true if false (for timer)
		gameInProgress = true;

		// When right clicking use flagging mode
		if (button == OF_MOUSE_BUTTON_RIGHT) {
			mainGrid.flagClickedBox(mainGrid.getClickedBox(x, y));
		}

		// When left clicking use regular mode unless flagging mode is set
		if (button == OF_MOUSE_BUTTON_LEFT) {

			// When in flagging mode, flag the clicked box
			if (flaggingMode) {
				mainGrid.flagClickedBox(mainGrid.getClickedBox(x, y));
			}
			else {
				// When mouse is pressed, reveal the clicked boxs
				mainGrid.revealClickedBox(mainGrid.getClickedBox(x, y));

				// Check if won the game
				if (mainGrid.isOnlyMinesRemaining()) {
					mainGrid.flagAllRemaining(); // When winning flag all mines
					gameInProgress = false;
					std::cout << "GAME IS OVER, YOU WON!!\n";
					gameState = gameWon; // Set game won to stop functionality of game till restart
				}

				// Check if lost the game
				if (mainGrid.isMineRevealed()) {
					mainGrid.revealAllMines(); // When losing reveal all mines
					isShaking = true; // Turn on screen shake, auto turn off after duration in update
					gameInProgress = false;
					std::cout << "GAME IS OVER, YOU LOST!!\n";
					gameState = gameLoss; // Set game loss to stop functionality of game till restart
				}
			}

		}
	}
}
