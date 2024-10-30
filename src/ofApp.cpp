
#include "ofApp.h"
#include "box.h"
#include "grid.h"

Box box1;
Box box2;
Grid mainGrid;

//--------------------------------------------------------------
void ofApp::setup() {
	// Setting up gui
	//gui.setup();
	//gui.add(gridColumns.setup("# of Columns", 8, 5, 50));
	//gui.add(gridRows.setup("# of Rows", 8, 5, 50));
	//gui.add(numberOfMines.setup("# of Mines", 10, 2, 450));
	//gui.add(restartBtn.setup("Submit"));

	//gui.add(flaggingMode.setup("Flagging Mode", false));

	//ofSetupOpenGL(100, 100, OF_WINDOW);
	ofBackground(200, 200, 200);

	glm::vec2 box1position(0, 0);
	glm::vec2 box2position(10, 0);

	//box1 = Box(glm::vec2(0, 0), 10.0f, false, 0);
	//box2 = Box(glm::vec2(10, 0), 10.0f, false, 0);

	mainGrid = Grid(8, 8, 10, 20.0f);
	mainGrid.generateGrid();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	//box1.display();
	//box2.display();
	mainGrid.displayGrid();
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
