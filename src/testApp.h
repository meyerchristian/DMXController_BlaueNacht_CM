#pragma once

#include "ofMain.h"
#include "ofxDmx.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
    void keyPressed(int key);

	ofxDmx dmx;
	ofShortColor level1;
    ofShortColor level2;
};
