#define __DMXController_BlaueNacht_CM__oscHelper__


#ifndef OSCHELPER_H_INCLUDED
#define OSCHELPER_H_INCLUDED

#include "ofMain.h"
#include "ofxOsc.h"

#include <iostream>



class oscHelper{
    
    
public:
    
    void setup();
    void listen();
    float* getSettings();
    float settings[14];

private:
    
    ofxOscReceiver receiver;
    
    
};

#endif
