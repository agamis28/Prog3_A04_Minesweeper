
#include "ofApp.h"

Grid mainGrid;
float boxSize = 45.0f;
int mineCount = 10;
ofImage mineImage;
bool invalidGameSettings = false; // When invalid game settings is false, do not restart game

//--------------------------------------------------------------
void ofApp::setup() {
	// Setting up gui
	gui.setup();
	gui.add(gridColumns.setup("# of Columns", 8, 5, 50));
	gui.add(gridRows.setup("# of Rows", 8, 5, 25));
	gui.add(numberOfMines.setup("# of Mines", 10, 2, 450));
	gui.add(restartBtn.setup("Restart"));

	//gui.add(flaggingMode.setup("Flagging Mode", false));

	// Setting up mine image
	mineImage.load("mineImage.png");

	// Setting up font
	font.load("VCR_OSD_MONO_1.001.ttf", boxSize / 2);

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
		}
		else {
			// When too many mines set invalidGameSettings to true
			invalidGameSettings = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Drawing Grid
	mainGrid.displayGrid(mineImage, font);

	// Drawing gui
	gui.draw();

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
	// When mouse is pressed, reveal the clicked box
	mainGrid.revealClickedBox(x, y);
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
