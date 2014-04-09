#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "ofxUI.h"

#include "oscHelper.h"
#define PORT 8000
#define HOST "141.75.214.249"
#define NUM_MSG_STRINGS 20

//Search: //dev /ll
#define DEVICE "tty.usbserial-EN088411"


struct light{
    int address;
    int red;
    int green;
    int blue;
    int master;
};

class testApp : public ofBaseApp{
    
public:
    
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void updateDMX();
    void updateConsole();
    void brightnessplus();
    void brightnessminus();
    void drawRects();
    void updateTouchOSC();

    light group_01 =    {0, 1, 2, 3, 7};
    light group_02 =    {7, 1, 2, 3, 7};
    light group_03 =   {15, 1, 2, 3, 7};
    light group_04 =   {22, 1, 2, 3, 7};
    
    ofColor col_01;
    ofColor col_02;
    ofColor col_03;
    ofColor col_04;
    
	ofxUISuperCanvas *gui1;
    void setGui1();
    void gui1Event(ofxUIEventArgs &e);
	ofxUISuperCanvas *gui2;
    void setGui2();
    void gui2Event(ofxUIEventArgs &e);
	ofxUISuperCanvas *gui3;
    void setGui3();
    void gui3Event(ofxUIEventArgs &e);
	ofxUISuperCanvas *gui4;
    void setGui4();
    void gui4Event(ofxUIEventArgs &e);

    ofxDmx *dmx;
    bool hasDevice;
    
    oscHelper osc;
    ofxOscSender sender;
    
    bool kb = false;
    bool touchosc = false;
    float timespektrum;
    float timezwei;
    float zeit;
    int anton;
    bool brightness;
    bool beat;
    float speedspektrum;
    float valuespektrum;

    
    // OSC
    ofTrueTypeFont font;
    ofxOscReceiver receiver;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    float oscIncoming;
    
    float test;
    float c3test;
};
