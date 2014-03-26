#include "testApp.h"

void testApp::setup() {
	dmx.connect("tty.usbserial-EN088411"); // Connection to ENTTEC DMX USB PRO
    level1.set(124, 255, 255);
    level2.set(151,255,255);
}

void testApp::update() {
	// use the time to generate a level
	//level1 = ofMap(sin(ofGetElapsedTimef() * 10), -1, 1, 0, 255);
	
	// pulses channels 1 and 2
    dmx.setLevel(8, level2.r);
    dmx.setLevel(9, level2.g);
    dmx.setLevel(10, level2.b);
    dmx.setLevel(14, 255);
}

void testApp::keyPressed(int key){
    
    if (key == 'h'){
        level1.setHue(200);
        cout << "Hue col_01:" << float(level1.getHue()) << endl;
        cout << "Saturation col_01:" << int(level1.getSaturation()) << endl;
        cout << "Brightness col_01:" << int(level1.getBrightness()) << endl;
        cout << "-----" << endl;
        cout << "R col_01:" << ofToString(int(level1.r)) << endl;
        cout << "G col_0aaaaaaaa1:" << ofToString(int(level1.g)) << endl;
        cout << "B col_01:" << ofToString(int(level1.b)) << endl;
        cout << "---------------------" << endl;
        
        dmx.setLevel(1, level1.r);
        dmx.setLevel(2, level1.g);
        dmx.setLevel(3, level1.b);
        dmx.setLevel(7, 255);
        dmx.update();
    }
}


void testApp::draw() {
	ofSetColor(level1);
	ofSetColor(level2);
    
}

    

///dev
//ll

