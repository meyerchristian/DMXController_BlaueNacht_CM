#pragma once

#include "ofMain.h"
#include "ofxDmx.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	ofxDmx dmx;
	ofColor level1;
    ofColor level2;    
};
