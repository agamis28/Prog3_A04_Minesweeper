#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "box.h"
#include "grid.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// OFX Initalized Variables
	ofxPanel gui;

	ofxIntSlider gridColumns;
	ofxIntSlider gridRows;
	ofxIntSlider numberOfMines;
	ofxButton restartBtn;

	//ofxToggle flaggingMode;

	// Initalizing Font
	ofTrueTypeFont font;
};