
#include "ofApp.h"
#include "box.h"
#include "grid.h"

Grid mainGrid;
float boxSize = 20.0f;

//--------------------------------------------------------------
void ofApp::setup() {
	// Setting up gui
	gui.setup();
	gui.add(gridColumns.setup("# of Columns", 8, 5, 50));
	gui.add(gridRows.setup("# of Rows", 8, 5, 50));
	gui.add(numberOfMines.setup("# of Mines", 10, 2, 450));
	gui.add(restartBtn.setup("Restart"));

	//gui.add(flaggingMode.setup("Flagging Mode", false));

	ofBackground(200, 200, 200);

	mainGrid = Grid(8, 8, 10, boxSize);
	mainGrid.generateGrid();
}

//--------------------------------------------------------------
void ofApp::update() {
	// When pressing restart button, generate new grid with corresponding gui given rows and columns (mines)
	if (restartBtn) {
		mainGrid.generateGrid(gridRows, gridColumns, numberOfMines, boxSize);
	}

	mainGrid.checkBoxHovered(ofGetMouseX(), ofGetMouseY());
}

//--------------------------------------------------------------
void ofApp::draw() {
	mainGrid.displayGrid();

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

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
