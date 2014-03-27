#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxUI.h"

// OSC
#include "oscHelper.h"
#define PORT 8000
#define NUM_MSG_STRINGS 20

// Deice: ENTTEC DMX USB PRO - MAC OSX Search: //dev /ll
#define DEVICE "tty.usbserial-EN088411"


// Define of struct "light"
struct light{
    int address; //adress-offset. DMX starts at 1
    int red;
    int green;
    int blue;
    int master;
};

class testApp : public ofBaseApp{
    
public:
    
    // OSC
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    oscHelper osc;
    
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // DMX settings
    ofxDmx *dmx;
    bool hasDevice;
    void updateDMX();
    
    // console
    void updateConsole();
    
    // Different light groups
    light group_01 =    {0, 1, 2, 3, 7};    // left wall
    light group_02 =    {7, 1, 2, 3, 7};    // heart
    light group_03 =   {15, 1, 2, 3, 7};    // right wall
    light group_04 =   {22, 1, 2, 3, 7};    // trees
    
    // Different colors for light groups
    ofColor col_01, col_02, col_03, col_04;
    
    // UI Setup left wall
	ofxUISuperCanvas *gui1;
    void setGui1();
    void gui1Event(ofxUIEventArgs &e);
    
    // UI heart
	ofxUISuperCanvas *gui2;
    void setGui2();
    void gui2Event(ofxUIEventArgs &e);
    
    // UI Setup right wall
	ofxUISuperCanvas *gui3;
    void setGui3();
    void gui3Event(ofxUIEventArgs &e);
    
    // UI Setup trees
	ofxUISuperCanvas *gui4;
    void setGui4();
    void gui4Event(ofxUIEventArgs &e);
    
    bool kb = false;
    bool touchosc = false;
};
