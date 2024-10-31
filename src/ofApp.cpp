
#include "ofApp.h"

Grid mainGrid;
float boxSize = 45.0f;
int mineCount = 10;
ofImage mineImage;
bool invalidGameSettings = false;

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

	ofBackground(200, 200, 200);

	mainGrid = Grid(8, 8, mineCount, boxSize);
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
			invalidGameSettings = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	mainGrid.displayGrid(mineImage, font);

	gui.draw();

	if (invalidGameSettings) {
		ofDrawBitmapStringHighlight("Sorry there are too many mines for the number of boxes! Please Try Again", ofGetWidth() / 2, ofGetHeight() / 4);
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
	mainGrid.checkBoxHovered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

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
