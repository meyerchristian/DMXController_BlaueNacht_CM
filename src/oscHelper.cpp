//
//  File.cpp
//  DMXController_BlaueNacht_CM
//
//  Created by Christian Meyer on 26.03.14.
//
//

#include "oscHelper.h"
#include "testApp.h"

void oscHelper::setup()
{
    cout << "listening for osc messages on port " << 1100 << "\n";
    receiver.setup(1100);
    
    settings[0] = 0;
    settings[1] = 0;
    settings[2] = 0;
    settings[3] = 0;
    settings[4] = 0;
    settings[5] = 0;
    settings[6] = 0;
    settings[7] = 0;
    settings[8] = 0;
    settings[9] = 0;
    settings[10] = 0;
    settings[11] = 0;
    settings[12] = 0;
    settings[13] = 0;
}

void oscHelper::listen()
{
    while(receiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        if(m.getAddress() == "/color/col_01_h"){
            settings[0] = (m.getArgAsFloat(0) * 255);
        }

        if(m.getAddress() == "/color/col_01_s"){
            settings[1] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_01_b"){
            settings[2] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_02_h"){
            settings[3] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_02_s"){
            settings[4] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_02_b"){
            settings[5] = (m.getArgAsFloat(0) * 255);
        }

        if(m.getAddress() == "/color/col_03_h"){
            settings[6] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_03_s"){
            settings[7] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_03_b"){
            settings[8] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_04_h"){
            settings[9] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_04_s"){
            settings[10] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_04_b"){
            settings[11] = (m.getArgAsFloat(0) * 255);
        }
        
        if(m.getAddress() == "/color/col_04_speedspektrum"){
            settings[12] = (m.getArgAsFloat(0) * 200);
        }
        
        if(m.getAddress() == "/color/col_04_valuespektrum"){
            settings[13] = (m.getArgAsFloat(0) * 10);
        }
    }
}

float* oscHelper::getSettings()
{
    return settings;
}