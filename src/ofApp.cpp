
#include "ofApp.h"
#include <chrono>
#include <thread>

Grid mainGrid;
float boxSize = 45.0f;
int mineCount = 10;
bool invalidGameSettings = false; // When invalid game settings is false, do not restart game
bool gameInProgress = false;
int timerCount = 0;
float lastTime = 0;

//--------------------------------------------------------------
void ofApp::setup() {
	// Setting up gui
	gui.setup();
	gui.add(gridColumns.setup("# of Columns", 8, 5, 50));
	gui.add(gridRows.setup("# of Rows", 8, 5, 25));
	gui.add(numberOfMines.setup("# of Mines", 10, 2, 450));
	gui.add(restartBtn.setup("Restart"));
	gui.add(flaggingMode.setup("Flagging Mode", false));

	//gui.add(flaggingMode.setup("Flagging Mode", false));

	// Setting up mine image
	mineImage.load("mineImage.png");

	// Setting up flag image
	flagImage.load("flagImage.png");

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

//--------------------------------------------------------------
void ofApp::update() {
	// When pressing restart button, generate new grid with corresponding gui given rows and columns (mines)
	if (restartBtn) {
		// Only allow restart when grid boxes are more than number of mines
		if (mainGrid.boxes.size() > numberOfMines) {
			invalidGameSettings = false;
			mainGrid.generateGrid(gridRows, gridColumns, numberOfMines, boxSize);
			gameInProgress = false;
			timerCount = 0;
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
			lastTime = currentTime;  // Update last time to current time
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Drawing Grid
	mainGrid.displayGrid(mineImage, flagImage, numberFont, textFont);

	// Drawing gui
	gui.draw();

	// Draw Timer
	ofSetColor(0);
	textFont.drawString("Timer: " + std::to_string(timerCount), ofGetWidth() / 2 + boxSize * 2, 50);

	// When game is invalid, let player know with bitmap graphics
	if (invalidGameSettings) {
		ofDrawBitmapStringHighlight("Sorry there are too many mines", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
		ofDrawBitmapStringHighlight("for the number of boxes!", ofGetWidth() / 2 - 30, ofGetHeight() / 2 + 25);
		ofDrawBitmapStringHighlight("Please Try Again", ofGetWidth() / 2, ofGetHeight() / 2 + 50);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	// When mouse is moved, check the box it is hovered over on grid and changes its color
	mainGrid.checkBoxHovered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	gameInProgress = true;
	if (flaggingMode) {
		mainGrid.flagClickedBox(mainGrid.getClickedBox(x, y));
	}
	else {
		// When mouse is pressed, reveal the clicked box
		mainGrid.revealClickedBox(mainGrid.getClickedBox(x, y));
		if (mainGrid.isOnlyMinesRemaining()) {
			std::cout << "GAME IS OVER, YOU WON!!";
		}
		if (mainGrid.isMineRevealed()) {
			std::cout << "GAME IS OVER, YOU LOST!! TOO BAD LOSER";
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
